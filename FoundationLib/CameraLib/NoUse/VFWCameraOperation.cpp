// VFWCameraOperation.cpp : implementation file
//

#include "stdafx.h"
#include "VFWCameraOperation.h"
#include <math.h>
#include <C++\FoudationLib\ColorSystemLib\ColorSystemConverter.h>
#include <C++\FoudationLib\BitmapLib\BitmapOperation.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LRESULT CALLBACK OnCaptureVideoData(HWND hWnd,LPVIDEOHDR lphdr)
{
	CVFWCameraOperation *opr=(CVFWCameraOperation *)capGetUserData(hWnd);
	
	if(opr==NULL )
		return -1;

	if(opr->getVfwCallback())
		opr->getVfwCallback()->OnVideoDataReceived(lphdr);

// 	if(opr->OnVideoDataCallback)
// 		return opr->OnVideoDataCallback(opr, lphdr);
	
	return 0;
}

LRESULT CALLBACK OnCaptureAudioData(HWND hWnd,LPWAVEHDR lpWHdr)
{
	CVFWCameraOperation *opr=(CVFWCameraOperation *)capGetUserData(hWnd);
	
	if(opr==NULL )
		return -1;

	if(opr->getVfwCallback())
		opr->getVfwCallback()->OnAudioDataReceived(lpWHdr);
	
// 	if(opr->OnAudioDataCallback)
// 		return opr->OnAudioDataCallback(opr, lpWHdr);
	
	return 0;
}

LRESULT CALLBACK OnStatus(HWND hWnd, int nID, LPCSTR lpsz)
{
	CVFWCameraOperation *opr=(CVFWCameraOperation *)capGetUserData(hWnd);
	
	if(opr==NULL )
		return -1;

	if(opr->getVfwCallback())
		opr->getVfwCallback()->OnStatus(nID, lpsz);
	
// 	if(opr->OnStatusCallback)
// 		return opr->OnStatusCallback(opr, nID, lpsz);
	
	return 0;
}

LRESULT CALLBACK OnError(HWND hWnd, int nID, LPCSTR lpsz)
{
	CVFWCameraOperation *opr=(CVFWCameraOperation *)capGetUserData(hWnd);
	
	if(opr==NULL )
		return -1;

	if(opr->getVfwCallback())
		opr->getVfwCallback()->OnError(nID, lpsz);
	
// 	if(opr->OnErrorCallback)
// 		return opr->OnErrorCallback(opr, nID, lpsz);
	
	return 0;
}

// 这个设置以后，视频数据就获取不到了，不知道为什么
// LRESULT CALLBACK OnControl(HWND hWnd, int nState )
// {
// 	CVFWCameraOperation *opr=(CVFWCameraOperation *)capGetUserData(hWnd);
// 	
// 	if(opr==NULL )
// 		return -1;
// 
// 	if(opr->getVfwCallback())
// 		opr->getVfwCallback()->OnCaptureControl(nState);
// 	
// // 	if(opr->OnCaptureControlCallback)
// // 		return opr->OnCaptureControlCallback(opr, nState);
// 	
// 	return 0;
// }

/////////////////////////////////////////////////////////////////////////////
// CVFWCameraOperation

CVFWCameraOperation::CVFWCameraOperation()
{
	m_hDib=NULL;
	m_isCaptureImage=FALSE;
	m_path="";
	m_userData=NULL;

	m_vfwCallback=NULL;

	memset(&m_audioInfo, 0x00, sizeof(WAVEFORMATEX));

	m_vfwDeviceCount=0;
	memset(m_vfwDevices, 0x00, MAX_VFW_DEVICE_COUNT * sizeof(int));

// 	OnVideoDataCallback=NULL;
// 	OnAudioDataCallback=NULL;
// 	OnStatusCallback=NULL;
// 	OnErrorCallback=NULL;
// 	OnCaptureControlCallback=NULL;
}

// CVFWCameraOperation::CVFWCameraOperation(IVFWCallback *vfwCallback)
// {
// 	m_hDib=NULL;
// 	m_isCaptureImage=FALSE;
// 	m_path="";
// 	m_userData=NULL;
// 
// 	m_vfwCallback=vfwCallback;
// }


CVFWCameraOperation::~CVFWCameraOperation()
{
}


// BEGIN_MESSAGE_MAP(CVFWCameraOperation, CStatic)
// 	//{{AFX_MSG_MAP(CVFWCameraOperation)
// 		// NOTE - the ClassWizard will add and remove mapping macros here.
// 	//}}AFX_MSG_MAP
// END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVFWCameraOperation message handlers

// 	初始化
// 		创建vfw视频捕获窗口
// 		将捕获窗口关联到自身，并设置为自身的子窗口
BOOL CVFWCameraOperation::create(CWnd *pWnd, CRect *rect, BOOL visible)
{
	m_pWnd=pWnd;
	if(rect)
	{
		m_rect.left=rect->left;
		m_rect.top=rect->top;
		m_rect.right=rect->right;
		m_rect.bottom=rect->bottom;
		m_visible=visible;
	}

	UINT flag=WS_CHILD;
	if(m_visible)
		flag |= WS_VISIBLE;

	m_hWndVideo=capCreateCaptureWindow(NULL,flag,m_rect.left,m_rect.top,m_rect.Width(),m_rect.Height(),m_pWnd->GetSafeHwnd(),0);
	if(!m_hWndVideo)
		return FALSE;

	capSetUserData(m_hWndVideo, this);

	return TRUE;
}

// 获取用户Rect
CRect *CVFWCameraOperation::getUserRect()
{
	return &m_rect;
}

// 获取用户DC
HDC CVFWCameraOperation::getUserDC()
{
	return m_hdc;
}

// 获取摄像头的窗口
HWND CVFWCameraOperation::getCamaraWnd()
{
	return m_hWndVideo;
}

// 枚举摄像头驱动到摄像头驱动列表
void CVFWCameraOperation::enumCameraDrivers()
{
	char camName[MAX_PATH], ver[MAX_PATH];
	m_cameraDriverList.RemoveAll();
	m_vfwDeviceCount=0;
	for(int i=0;i<MAX_VFW_DIRVER_COUNT;i++)
	{
		if(capGetDriverDescription(i, camName, MAX_PATH, ver, MAX_PATH))
		{
			m_cameraDriverList.Add(camName);
		}
	}
}

// 枚举摄像头设备到摄像头列表
void CVFWCameraOperation::enumCameraDevices()
{
	if(!m_hWndVideo)
		return;

	for(int j=m_vfwDeviceCount;j<MAX_VFW_DEVICE_COUNT;j++)
	{
		if(connectCamera(j))
		{
			m_vfwDevices[m_vfwDeviceCount]=j;
			m_vfwDeviceCount++;
			CString devDesc;
			devDesc.Format("视频设备 #%d", m_vfwDeviceCount);
			m_cameraList.Add(devDesc);
			disconnectCamera();
		}
	}
}


// 	获取设备个数
// 		如果设备列表为空，则获取设备
// 		返回设备列表个数
int CVFWCameraOperation::getCameraDriverCount()
{
	if(m_cameraDriverList.GetSize()>0)
		return m_cameraDriverList.GetSize();

	enumCameraDrivers();

	return m_cameraDriverList.GetSize();
}

// 	获取设备列表
// 		如果设备列表为空，则枚举设备
// 		返回设备列表
void CVFWCameraOperation::getCameraDeviceList(CStringArray &cameraList)
{
	if(m_cameraDriverList.GetCount()<=0)
		enumCameraDrivers();

	if(m_cameraDriverList.GetCount()<=0)
		return;

	if(m_cameraList.GetCount()<=0)
		enumCameraDevices();

	if(m_cameraList.GetCount()<=0)
		return;

	cameraList.RemoveAll();
	for(int i=0;i<m_cameraList.GetCount();i++)
		cameraList.Add(m_cameraList.GetAt(i));
}

// 刷新摄像头列表
void CVFWCameraOperation::refreshCameraList()
{
	enumCameraDrivers();
}

// 	连接指定摄像头
BOOL CVFWCameraOperation::connectCamera(unsigned int index)
{
	if(!capDriverConnect(m_hWndVideo, index))
		return FALSE;
	else
		return TRUE;
}

// 	打开指定摄像头
BOOL CVFWCameraOperation::openCamera(unsigned int index)
{
	if(!capDriverConnect(m_hWndVideo, index))
		return FALSE;

	CAPTUREPARMS para;
	if(!getCameraParameter(&para))
		return FALSE;

	para.fAbortLeftMouse=FALSE;
	para.fAbortRightMouse=FALSE;
	para.fCaptureAudio=FALSE;
// 	para.dwRequestMicroSecPerFrame=6667;
// 	para.fMakeUserHitOKToCapture=FALSE;
	para.fYield=TRUE;     // 使用背景作业
	para.wPercentDropForError = 50;   // 允许遗失的百分比

	if(!setCameraparameter(&para))
		return FALSE;

	return TRUE;
}

// 	获取和设置窗口参数，包括是否捕获声音等等
BOOL CVFWCameraOperation::getCameraParameter(PCAPTUREPARMS para)
{
	return capCaptureGetSetup(m_hWndVideo, para, sizeof(CAPTUREPARMS));
}

BOOL CVFWCameraOperation::setCameraparameter(PCAPTUREPARMS para)
{
	return capCaptureSetSetup(m_hWndVideo, para, sizeof(CAPTUREPARMS));
}

//	获取和设置视频格式信息
BOOL CVFWCameraOperation::getVideoFormat(PBITMAPINFO pInfo)
{
	return capGetVideoFormat(m_hWndVideo, pInfo, sizeof(BITMAPINFO));
}

BOOL CVFWCameraOperation::setVideoFormat(PBITMAPINFO pInfo)
{
	return capSetVideoFormat(m_hWndVideo, pInfo, sizeof(BITMAPINFO));
}

// 获取和设置音频格式
BOOL CVFWCameraOperation::getAudioFormat(PWAVEFORMATEX pWaveInfo)
{
	return capGetAudioFormat(m_hWndVideo, pWaveInfo, sizeof(WAVEFORMATEX));
}

BOOL CVFWCameraOperation::setAudioFormat(PWAVEFORMATEX pWaveInfo)
{
	return capSetAudioFormat(m_hWndVideo, pWaveInfo, sizeof(WAVEFORMATEX));
}

// 	获取和设置视频大小（设置视频大小时，自身窗口也要跟着变化）
BOOL CVFWCameraOperation::getVideoSize(int &width, int &height)
{
	BITMAPINFO info;
	if(!capGetVideoFormat(m_hWndVideo, &info, sizeof(BITMAPINFO)))
	{
		width=0;
		height=0;
		return FALSE;
	}

	width=info.bmiHeader.biWidth;
	height=info.bmiHeader.biHeight;
	return TRUE;
}

BOOL CVFWCameraOperation::setVideoSize(int width, int height)
{
	BITMAPINFO info;
	if(!capGetVideoFormat(m_hWndVideo, &info, sizeof(BITMAPINFO)))
		return FALSE;
	
	info.bmiHeader.biWidth=width;
	info.bmiHeader.biHeight=height;

	if(!capSetVideoFormat(m_hWndVideo, &info, sizeof(BITMAPINFO)))
		return FALSE;

	return TRUE;
}

// 	捕获预览（Overlay或Preview，默认Preview）
BOOL CVFWCameraOperation::startPreview(PreviewMode mode, int rate)
{
	UINT style=GetWindowLong(m_hWndVideo, GWL_STYLE);
	style |= WS_VISIBLE;
	SetWindowLong(m_hWndVideo, GWL_STYLE, style);
    //设置预览时的比例 
	capPreviewScale(m_hWndVideo, TRUE);

    //设置预览时的帧频率 
	capPreviewRate(m_hWndVideo, rate);
	
	switch(mode)
	{
	case Overlay:
// 		capPreview(m_hWndVideo, 0);
		capOverlay(m_hWndVideo, 1);
		break;
	case Preview:
// 		capOverlay(m_hWndVideo, 0);
		capPreview(m_hWndVideo, 1);
		break;
	}
	return TRUE;
}

//	停止预览
BOOL CVFWCameraOperation::stopPreview()
{
	capOverlay(m_hWndVideo, 0);
	capPreview(m_hWndVideo, 0);
	capCaptureAbort(m_hWndVideo);  
	UINT style=GetWindowLong(m_hWndVideo, GWL_STYLE);
	style &= ~WS_VISIBLE;
	SetWindowLong(m_hWndVideo, GWL_STYLE, style);
	return TRUE;
}

// 	截取视频图像（获得BitmapInfoHeader和Bitmap数据，可以直接保存到文件的那种）
BOOL CVFWCameraOperation::captureImage(CString path)
{
	m_path=path;
	m_isCaptureImage=TRUE;

	return TRUE;
}

BOOL CVFWCameraOperation::saveImage(unsigned char *data, int dataLen)
{
	m_isCaptureImage=FALSE;

	if(m_path=="")
		return FALSE;

	int width=m_videoInfo.bmiHeader.biWidth;
	int height=m_videoInfo.bmiHeader.biHeight;

	unsigned char *dt=NULL;
	unsigned char *dtrgb=NULL;
	unsigned char *dtrgb2=NULL;
	unsigned long len=0;
	if(m_videoInfo.bmiHeader.biCompression==844715353)
	{
		// YUV2 to RGB( tested RGB to YUV420Planar, and then to RGB, test success!)

// 		dtrgb=new unsigned char[dataLen*3/2];
// 		dtrgb2=new unsigned char[dataLen*3/2];
// 		ColorSystemConverter::YUY2ToRGB(data, dtrgb, dataLen);
// 		ColorSystemConverter::Vertical(dtrgb, width, height, dtrgb2);
// 		delete dtrgb;
// 		dtrgb=NULL;
// 		dt=dtrgb2;
// 		len=dataLen*3/2;
// 
// 		unsigned char *yuv=new unsigned char[len];
// 		ColorSystemConverter::RGBToYUV420Planar(dt, width, height, yuv);
// 		unsigned char *rgb=new unsigned char[len];
// 		ColorSystemConverter::YUV420PlanarToRGB(yuv, width, height, dtrgb2);
// 
// 		delete yuv;
// 		delete rgb;
// 
// 		dt=dtrgb2;

		// tested YUV2 to YUV420Planar, and then to RGB

		unsigned char *dtyuv420=new unsigned char[dataLen];
		CColorSystemConverter::YUV2ToYUV420Planar(data, width, height, dtyuv420);
		dtrgb=new unsigned char[dataLen * 3 / 2];
		CColorSystemConverter::YUV420PlanarToRGB(dtyuv420, width, height, dtrgb);
		dtrgb2=new unsigned char[dataLen * 3 / 2];
		CColorSystemConverter::Vertical(dtrgb, width, height, dtrgb2);
 		delete dtrgb;
		delete dtyuv420;

		len=dataLen*3/2;
		
		dt=dtrgb2;
	}
	else
	{
		dt=data;
		len=dataLen;
	}

	BITMAPINFOHEADER infoHead;
	memcpy(&infoHead, &m_videoInfo.bmiHeader, sizeof(BITMAPINFOHEADER));
	if(infoHead.biCompression==844715353)
	{
		infoHead.biBitCount=24;
		infoHead.biCompression=BI_RGB;
		infoHead.biSizeImage=0;
	}
	
	if(!CBitmapOperation::saveBmp(m_path, infoHead, &m_videoInfo.bmiColors[0], dt, len))
	{
		if(dtrgb2)
			delete dtrgb2;
		return FALSE;
	}

	if(dtrgb2)
		delete dtrgb2;

	return TRUE;
}

// 开始捕获
BOOL CVFWCameraOperation::startCapture(HDC hdc, int width, int height)
{
	m_hdc=hdc;

	m_hDib=DrawDibOpen();
	if(!m_hDib)
		return FALSE;

	if(!getVideoFormat(&m_videoInfo))
		return FALSE;

	if(!getAudioFormat(&m_audioInfo))
	{
		MessageBox(0, "获取音频格式信息失败！", "", 0);
		return FALSE;
	}

	if(!DrawDibBegin(m_hDib,
				m_hdc,
				width,				// don't stretch
				height,				// don't stretch
				&m_videoInfo.bmiHeader,
				m_videoInfo.bmiHeader.biWidth,         // width of image
				m_videoInfo.bmiHeader.biHeight,        // height of image
				DDF_HURRYUP //0				
				))
		return FALSE;

	//如果要捕获视频流，则要使用函数指定不生成文件。否则将会自动生成AVI文件   
	if(!capCaptureSequenceNoFile(m_hWndVideo))
		return FALSE;

	return TRUE;
}

// 显示捕获的帧数据
BOOL CVFWCameraOperation::captureShow(unsigned char *data, int dstx, int dsty, int dstWidth, int dstHeight, int srcWidth, int srcHeight)
{
	int width=srcWidth;
	int height=srcHeight;

	if(width==-1)
		width=m_videoInfo.bmiHeader.biWidth;
	if(height==-1)
		height=m_videoInfo.bmiHeader.biHeight;

	/*********************************************************************

	DrawDib Flags

	**********************************************************************/
// #define DDF_0001            0x0001          /* ;Internal */
// #define DDF_UPDATE          0x0002          /* re-draw the last DIB */
// #define DDF_SAME_HDC        0x0004          /* HDC same as last call (all setup) */
// #define DDF_SAME_DRAW       0x0008          /* draw params are the same */
// #define DDF_DONTDRAW        0x0010          /* dont draw frame, just decompress */
// #define DDF_ANIMATE         0x0020          /* allow palette animation */
// #define DDF_BUFFER          0x0040          /* always buffer image */
// #define DDF_JUSTDRAWIT      0x0080          /* just draw it with GDI */
// #define DDF_FULLSCREEN      0x0100          /* use DisplayDib */
// #define DDF_BACKGROUNDPAL   0x0200	    /* Realize palette in background */
// #define DDF_NOTKEYFRAME     0x0400          /* this is a partial frame update, hint */
// #define DDF_HURRYUP         0x0800          /* hurry up please! */
// #define DDF_HALFTONE        0x1000          /* always halftone */
// #define DDF_2000            0x2000          /* ;Internal */
// 
// #define DDF_PREROLL         DDF_DONTDRAW    /* Builing up a non-keyframe */
// #define DDF_SAME_DIB        DDF_SAME_DRAW
// #define DDF_SAME_SIZE       DDF_SAME_DRAW

	BOOL ret=DrawDibDraw(m_hDib,
		m_hdc,
		dstx,		// dest : left pos
		dsty,		// dest : top pos
		dstWidth,					 // don't zoom x
		dstHeight,					 // don't zoom y
		&m_videoInfo.bmiHeader,			 // bmp header info
		data,					 // bmp data
// 		dstx,					 // src :left
// 		dsty,					 // src :top
		0,
		0,
		width,				 // src : width
		height,				 // src : height
		DDF_SAME_DRAW			 // use prev params....
		);

	return ret;
}

// 停止捕获
void CVFWCameraOperation::stopCapture()
{
// 	capSetCallbackOnVideoStream(m_hWndVideo, NULL);
// 	capSetCallbackOnWaveStream(m_hWndVideo, NULL);
// 	capSetCallbackOnCapControl(m_hWndVideo, NULL);
// 	capSetCallbackOnStatus(m_hWndVideo, NULL);
// 	capSetCallbackOnError(m_hWndVideo, NULL);

	if(m_hDib)
	{
		DrawDibEnd(m_hDib);
		DrawDibClose(m_hDib);
		m_hDib=NULL;
	}
	
	capCaptureStop(m_hWndVideo);
	//停止捕获   
	capCaptureAbort(m_hWndVideo);
}

// 	// 	设置视频回调函数
// 	BOOL CVFWCameraOperation::setVideoCallback(VideoDataCallback videoCallback)
// 	{
// 		OnVideoDataCallback=videoCallback;
// 		return capSetCallbackOnVideoStream(m_hWndVideo, OnCaptureVideoData);
// 	}
// 
// 	// 	设置音频回调函数
// 	BOOL CVFWCameraOperation::setAudioCallback(AudioDataCallback audioCallback)
// 	{
// 		OnAudioDataCallback=audioCallback;
// 		return capSetCallbackOnWaveStream(m_hWndVideo, OnCaptureAudioData);
// 	}
// 
// 	//	设置控制回调函数
// 	// 	typedef LRESULT (CALLBACK* CAPCONTROLCALLBACK)(HWND hWnd, int nState);
// 	BOOL CVFWCameraOperation::setControlCallback(CaptureControlCallback controlCallback)
// 	{
// 		OnCaptureControlCallback=controlCallback;
// 		return capSetCallbackOnCapControl(m_hWndVideo, OnControl);
// 	}
// 
// 	//	设置设备状态回调函数
// 	//	LRESULT CALLBACK capStatusCallback(HWND hWnd, int nID, LPCSTR lpsz);
// 	BOOL CVFWCameraOperation::setStatusCallback(StatusCallback statusCallback)
// 	{
// 		OnStatusCallback=statusCallback;
// 		return capSetCallbackOnStatus(m_hWndVideo, OnStatus);
// 	}
// 
// 	//	设置异常回调函数
// 	BOOL CVFWCameraOperation::setErrorCallback(ErrorCallback errorCallback)
// 	{
// 		OnErrorCallback=errorCallback;
// 		return capSetCallbackOnError(m_hWndVideo, OnError);
// 	}

// 	显示摄像头设备自身的属性
BOOL CVFWCameraOperation::showCameraProperty()
{
	return capDlgVideoSource(m_hWndVideo);
}

// 	capDlgVideoSource
// 	capDlgVideoFormat
int CVFWCameraOperation::showVideoSource()
{
	CAPDRIVERCAPS CapDrvCaps;
	ZeroMemory(&CapDrvCaps, sizeof(CapDrvCaps));
	if(!capDriverGetCaps(m_hWndVideo, &CapDrvCaps, sizeof (CAPDRIVERCAPS)))
		return -1;

	if(!CapDrvCaps.fHasDlgVideoSource)
		return -2;

	if(!capDlgVideoSource(m_hWndVideo))
		return -3;

	return 0;
}

BOOL CVFWCameraOperation::showVideoFormat()
{
	return capDlgVideoFormat(m_hWndVideo);
}

// 设置回调函数的接口
IVFWCallback *CVFWCameraOperation::getVfwCallback() const
{
	return m_vfwCallback;
}

void CVFWCameraOperation::setVfwCallback(IVFWCallback * val)
{
	m_vfwCallback = val;
	setVideoCallback();
	setAudioCallback();
	setStatusCallback();
	setErrorCallback();
}

// 	关闭指定摄像头
BOOL CVFWCameraOperation::closeCamera()
{
    // Disable the callback function..
	capSetCallbackOnVideoStream(m_hWndVideo, NULL);
	capSetCallbackOnWaveStream(m_hWndVideo, NULL);
	capSetCallbackOnCapControl(m_hWndVideo, NULL);
	capSetCallbackOnStatus(m_hWndVideo, NULL);
	capSetCallbackOnError(m_hWndVideo, NULL);
	
	Sleep(300);		// This delay is important...
	
	//将捕获窗同驱动器断开   
	return capDriverDisconnect(m_hWndVideo);
}

BOOL CVFWCameraOperation::disconnectCamera()
{
	return capDriverDisconnect(m_hWndVideo);
}

// 	设置视频回调函数
// 	typedef LRESULT (CALLBACK* CAPVIDEOCALLBACK)  (HWND hWnd, LPVIDEOHDR lpVHdr);
BOOL CVFWCameraOperation::setVideoCallback()
{
	return capSetCallbackOnVideoStream(m_hWndVideo, OnCaptureVideoData);
}

// 	设置音频回调函数
// 	typedef LRESULT (CALLBACK* CAPWAVECALLBACK)   (HWND hWnd, LPWAVEHDR lpWHdr);
BOOL CVFWCameraOperation::setAudioCallback()
{
	return capSetCallbackOnWaveStream(m_hWndVideo, OnCaptureAudioData);
}

//	设置控制回调函数
// 这个设置以后，视频数据就获取不到了，不知道为什么
// 	typedef LRESULT (CALLBACK* CAPCONTROLCALLBACK)(HWND hWnd, int nState);
// BOOL CVFWCameraOperation::setControlCallback()
// {
// 	return capSetCallbackOnCapControl(m_hWndVideo, OnControl);
// }

//	设置设备状态回调函数
//	LRESULT CALLBACK capStatusCallback(HWND hWnd, int nID, LPCSTR lpsz);
BOOL CVFWCameraOperation::setStatusCallback()
{
	return capSetCallbackOnStatus(m_hWndVideo, OnStatus);
}

//	设置异常回调函数
//	LRESULT CALLBACK capErrorCallback(HWND hWnd, int nID, LPCSTR lpsz);
BOOL CVFWCameraOperation::setErrorCallback()
{
	return capSetCallbackOnError(m_hWndVideo, OnError);
}
