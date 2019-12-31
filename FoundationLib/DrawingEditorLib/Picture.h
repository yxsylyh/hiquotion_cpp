// Picture.h: interface for the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICTURE_H__39525CCB_9249_4C72_AEEF_A8E53E6A71C8__INCLUDED_)
#define AFX_PICTURE_H__39525CCB_9249_4C72_AEEF_A8E53E6A71C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "Rectangle.h"

// cximage.lib jasper.lib Jpeg.lib libdcr.lib png.lib Tiff.lib zlib.lib
#pragma comment(lib,"cxImage\\cximage.lib")
#pragma comment(lib,"cxImage\\jasper.lib")
#pragma comment(lib,"cxImage\\Jpeg.lib")
#pragma comment(lib,"cxImage\\libdcr.lib")
#pragma comment(lib,"cxImage\\png.lib")
#pragma comment(lib,"cxImage\\Tiff.lib")
#pragma comment(lib,"cxImage\\zlib.lib")

#include <ximage.h>

class CPicture : public CRectangle  
{
public:
	CPicture();
	virtual ~CPicture();

	// 属性
	
	virtual string getType();                     // 获取绘制对象的类型

	// 图片路径
	string getPath() const { return m_path; }
	void setPath(string val);

	// 边框宽度
	// 内部存储的数据比外面看到的大 2 倍
	virtual int getBorderWidth() const { return m_borderWidth; }
	virtual void setBorderWidth(int val) { m_borderWidth = val; }

	// 方法

	virtual void draw(CDC *pDC);                // 屏幕上绘制

	virtual void Serialize(CArchive &ar);
	
protected:
	DECLARE_SERIAL(CPicture);

	string m_path;
	CxImage m_image;
};

#endif // !defined(AFX_PICTURE_H__39525CCB_9249_4C72_AEEF_A8E53E6A71C8__INCLUDED_)
