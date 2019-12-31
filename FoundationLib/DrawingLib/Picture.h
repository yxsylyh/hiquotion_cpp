// Picture.h: interface for the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTURE_H__39525CCB_9249_4C72_AEEF_A8E53E6A71C8__INCLUDED_)
#define AFX_PICTURE_H__39525CCB_9249_4C72_AEEF_A8E53E6A71C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Rectangle.h"

// cximage.lib jasper.lib Jpeg.lib libdcr.lib png.lib Tiff.lib zlib.lib
// #ifdef _DEBUG
// #pragma comment(lib,"cximaged.lib")
// #else
#pragma comment(lib,"cximage.lib")
// #endif
#pragma comment(lib,"jasper.lib")
#pragma comment(lib,"Jpeg.lib")
#pragma comment(lib,"libdcr.lib")
#pragma comment(lib,"mng.lib")
#pragma comment(lib,"png.lib")
#pragma comment(lib,"Tiff.lib")
#pragma comment(lib,"zlib.lib")

#include <C++/FoudationLib/cxImageLib/ximage.h>

class CPicture : public CRectangle  
{
public:
	CPicture();
	CPicture(std::string path);
	virtual ~CPicture();

	// 属性
	
	// 图片路径
	std::string getPath() const { return m_path; }
	void setPath(std::string val, DWORD imageType=0);

	// 资源 ID
	void setResource(HRSRC hRes, DWORD imagetype);
	void setResource(DWORD resId, DWORD imagetype, CString catalog="Bitmap");

	// 边框宽度
	// 内部存储的数据比外面看到的大 2 倍
	virtual int getBorderWidth() const { return m_borderWidth; }
	virtual void setBorderWidth(int val) { m_borderWidth = val; }

	CxImage getPicture() const { return m_picture; }
	void setPicture(CxImage val) { m_picture = val; }

	// 方法
	void rotate(float angle);
	void rotate180();

	virtual void drawMe(CDC *pDC, CPoint point);

	int getImageWidth() const { return m_imageWidth; }
	int getImageHeight() const { return m_imageHeight; }

protected:
	std::string m_path;
	CxImage m_picture;

	int m_imageWidth;
	int m_imageHeight;
};

#endif // !defined(AFX_PICTURE_H__39525CCB_9249_4C72_AEEF_A8E53E6A71C8__INCLUDED_)
