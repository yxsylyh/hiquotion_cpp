// ImageConverter.h: interface for the CImageConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGECONVERTER_H__8913A583_388D_46D3_BF9B_751DBC26A5C2__INCLUDED_)
#define AFX_IMAGECONVERTER_H__8913A583_388D_46D3_BF9B_751DBC26A5C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++/FoudationLib/ImageLib/include.h>

/*
	图像转换类

	支持 BMP、GIF、JPEG 、Exif 、PNG 、TIFF 、ICON、WMF 、EMF 格式互转

*/
/*
	用法：

	在 stdafx.h 中添加如下内容：

	// #include <afxdtctl.h>
	#define ULONG_PTR ULONG
	#include <GDIPlus/Includes/gdiplus.h>
	using namespace Gdiplus;
	#pragma comment(lib, "gdiplus.lib")

	注意：这些内容需要在 std 命名空间之前添加，否则会出现“类模板需要模板参数列表”的错误提示，不能编译通过。

	
*/
/*
	image/bmp
	image/gif
	image/jpeg
	image/pjpeg
	image/png
	image/x-icon
	image/x-jg
	image/x-png
	image/x-wmf
*/

#define FMT_BMP L"image/bmp"
#define FMT_GIF L"image/gif";
#define FMT_JPG L"image/jpeg";
#define FMT_PJPG L"image/pjpeg"
#define FMT_PNG L"image/png"
#define FMT_XICO L"image/x-icon"
#define FMT_XJG L"image/x-jg"
#define FMT_XPNG L"image/x-png"
#define FMT_XWMF L"image/x-wmf"

class CImageConverter  
{
public:
	CImageConverter();
	virtual ~CImageConverter();

	BOOL isInitialized();
	Status getStatus();

	// 将图像文件转换为 bmp 格式
	// 返回值：
	//  0：成功
	// -1：目标文件扩展名为空
	// -2：获取存储格式的class id失败
	int convertToBmp(CString srcFile, CString toFile);

protected:
	CString getFormatFromFileExt(CString ext);
	int GetImageCLSID(const WCHAR* format, CLSID* pCLSID);
	WCHAR* ToWChar(char *str);

protected:
	GdiplusStartupInput m_gdiplusStartupInput;
    ULONG_PTR m_pGdiToken;

	Status m_status;

};

#endif // !defined(AFX_IMAGECONVERTER_H__8913A583_388D_46D3_BF9B_751DBC26A5C2__INCLUDED_)
