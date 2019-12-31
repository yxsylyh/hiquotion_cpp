// ShapeObj.cpp: implementation of the CShapeObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "ShapeObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CShapeObj, CDrawnObj, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShapeObj::CShapeObj()
{
	m_backColor=RGB(255,255,255);
	m_fillStyle=BS_SOLID;
	m_borderColor=RGB(0,0,0);
	m_borderStyle=PS_SOLID;
	m_borderWidth=1;
}

CShapeObj::CShapeObj(CRect rect) : CDrawnObj(rect)
{

}

CShapeObj::~CShapeObj()
{

}

void CShapeObj::Serialize(CArchive &ar)
{
	CDrawnObj::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_backColor;
		ar << m_fillStyle;
		ar << m_borderColor;
		ar << m_borderStyle;
		ar << m_borderWidth;
	}
	else
	{
		// get the document back pointer from the archive
		ar >> m_backColor;
		ar >> m_fillStyle;
		ar >> m_borderColor;
		ar >> m_borderStyle;
		ar >> m_borderWidth;

	}

}
