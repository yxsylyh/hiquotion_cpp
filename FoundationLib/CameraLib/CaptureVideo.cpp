//Download by http://www.NewXing.com
// CaptureVideo.cpp : 实现文件
//

#include "stdafx.h"
#include "CaptureVideo.h"
#include <dvdmedia.h>
#include <algorithm>

#pragma comment(lib, "quartz.lib")
#pragma comment(lib, "strmiids.lib")

#ifndef srelease
#define srelease(x)		\
	if ( NULL != x )	\
	{					\
		x->Release( );	\
		x = NULL;		\
	}
#endif

// CSampleGrabberCB

CSampleGrabberCB::CSampleGrabberCB()
{
	m_lWidth = 0;
	m_lHeight = 0;
	m_sFileName = _T("");
	m_bSnapshot = FALSE;

	m_action=0;
	m_callback=NULL;
}

STDMETHODIMP CSampleGrabberCB::QueryInterface(REFIID riid, void ** ppv)
{
	if(riid == IID_ISampleGrabberCB || riid == IID_IUnknown)
	{
		*ppv = (void *)static_cast<ISampleGrabberCB*>(this);
		return NOERROR;
	}

	return E_NOINTERFACE;
}

STDMETHODIMP CSampleGrabberCB::SampleCB(double SampleTime, IMediaSample * pSample)
{
	return 0;
}


STDMETHODIMP CSampleGrabberCB::BufferCB( double dblSampleTime, BYTE * pBuffer, long lBufferSize )
{
	if(!m_bSnapshot)
		return 0;

	if(m_action==0)
	{
		if(!pBuffer)return E_POINTER;

		SaveBitmap(pBuffer, lBufferSize);
	}
	else if(m_action==1)
	{
		if(!m_callback)
			return 0;

		int length=sizeof(BITMAPFILEHEADER) + lBufferSize + sizeof( BITMAPINFOHEADER );
		char *buffer=new char[length];

		BITMAPFILEHEADER bfh;
		memset(&bfh, 0, sizeof(bfh));
		bfh.bfType ='MB';
		bfh.bfOffBits = 54;//+sizeof(RGBQUAD)*256; // sizeof(BITMAPINFOHEADER) + sizeof( BITMAPFILEHEADER);
		bfh.bfSize = bfh.bfOffBits + m_lHeight * m_lWidth * 24; // bfOffBits + 长 X 宽 X 位数 //length; /*sizeof(bfh) + lBufferSize + sizeof( BITMAPINFOHEADER);*/

		memcpy(buffer, &bfh, sizeof(bfh));

		BITMAPINFOHEADER bih;
		memset(&bih, 0, sizeof(bih));
		bih.biSize = sizeof(bih);
		bih.biWidth = m_lWidth;
		bih.biHeight = m_lHeight;
		bih.biPlanes = 1;
		bih.biBitCount = 24;
		bih.biXPelsPerMeter = 3780;
		bih.biYPelsPerMeter = 3780;
		bih.biSizeImage=bih.biWidth * bih.biHeight * bih.biBitCount;
		bih.biCompression=0;


		memcpy(buffer+sizeof(bfh), &bih, sizeof(bih));

		memcpy(buffer+sizeof(bfh)+sizeof(bih), pBuffer, lBufferSize);

		m_callback->OnSnapshot(buffer, length);

		delete buffer;
	}

	m_bSnapshot = FALSE;

	return 0;
}

//创建位图文件
BOOL CSampleGrabberCB::SaveBitmap(BYTE * pBuffer, long lBufferSize )
{
	HANDLE hf = CreateFile(m_sFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL,
						CREATE_ALWAYS, NULL, NULL);
	if( hf == INVALID_HANDLE_VALUE )return 0;

	// 写文件头 
	BITMAPFILEHEADER bfh;
	memset(&bfh, 0, sizeof(bfh));
	bfh.bfType ='MB';
	bfh.bfSize = sizeof(bfh) + lBufferSize + sizeof( BITMAPINFOHEADER);
	bfh.bfOffBits = sizeof(BITMAPINFOHEADER) + sizeof( BITMAPFILEHEADER);
	DWORD dwWritten = 0;
	WriteFile(hf, &bfh, sizeof(bfh), &dwWritten, NULL );

	// 写位图格式
	BITMAPINFOHEADER bih;
	memset(&bih, 0, sizeof(bih));
	bih.biSize = sizeof(bih);
	bih.biWidth = m_lWidth;
	bih.biHeight = m_lHeight;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	WriteFile(hf, &bih, sizeof(bih), &dwWritten, NULL);

	// 写位图数据
	WriteFile(hf, pBuffer, lBufferSize, &dwWritten, NULL);
	CloseHandle(hf);
	return 0;
}


// CCaptureVideo

IMPLEMENT_DYNAMIC(CCaptureVideo, CWnd)

CCaptureVideo::CCaptureVideo()
{
	//COM Library Intialization
	if(FAILED(CoInitialize(NULL)))
	{
		AfxMessageBox(_T("CoInitialize Failed!\r\n"));
		return;
	}

	m_pGB = NULL;
	m_pCapture = NULL;
	m_pBF = NULL;
	m_pMC = NULL;
	m_pVW = NULL;
	m_pGrabber = NULL;

	m_iCameraID = -1;
	m_bCaptureStart = FALSE;
	m_bFullScreen = 0;

	m_bCaptureStart = FALSE;

	m_action=0;
}

CCaptureVideo::~CCaptureVideo()
{
	ReleaseCaptureRes();

	CoUninitialize();
}

void CCaptureVideo::ReleaseCaptureRes()
{
	if(m_pMC)m_pMC->Stop();
	if(m_pVW)
	{
		m_pVW->put_Visible(OAFALSE);
		m_pVW->put_Owner(NULL);
	}

	m_pGrabber.Release();
	m_pGrabber = NULL;

	srelease(m_pCapture);
	srelease(m_pVW);
	srelease(m_pMC);
	srelease(m_pGB);
	srelease(m_pBF);
}

BEGIN_MESSAGE_MAP(CCaptureVideo, CWnd)
	ON_WM_CONTEXTMENU()
// 	ON_COMMAND_RANGE(ID_CAMERALIST_ITEM1, ID_CAMERALIST_ITEM1+CAMERALIST_MAX_COUNT, &CCaptureVideo::OnCameraListItem)
// 	ON_COMMAND(ID_POPMENU_CAPTURESTART, &CCaptureVideo::OnPopmenuCapturestart)
// 	ON_COMMAND(ID_POPMENU_CAPTURESTOP, &CCaptureVideo::OnPopmenuCapturestop)
// 	ON_COMMAND(ID_POPMENU_FULLSCREEN, &CCaptureVideo::OnPopmenuFullscreen)
// 	ON_COMMAND(ID_POPMENU_SNAPSHOT, &CCaptureVideo::OnPopmenuSnapshot)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int GuidToString(const GUID &guid, char* buffer){
	int buf_len = 64;
	sprintf_s(
		buffer,
		buf_len,
		"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);
	return 0;
}

int GetMajorType(GUID guid, char* buffer) {
	memset(buffer, 0, 256);
	if (guid == MEDIATYPE_Video) {
		sprintf_s(buffer, 256, "MEDIATYPE_Video");
		return 0;
	}
	if (guid == MEDIATYPE_Audio) {
		sprintf_s(buffer, 256, "MEDIATYPE_Audio");
		return 0;
	}
	if (guid == MEDIASUBTYPE_RGB24) {
		sprintf_s(buffer, 256, "MEDIATYPE_Stream");
		return 0;
	}
	return -1;
}

int GetSubType(GUID guid, char* buffer) {
	memset(buffer, 0, 256);
	if( guid == MEDIASUBTYPE_YUY2){
		sprintf_s(buffer, 256, "MEDIASUBTYPE_YUY2");
		return 0;
	}
	if (guid == MEDIASUBTYPE_MJPG) {
		sprintf_s(buffer, 256, "MEDIASUBTYPE_MJPG");
		return 0;
	}
	if (guid == MEDIASUBTYPE_RGB24) {
		sprintf_s(buffer, 256, "MEDIASUBTYPE_RGB24");
		return 0;
	}
	return -1;
}

int GetFormatType(GUID guid, char* buffer) {
	memset(buffer, 0, 256);
	if (guid == FORMAT_VideoInfo) {
		sprintf_s(buffer, 256, "FORMAT_VideoInfo");
		return 0;
	}
	if (guid == FORMAT_VideoInfo2) {
		sprintf_s(buffer, 256, "FORMAT_VideoInfo2");
		return 0;
	}
	return -1;
}

int DsGetOptionDevice(IMoniker* pMoniker,TDeviceInfo& info) {
	USES_CONVERSION;
	HRESULT hr = NULL;
	IBaseFilter *pFilter;
	hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)&pFilter);
	if (!pFilter) {
		return -1;
	}
	IEnumPins * pinEnum = NULL;
	IPin * pin = NULL;
	if (FAILED(pFilter->EnumPins(&pinEnum))) {
		pinEnum->Release();
		return -1;
	}
	pinEnum->Reset();
	ULONG pinFetched = 0;
	while (SUCCEEDED(pinEnum->Next(1, &pin, &pinFetched)) && pinFetched) {
		if (!pin) {
			continue;
		}
		PIN_INFO pinInfo;
		if (FAILED(pin->QueryPinInfo(&pinInfo))) {
			continue;
		}
		if (pinInfo.dir != PINDIR_OUTPUT) {
			continue;
		}
#if PRINT_DEBUG
		printf("\t[Pin] Dir:Output Name %s\n", W2A(pinInfo.achName));
#endif

		IEnumMediaTypes *mtEnum = NULL;
		AM_MEDIA_TYPE   *mt = NULL;
		if (FAILED(pin->EnumMediaTypes(&mtEnum)))
			break;
		mtEnum->Reset();
		ULONG mtFetched = 0;
		while (SUCCEEDED(mtEnum->Next(1, &mt, &mtFetched)) && mtFetched) {
			char majorbuf[256];			
			if ( GetMajorType(mt->majortype, majorbuf) != 0) {
				GuidToString(mt->majortype, majorbuf);
			}
			char subtypebuf[256];
			if (GetSubType(mt->subtype, subtypebuf) != 0) {
				GuidToString(mt->subtype, subtypebuf);
			}					
			char formatbuf[256];
			if (GetFormatType(mt->formattype, formatbuf) != 0) {
				GuidToString(mt->formattype, formatbuf);				
			}
#if PRINT_DEBUG
			printf("\t%s\t%s\t%s", majorbuf, subtypebuf, formatbuf);
#endif
			BITMAPINFOHEADER* bmi = NULL;
			int avgTime;
			if (mt->formattype == FORMAT_VideoInfo) {
				if ( mt->cbFormat >= sizeof(VIDEOINFOHEADER)){					
					VIDEOINFOHEADER *pVih = reinterpret_cast<VIDEOINFOHEADER*>( mt->pbFormat);
					bmi = &( pVih->bmiHeader );
					avgTime = pVih->AvgTimePerFrame;
				}
			} else if (mt->formattype == FORMAT_VideoInfo2) {
				if (mt->cbFormat >= sizeof(VIDEOINFOHEADER2)) {
					VIDEOINFOHEADER2* pVih = reinterpret_cast<VIDEOINFOHEADER2*>(mt->pbFormat);
					bmi = &(pVih->bmiHeader);
					avgTime = pVih->AvgTimePerFrame;
				}
			}
			if( bmi ){
				info.SetResolution(bmi->biWidth, bmi->biHeight, avgTime);
#if PRINT_DEBUG
				printf("\t%d * %d, Bit %d\n", bmi->biWidth, bmi->biHeight, bmi->biBitCount);
#endif		
			}else {
				printf("\tNo find\n");
			}			
		}
		pin->Release();
	}
	return 0;
}

//根据设备最好的参数排序
bool SortDevice(const TDeviceInfo& device1, const TDeviceInfo& device2) {
	if (device1.BestParam.width > device2.BestParam.width)
		return true;
	return false;
}
//guidValue：
//CLSID_AudioInputDeviceCategory：获取音频输入设备列表
//CLSID_VideoInputDeviceCategory：获取视频输入设备列表
HRESULT DsGetAudioVideoInputDevices(std::vector<TDeviceInfo>& deviceVec, REFGUID guidValue)
{
	TDeviceInfo info;
	HRESULT hr;

	// 初始化  
	deviceVec.clear();

	// 初始化COM  
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (FAILED(hr)) {
// 		printf("Init error!\n");
		AfxMessageBox("Init error!\n");
		return hr;
	}
	// 创建系统设备枚举器实例  
	ICreateDevEnum *pSysDevEnum = NULL;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void **)&pSysDevEnum);
	if (FAILED(hr)){
		CoUninitialize();
// 		printf("Create instance error!\n");
		AfxMessageBox("Create instance error!\n");
		return hr;
	}
	// 获取设备类枚举器  
	IEnumMoniker *pEnumCat = NULL;
	hr = pSysDevEnum->CreateClassEnumerator(guidValue, &pEnumCat, 0);
	if (hr != S_OK) {
		CoUninitialize();
		//pSysDevEnum->Release();
		return hr;
	}

	// 枚举设备名称  
	IMoniker *pMoniker = NULL;
	ULONG cFetched;
	while (pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK) {
		IPropertyBag *pPropBag;
		hr = pMoniker->BindToStorage(NULL, NULL, IID_IPropertyBag, (void **)&pPropBag);
		if ( FAILED( hr ) ) {
			pMoniker->Release();
			continue;
		}		
		info.Reset();
		// 获取设备友好名  
		VARIANT varName;
		varName.vt = VT_BSTR;
		hr = pPropBag->Read(L"FriendlyName", &varName, NULL);
		if (SUCCEEDED(hr)) {
// 			StringCchCopy(info.FriendlyName, MAX_FRIENDLY_NAME_LENGTH, varName.bstrVal);
// #if PRINT_DEBUG
// 			wprintf(L"Device:%s\n", info.FriendlyName);
// #endif
// 			// 获取设备Moniker名  
// 			LPOLESTR pOleDisplayName = reinterpret_cast<LPOLESTR>(CoTaskMemAlloc(MAX_MONIKER_NAME_LENGTH * 2));
// 			if (pOleDisplayName != NULL) {
// 				hr = pMoniker->GetDisplayName(NULL, NULL, &pOleDisplayName);
// 				if (SUCCEEDED(hr)) {
// 					StringCchCopy( info.MonikerName, MAX_MONIKER_NAME_LENGTH, pOleDisplayName );
					//获取设备支持的分辨率
					DsGetOptionDevice( pMoniker, info );
					deviceVec.push_back( info );
// 				}
// 				CoTaskMemFree(pOleDisplayName);
//			}
		}		
//		VariantClear(&varName);
		pPropBag->Release();			
		pMoniker->Release();
	} // End for While  

	pEnumCat->Release();
	pSysDevEnum->Release();
	CoUninitialize();

//	std::sort( deviceVec.begin(), deviceVec.end(), SortDevice );
// 	for (int i = 0; i < deviceVec.size(); i++) {
// 		deviceVec[i].Debug();
// 	}
	return hr;
}

// CCaptureVideo 消息处理程序

int CCaptureVideo::EnumDevices(CStringArray& listCamera)
{
	//枚举视频扑捉设备
	ICreateDevEnum *pCreateDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pCreateDevEnum);
	if(hr != NOERROR)return -1;

	ATL::CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
	if(hr != NOERROR)return -1;

	pEm->Reset();

	int id = 0;
	ULONG cFetched;
	IMoniker *pM;
	while(hr = pEm->Next(1, &pM, &cFetched), hr == S_OK)
	{
		IPropertyBag *pBag;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void**)&pBag);
		if(SUCCEEDED(hr)) 
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if(hr == NOERROR)
			{
				id++;
				CString name(var.bstrVal);
				listCamera.Add(name);
				SysFreeString(var.bstrVal);
			}

			pBag->Release();
		}

		pM->Release();
	}

	return id;
}

int CCaptureVideo::EnumDevices(std::vector<TDeviceInfo>& deviceVec, REFGUID guidValue)
{
	return DsGetAudioVideoInputDevices(deviceVec, guidValue);
}

HRESULT CCaptureVideo::StartCapture(int iDeviceID)
{
	HRESULT hr;
	
	hr = InitCaptureGraphBuilder();
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Failed to get video interfaces!"));
		return hr;
	}

	// Bind Device Filter. We know the device because the id was passed in
	if(!BindFilter(iDeviceID, &m_pBF))return S_FALSE;

	hr = m_pGB->AddFilter(m_pBF, L"Capture Filter");

	// create a sample grabber
	hr = m_pGrabber.CoCreateInstance(CLSID_SampleGrabber);
	if(!m_pGrabber)
	{
		AfxMessageBox(_T("Fail to create SampleGrabber, maybe qedit.dll is not registered?"));
		return hr;
	}

	ATL::CComQIPtr<IBaseFilter, &IID_IBaseFilter> pGrabBase(m_pGrabber);

	//设置视频格式
	AM_MEDIA_TYPE mt;
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24;
	hr = m_pGrabber->SetMediaType(&mt);
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Fail to set media type!"));
		return hr;
	}

	hr = m_pGB->AddFilter(pGrabBase, L"Grabber");
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Fail to put sample grabber in graph"));
		return hr;
	}

	// try to render preview/capture pin
	hr = m_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, m_pBF, pGrabBase, NULL);
	if(FAILED(hr))
		hr = m_pCapture->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, m_pBF, pGrabBase,NULL);

	if(FAILED(hr))
	{
		AfxMessageBox(_T("Can't build the graph"));
		return hr;
	}

	hr = m_pGrabber->GetConnectedMediaType(&mt);
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Fail to read the connected media type"));
		return hr;
	}

	VIDEOINFOHEADER * vih = (VIDEOINFOHEADER*)mt.pbFormat;
	m_CB.m_lWidth = vih->bmiHeader.biWidth;
	m_CB.m_lHeight = vih->bmiHeader.biHeight;

	FreeMediaType(mt);
	hr = m_pGrabber->SetBufferSamples(FALSE);
	hr = m_pGrabber->SetOneShot(FALSE);
	hr = m_pGrabber->SetCallback(&m_CB, 1);

	//设置视频捕捉窗口
	SetupVideoWindow();

	hr = m_pMC->Run();//开始视频捕捉
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Couldn't run the graph!"));
		return hr;
	}

	m_bCaptureStart = TRUE;

	return S_OK;
}

HRESULT CCaptureVideo::StartCapture(int iDeviceID, int width, int height, int avgTimePerFrame)
{
	HRESULT hr;

	hr = InitCaptureGraphBuilder();
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Failed to get video interfaces!"));
		return hr;
	}

	// Bind Device Filter. We know the device because the id was passed in
	if(!BindFilter(iDeviceID, &m_pBF))return S_FALSE;

	hr = m_pGB->AddFilter(m_pBF, L"Capture Filter");


	VIDEO_STREAM_CONFIG_CAPS scc; 
	IAMStreamConfig*  pStreamConfig;
	AM_MEDIA_TYPE *pmtConfig;
	hr = m_pCapture->FindInterface(&PIN_CATEGORY_CAPTURE, 0, m_pBF, IID_IAMStreamConfig, (void**)&pStreamConfig); 
	if (FAILED(hr))
		return FALSE;
	hr = pStreamConfig->GetFormat(&pmtConfig);
	if (FAILED(hr))
	{
		pStreamConfig->Release();
		return FALSE;
	}

	VIDEOINFOHEADER * vih = (VIDEOINFOHEADER*) pmtConfig->pbFormat;
	vih->AvgTimePerFrame = avgTimePerFrame;
	vih->bmiHeader.biWidth = width;
	vih->bmiHeader.biHeight = height;/**/
// 	pmtConfig->majortype = MEDIATYPE_Video;
//	pmtConfig->subtype = MEDIASUBTYPE_RGB24;
	hr = pStreamConfig->SetFormat(pmtConfig);
	if (FAILED(hr))
	{
		pStreamConfig->Release();
		return FALSE;
	}
	pStreamConfig->Release();




	// create a sample grabber
	hr = m_pGrabber.CoCreateInstance(CLSID_SampleGrabber);
	if(!m_pGrabber)
	{
		AfxMessageBox(_T("Fail to create SampleGrabber, maybe qedit.dll is not registered?"));
		return hr;
	}

	ATL::CComQIPtr<IBaseFilter, &IID_IBaseFilter> pGrabBase(m_pGrabber);

	//设置视频格式
// 	BITMAPINFOHEADER bmi;
// 	memset(&bmi, 0x00, sizeof(BITMAPINFOHEADER));
// 
// 	bmi.biWidth=width;
// 	bmi.biHeight=height;

// 	int avgTime;
// 	if (mt->formattype == FORMAT_VideoInfo) {
// 		if ( mt->cbFormat >= sizeof(VIDEOINFOHEADER)){					
// 			VIDEOINFOHEADER *pVih = reinterpret_cast<VIDEOINFOHEADER*>( mt->pbFormat);
// 			bmi = &( pVih->bmiHeader );
// 			avgTime = pVih->AvgTimePerFrame;
// 		}
// 	} else if (mt->formattype == FORMAT_VideoInfo2) {
// 		if (mt->cbFormat >= sizeof(VIDEOINFOHEADER2)) {
// 			VIDEOINFOHEADER2* pVih = reinterpret_cast<VIDEOINFOHEADER2*>(mt->pbFormat);
// 			bmi = &(pVih->bmiHeader);
// 			avgTime = pVih->AvgTimePerFrame;
// 		}
// 	}
// 	if( bmi ){
// 		info.SetResolution(bmi->biWidth, bmi->biHeight, avgTime);


// 	AM_MEDIA_TYPE mt;
// 	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
// 	mt.majortype = MEDIATYPE_Video;
// 	mt.subtype = MEDIASUBTYPE_RGB24;
//	mt.pbFormat=(BYTE *)&bmi;
	
//	hr = m_pGrabber->SetMediaType(&mt);
	hr = m_pGrabber->SetMediaType(pmtConfig);
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Fail to set media type!"));
		return hr;
	}

	hr = m_pGB->AddFilter(pGrabBase, L"Grabber");
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Fail to put sample grabber in graph"));
		return hr;
	}

	// try to render preview/capture pin
	hr = m_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, m_pBF, pGrabBase, NULL);
	if(FAILED(hr))
		hr = m_pCapture->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, m_pBF, pGrabBase,NULL);

	if(FAILED(hr))
	{
		AfxMessageBox(_T("Can't build the graph"));
		return hr;
	}

	AM_MEDIA_TYPE mt;
	hr = m_pGrabber->GetConnectedMediaType(&mt);
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Fail to read the connected media type"));
		return hr;
	}

	vih = (VIDEOINFOHEADER*)mt.pbFormat;
	m_CB.m_lWidth = vih->bmiHeader.biWidth;
	m_CB.m_lHeight = vih->bmiHeader.biHeight;

	FreeMediaType(mt);
	hr = m_pGrabber->SetBufferSamples(FALSE);
	hr = m_pGrabber->SetOneShot(FALSE);
	hr = m_pGrabber->SetCallback(&m_CB, 1);

	//设置视频捕捉窗口
	SetupVideoWindow();

	hr = m_pMC->Run();//开始视频捕捉
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Couldn't run the graph!"));
		return hr;
	}

	m_bCaptureStart = TRUE;

	return S_OK;
}

void CCaptureVideo::StopCapture()
{
	if(m_bCaptureStart)
	{
		m_bCaptureStart = FALSE;

		ReleaseCaptureRes();
	}
}

HRESULT CCaptureVideo::InitCaptureGraphBuilder()
{
	HRESULT hr;

	// 创建IGraphBuilder接口
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGB);

	// 创建ICaptureGraphBuilder2接口
	hr = CoCreateInstance (CLSID_CaptureGraphBuilder2 , NULL, CLSCTX_INPROC, IID_ICaptureGraphBuilder2, (void**)&m_pCapture);
	if(FAILED(hr))return hr;

	m_pCapture->SetFiltergraph(m_pGB);

	hr = m_pGB->QueryInterface(IID_IMediaControl, (void**)&m_pMC);
	if (FAILED(hr))return hr;

	hr = m_pGB->QueryInterface(IID_IVideoWindow, (LPVOID*)&m_pVW);
	if (FAILED(hr))return hr;

	return hr;
}

bool CCaptureVideo::BindFilter(int deviceId, IBaseFilter **pFilter)
{
	if (deviceId < 0) return false;

	// enumerate all video capture devices
	ATL::CComPtr<ICreateDevEnum> pCreateDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,IID_ICreateDevEnum, (void**)&pCreateDevEnum);
	if(hr != NOERROR) return false;

	ATL::CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&pEm, 0);
	if(hr != NOERROR) return false;

	pEm->Reset();

	ULONG cFetched;
	IMoniker *pM;
	int index = 0;
	while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK, index <= deviceId)
	{
		IPropertyBag *pBag;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void**)&pBag);
		if(SUCCEEDED(hr))
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if (hr == NOERROR) 
			{
				if (index == deviceId)
				{
					pM->BindToObject(0, 0, IID_IBaseFilter, (void**)pFilter);
				}

				SysFreeString(var.bstrVal);
			}

			pBag->Release();
		}

		pM->Release();
		index++;
	}

	return true;
}

HRESULT CCaptureVideo::SetupVideoWindow()
{
	HRESULT hr;

	hr = m_pVW->put_Owner((OAHWND)m_hWnd);
	if (FAILED(hr))return hr;

	hr = m_pVW->put_WindowStyle(WS_CHILD|WS_CLIPCHILDREN);
	if (FAILED(hr))return hr;

	ResizeVideoWindow();
	hr = m_pVW->put_Visible(OATRUE);
	return hr;
}

void CCaptureVideo::ResizeVideoWindow()
{
	if(m_pVW)
	{
		//让图像充满整个窗口
		CRect rc;
		GetClientRect(&rc);
		m_pVW->SetWindowPosition(0, 0, rc.right, rc.bottom);
	} 
}

void CCaptureVideo::FreeMediaType(AM_MEDIA_TYPE& mt)
{
	if(mt.cbFormat != 0)
	{
		CoTaskMemFree((PVOID)mt.pbFormat);
		// Strictly unnecessary but tidier
		mt.cbFormat = 0;
		mt.pbFormat = NULL;
	}

	if(mt.pUnk != NULL) 
	{
		mt.pUnk->Release();
		mt.pUnk = NULL;
	}
}

void CCaptureVideo::UpdateMenuItemState(CMenu* pParent, UINT id, UINT nFlag)
{
	ASSERT(pParent);

	MENUITEMINFO infoItem;
	infoItem.cbSize = sizeof (MENUITEMINFO);
	infoItem.fMask = MIIM_STATE;

	VERIFY(pParent->GetMenuItemInfo(id, &infoItem));
	infoItem.fState |= nFlag;
	pParent->SetMenuItemInfo(id, &infoItem);
}

void CCaptureVideo::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
// 	CMenu menuVideo;
// 	menuVideo.LoadMenu(IDR_POPUP_VIDEO);
// 
// 	CMenu* pSubMenu = menuVideo.GetSubMenu(0);
// 	ASSERT(pSubMenu);
// 
// 	CMenu* pCameraList = pSubMenu->GetSubMenu(0);
// 	ASSERT(pCameraList);
// 
// 	CStringArray listCamera;
// 	EnumDevices(listCamera);
// 
// 	UINT iNewCnt = listCamera.GetCount();
// 	if(iNewCnt <= 0)
// 	{
// 		while(pCameraList->GetMenuItemCount() > 1)
// 			pCameraList->DeleteMenu(1, MF_BYPOSITION);
// 
// 		pCameraList->ModifyMenu(0, MF_BYPOSITION|MF_STRING|MF_GRAYED, ID_CAMERALIST_ITEM1, _T("没有可用的视频设备"));
// 	}
// 	else
// 	{
// 		UINT iOldCnt = pCameraList->GetMenuItemCount();
// 		UINT iIndex = iNewCnt, iFlag;
// 		for(; iIndex < iOldCnt; iIndex++)
// 			pCameraList->DeleteMenu(iNewCnt, MF_BYPOSITION);
// 		
// 		for(iIndex = 0; iIndex < iNewCnt; iIndex++)
// 		{
// 			iFlag = MF_STRING;
// 			iFlag |= (iIndex == m_iCameraID) ? MF_CHECKED : 0;
// 			iFlag |= m_bCaptureStart ? MF_GRAYED : 0;
// 
// 			if(iOldCnt > iIndex)
// 				pCameraList->ModifyMenu(iIndex, iFlag|MF_BYPOSITION, ID_CAMERALIST_ITEM1 + iIndex, listCamera[iIndex]);
// 			else
// 				pCameraList->AppendMenu(iFlag, ID_CAMERALIST_ITEM1 + iIndex, listCamera[iIndex]);
// 		}
// 	}
// 
// 	if(m_iCameraID > (int)iNewCnt)
// 	{
// 		m_iCameraID = -1;
// 		m_bCaptureStart = FALSE;
// 	}
// 
// 	if(m_bFullScreen)
// 		UpdateMenuItemState(pSubMenu, ID_POPMENU_FULLSCREEN, MF_CHECKED);
// 
// 	if((m_iCameraID < 0) || m_bCaptureStart)
// 		UpdateMenuItemState(pSubMenu, ID_POPMENU_CAPTURESTART, MF_GRAYED);
// 
// 	if((m_iCameraID < 0) || (!m_bCaptureStart))
// 	{
// 		UpdateMenuItemState(pSubMenu, ID_POPMENU_CAPTURESTOP, MF_GRAYED);
// 		UpdateMenuItemState(pSubMenu, ID_POPMENU_SNAPSHOT, MF_GRAYED);
// 	}
// 
// 	if(AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
// 	{
// 		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;
// 
// 		if(!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSubMenu->m_hMenu, FALSE, TRUE))
// 			return;
// 
// 		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
// 	}
// 	else
// 	{
// 		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_TOPALIGN, point.x, point.y, this);
// 	}
// 
// 	UpdateDialogControls(this, FALSE);
// 	SetFocus();
}

void CCaptureVideo::OnCameraListItem(UINT id)
{
//	m_iCameraID = id - ID_CAMERALIST_ITEM1;
}

void CCaptureVideo::OnPopmenuCapturestart()
{
	// TODO: 在此添加命令处理程序代码
	StartCapture(m_iCameraID);
}

void CCaptureVideo::OnPopmenuCapturestop()
{
	// TODO: 在此添加命令处理程序代码
	StopCapture();
}

void CCaptureVideo::OnPopmenuFullscreen()
{
	// TODO: 在此添加命令处理程序代码
// 	m_bFullScreen = !m_bFullScreen;
// 
// 	static CWnd *pOldParent;
// 	static RECT rectOldPos;
// 
// 	if(m_bFullScreen)
// 	{
// #if 0
// 		//全屏代码，目前不采用
// 
// 		GetWindowRect(&rectOldPos);
// 		pOldParent = SetParent(CWnd::GetDesktopWindow());
// 
// 		static DWORD dwOldStyle;
// 		ShowWindow(SW_HIDE);
// 		dwOldStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
// 		SetWindowLong(m_hWnd, GWL_EXSTYLE, dwOldStyle|WS_EX_TOOLWINDOW);
// 		ShowWindow(SW_SHOW);
// 
// 		int iWidth = GetSystemMetrics(SM_CXSCREEN);
// 		int iHeight = GetSystemMetrics(SM_CYSCREEN);
// 		SetWindowPos(&CWnd::wndTopMost, 0, 0, iWidth, iHeight, SWP_FRAMECHANGED);
// #endif
// 		pOldParent = GetParent();
// 		GetWindowRect(&rectOldPos);
// 
// 		CZoomInShow dlg(0, 0, m_hWnd);
// 		dlg.DoModal();
// 	}
// 	else
// 	{
// 		ASSERT(pOldParent);
// 
// 		CDialog *pDlg = (CDialog*)GetParent();
// 		ASSERT(pDlg->IsKindOf(RUNTIME_CLASS(CDialog)));
// 		pDlg->EndDialog(0);
// 
// 		SetParent(pOldParent);
// 		pOldParent->ScreenToClient(&rectOldPos);
// 		MoveWindow(&rectOldPos);
// 	}
}

void CCaptureVideo::OnPopmenuSnapshot()
{
	// TODO: 在此添加命令处理程序代码
	m_CB.m_action=m_action;

	if(m_action==0)
	{
		CFileDialog dlg(FALSE, ".bmp", NULL, OFN_OVERWRITEPROMPT,
			"BMP文件|*.bmp|所有文件|*.*|", this);
		if(dlg.DoModal() == IDOK)
		{
			m_CB.m_sFileName = dlg.GetFileName();
			m_CB.m_bSnapshot = TRUE;
		}
	}
	else if(m_action==1)
		m_CB.m_bSnapshot=TRUE;
}

void CCaptureVideo::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bFullScreen) OnPopmenuFullscreen();

	CWnd::OnLButtonDblClk(nFlags, point);
}

BOOL CCaptureVideo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_pVW && (pMsg->hwnd != m_hWnd) && (pMsg->message == WM_LBUTTONDBLCLK))
		OnLButtonDblClk(pMsg->wParam, pMsg->lParam);

	return CWnd::PreTranslateMessage(pMsg);
}

void CCaptureVideo::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	ResizeVideoWindow();
}
