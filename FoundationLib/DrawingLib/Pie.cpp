// Pie.cpp: implementation of the CPie class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Figure.h"
#include "Pie.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPie::CPie()
: IShape(0, 0, 10, 10)
{
	m_start.x=0;
	m_start.y=0;
	
	m_end.x=10;
	m_end.y=10;
}

CPie::CPie(int left, int top, int right, int bottom, int startx, int starty, int endx, int endy)
: IShape(left, top, right, bottom)
{
	m_start.x=startx;
	m_start.y=starty;
	
	m_end.x=endx;
	m_end.y=endy;
}

CPie::CPie(int left, int top, int right, int bottom, POINT start, POINT end)
: IShape(left, top, right, bottom)
{
	m_start.x=start.x;
	m_start.y=start.y;
	
	m_end.x=end.x;
	m_end.y=end.y;
}

CPie::CPie(RECT rect, int startx, int starty, int endx, int endy)
: IShape(rect)
{
	m_start.x=startx;
	m_start.y=starty;
	
	m_end.x=endx;
	m_end.y=endy;
}

CPie::CPie(RECT rect, POINT start, POINT end)
: IShape(rect)
{
	m_start.x=start.x;
	m_start.y=start.y;
	
	m_end.x=end.x;
	m_end.y=end.y;
}

CPie::~CPie()
{

}

// ·½·¨
void CPie::setPoints(POINT start, POINT end)
{
	m_start.x=start.x;
	m_start.y=start.y;
	
	m_end.x=end.x;
	m_end.y=end.y;
}

void CPie::drawMe(CDC *pDC, CPoint point)
{
	CPoint p=point;
	p.Offset(m_rect.TopLeft());
	CPoint start=m_start;
	start.Offset(point);
	CPoint end=m_end;
	end.Offset(point);
	pDC->MoveTo(p);
	CRect rect(p, m_rect.Size());
	pDC->Pie(&rect, start, end);
}
