// Picture.cpp: implementation of the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "Picture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4786)

IMPLEMENT_SERIAL(CPicture, CRectangle, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPicture::CPicture()
{

}

CPicture::~CPicture()
{

}

// 属性

string CPicture::getType()                   // 获取绘制对象的类型
{
	return "CPicture";
}

void CPicture::setPath(string val)
{
	m_path = val;
	if(val=="")
	{
		m_image.Clear();
		m_image.Destroy();
	}
	else
	{
		m_image.Load(m_path.c_str());
// 		if(m_image.IsValid())
// 		{
// 			if (m_image.GetTransIndex() != 24)
// 			{
// 				m_image.IncreaseBpp(24);
// 			}
// 			m_image.SetTransIndex(0);
// 			m_image.SetTransColor(m_image.GetPixelColor(1,1));
// 		}
	}
}

// 方法

void CPicture::draw(CDC *pDC)                // 屏幕上绘制
{
	CRectangle::draw(pDC);
	
	CRect rect=m_rect;
	rect.DeflateRect(CSize(1,1));
	if(m_image.IsValid())
	{
		m_image.Draw2(pDC->GetSafeHdc(),rect);
// 		FILE* hFile;
// 		hFile = fopen(m_path.c_str(),"w+b");

// 		m_image.Encode(hFile,true);
	}
}

void CPicture::Serialize(CArchive &ar)
{
	CRectangle::Serialize(ar);
	if (ar.IsStoring())
	{
		CString s=m_path.c_str();
		ar << s;
	}
	else
	{
		// get the document back pointer from the archive
		CString s="";
		ar >> s;
		if(s!="")
			setPath(s.GetBuffer(s.GetLength()));
	}
	
}
