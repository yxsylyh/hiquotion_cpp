// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Line.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine() : ILine()
{
	m_start.x=0;
	m_start.y=0;
	m_end.x=0;
	m_end.y=0;

	m_lineColor=RGB(0,0,0);
	m_lineStyle=PS_SOLID;
	m_lineWidth=0;

	m_srcPointCap=PS_ENDCAP_SQUARE;
	m_dstPointCap=PS_ENDCAP_SQUARE;
}

CLine::CLine(CRect rect, COLORREF color, int lineStyle, int lineWitdh, int srcCap, int dstCap)
{
	m_start=m_rect.TopLeft();
	m_end=m_rect.BottomRight();

	m_lineColor=color;
	m_lineStyle=lineStyle;
	m_lineWidth=lineWitdh;
	m_srcPointCap=srcCap;
	m_dstPointCap=dstCap;
}

CLine::CLine(CPoint src, CPoint dst, COLORREF color, int lineStyle, int lineWitdh, int srcCap, int dstCap)
{
	m_start=src;
	m_end=dst;

	m_lineColor=color;
	m_lineStyle=lineStyle;
	m_lineWidth=lineWitdh;
	m_srcPointCap=srcCap;
	m_dstPointCap=dstCap;

}

CLine::CLine(int srcx, int srcy, int dstx, int dsty, COLORREF color, int lineStyle, int lineWitdh, int srcCap, int dstCap)
{
	m_start.x=srcx;
	m_start.y=srcy;
	m_end.x=dstx;
	m_end.y=dsty;

	m_lineColor=color;
	m_lineStyle=lineStyle;
	m_lineWidth=lineWitdh;
	m_srcPointCap=srcCap;
	m_dstPointCap=dstCap;
}

CLine::~CLine()
{

}

