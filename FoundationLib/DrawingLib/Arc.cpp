// Arc.cpp: implementation of the CArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Figure.h"
#include "Arc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArc::CArc()
{
	m_rect.left=0;
	m_rect.top=0;
	m_rect.right=10;
	m_rect.bottom=10;

	m_start.x=0;
	m_start.y=0;

	m_end.x=10;
	m_end.y=10;
}

CArc::CArc(int left, int top, int right, int bottom, int startx, int starty, int endx, int endy)
{
	m_rect.left=left;
	m_rect.top=top;
	m_rect.right=right;
	m_rect.bottom=bottom;
	
	m_start.x=startx;
	m_start.y=starty;
	
	m_end.x=endx;
	m_end.y=endy;
}

CArc::CArc(int left, int top, int right, int bottom, POINT start, POINT end)
{
	m_rect.left=left;
	m_rect.top=top;
	m_rect.right=right;
	m_rect.bottom=bottom;
	
	m_start.x=start.x;
	m_start.y=start.y;
	
	m_end.x=end.x;
	m_end.y=end.y;
}

CArc::CArc(RECT rect, int startx, int starty, int endx, int endy)
{
	m_rect.left=rect.left;
	m_rect.top=rect.top;
	m_rect.right=rect.right;
	m_rect.bottom=rect.bottom;
	
	m_start.x=startx;
	m_start.y=starty;
	
	m_end.x=endx;
	m_end.y=endy;
}

CArc::CArc(RECT rect, POINT start, POINT end)
{
	m_rect.left=rect.left;
	m_rect.top=rect.top;
	m_rect.right=rect.right;
	m_rect.bottom=rect.bottom;
	
	m_start.x=start.x;
	m_start.y=start.y;
	
	m_end.x=end.x;
	m_end.y=end.y;
}

CArc::~CArc()
{

}

void CArc::drawMe(CDC *pDC, CPoint point)
{
	if(point.x==0 && point.y==0)
	{
		pDC->Arc(&m_rect, m_start, m_end);
	}
	else
	{
		CPoint p=point;
		p.Offset(m_rect.TopLeft());
		CPoint start=m_start;
		start.Offset(m_rect.TopLeft());
		CPoint end=m_end;
		end.Offset(m_rect.TopLeft());
		pDC->MoveTo(p);
		CRect rect(p, m_rect.Size());
		
		pDC->Arc(&rect, start, end);
	}
}
