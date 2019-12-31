// ImageConverter.cpp: implementation of the CImageConverter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageConverter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageConverter::CImageConverter()
{
	m_status=GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);
}

CImageConverter::~CImageConverter()
{
	if(m_status!=GdiplusNotInitialized)
		GdiplusShutdown(m_pGdiToken);
}

BOOL CImageConverter::isInitialized()
{
	if(m_status==Ok)
		return TRUE;
	else
		return FALSE;
}

Status CImageConverter::getStatus()
{
	return m_status;
}

CString CImageConverter::getFormatFromFileExt(CString ext)
{
	CString capExt=ext;
	capExt.MakeUpper();
// BMP、GIF、JPEG 、Exif 、PNG 、TIFF 、ICON、WMF 、EMF
	if(capExt=="BMP")
		return FMT_BMP;
	if(capExt=="GIF")
		return FMT_GIF;
	if(capExt=="JPG" || capExt=="JPEG")
		return FMT_JPG;
	if(capExt=="PNG")
		return FMT_PNG;
	if(capExt=="TIF" || capExt=="TIFF")
		return FMT_XPNG;  // ???
	if(capExt=="ICO" || capExt=="ICON")
		return FMT_XICO;
	if(capExt=="WMF" || capExt=="EMF" || capExt=="EXIF")
		return FMT_XWMF;
	
	return FMT_BMP;
}

int CImageConverter::GetImageCLSID(const WCHAR* format, CLSID* pCLSID)
{
	//得到格式为format的图像文件的编码值，访问该格式图像的COM组件的
		//GUID值保存在pCLSID中
		UINT num = 0;
		UINT size = 0;
		ImageCodecInfo* pImageCodecInfo = NULL;
		GetImageEncodersSize(&num, &size);
		
		if(size == 0)
			return FALSE; // 编码信息不可用
		
		//分配内存
		pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
		if(pImageCodecInfo == NULL)
			return FALSE; // 分配失败
		
		//获得系统中可用的编码方式的所有信息
		GetImageEncoders(num, size, pImageCodecInfo);
		
		//在可用编码信息中查找format格式是否被支持
		for(UINT i = 0; i < num; ++i)
		{ //MimeType：编码方式的具体描述
			if( wcscmp(pImageCodecInfo[i].MimeType, format) == 0 )
			{
				*pCLSID = pImageCodecInfo[i].Clsid;
				free(pImageCodecInfo);
				return TRUE;
			}
		}
		free(pImageCodecInfo);
		return FALSE;
}

WCHAR* CImageConverter::ToWChar(char *str)
{
    //在 GDI＋中，有关字符的参数类型全部都是 WCHAR 类型的
    //该函数是将传统字符串进行转换
    static WCHAR buffer[1024];
    wcsset(buffer,0);
    MultiByteToWideChar(CP_ACP,0,str,strlen(str),buffer,1024);
    return buffer;
}

// 将图像文件转换为 bmp 格式
// 返回值：
//  0：成功
// -1：目标文件扩展名为空
// -2：获取存储格式的class id失败
int CImageConverter::convertToBmp(CString srcFile, CString toFile)
{
	Image image(ToWChar((LPTSTR)(LPCSTR)srcFile));
// 	CString ext=CFileOperation::getFileExtName(toFile);
// 	if(ext=="")
// 		return -1;
	CLSID clsid;
	if(!GetImageCLSID(FMT_BMP, &clsid))
		return -2;
	
	m_status=image.Save(ToWChar((LPTSTR)(LPCSTR)toFile), &clsid, NULL);

	return 0;
}
