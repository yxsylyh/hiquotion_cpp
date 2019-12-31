// Picture.cpp: implementation of the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Picture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4786)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPicture::CPicture()
: CRectangle(), m_path("")
{
	CContainer::m_borderStyle=-1; // 默认情况下，图片不需要边框
}

CPicture::CPicture(std::string path)
: CRectangle(), m_path(path)
{
	if(m_path.size()>0)
		m_picture.Load((LPTSTR)m_path.c_str());
}

CPicture::~CPicture()
{

}

// 属性

void CPicture::setPath(std::string val, DWORD imageType)
{
	m_path = val;
	if(val.size()<=0)
	{
		m_picture.Clear();
		m_picture.Destroy();
	}
	else
	{
		bool ret=m_picture.Load((char *)m_path.c_str(), imageType);
		m_imageWidth=m_picture.GetWidth();
		m_imageHeight=m_picture.GetHeight();
	}
}

// 资源 ID
void CPicture::setResource(HRSRC hRes, DWORD imagetype)
{
	m_picture.LoadResource(hRes, imagetype);
}


void CPicture::setResource(DWORD resId, DWORD imagetype, CString catalog/*="Bitmap"*/)
{
	HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(resId), catalog/*"GIF"*/);
	if(!hRsrc)
		return;

	m_picture.LoadResource(hRsrc, imagetype);
}

// 方法

void CPicture::rotate(float angle)
{
	if(m_picture.IsValid())
		m_picture.Rotate(angle);
}

void CPicture::rotate180()
{
	if(m_picture.IsValid())
		m_picture.Rotate180();
}

void CPicture::drawMe(CDC *pDC, CPoint point)
{
	CContainer::drawMe(pDC, point);

	CPoint p=point;
	p.Offset(m_rect.TopLeft());
	
	pDC->MoveTo(p);
	CRect rect(p, m_rect.Size());
	rect.DeflateRect(CSize(1,1));

	if(m_picture.IsValid())
// 		m_picture.Stretch(pDC->GetSafeHdc(), rect);  // Stretch 方法不能实现透明图片的绘制
		m_picture.Draw2(pDC->GetSafeHdc(), rect);    // 可以实现透明图片的绘制，透明图标立马透明了
}	
