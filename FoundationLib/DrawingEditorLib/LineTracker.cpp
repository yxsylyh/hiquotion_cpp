// LineTracker.cpp: implementation of the CLineTracker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "LineTracker.h"
#include "Handle.h"
#include "Tracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLineTracker::CLineTracker(CRect rect) : CTracker(rect)
{
	m_src.x=rect.TopLeft().x-Default_Handle_Sizex;
	m_src.y=rect.TopLeft().y-Default_Handle_Sizey;

	m_dst.x=rect.BottomRight().x+Default_Handle_Sizex;
	m_dst.y=rect.BottomRight().y+Default_Handle_Sizey;
}

CLineTracker::CLineTracker(POINT src, POINT dst)
{
	if(src.x<dst.x)
	{
		m_src.x=src.x-Default_Handle_Sizex;
		m_dst.x=dst.x;
	}
	else if(src.x>dst.x)
	{
		m_src.x=src.x;
		m_dst.x=dst.x-Default_Handle_Sizex;
	}
	else
	{
		m_src.x=src.x-Default_Handle_Sizex/2;
		m_dst.x=dst.x-Default_Handle_Sizex/2;
	}

	if(src.y<dst.y)
	{
		m_src.y=src.y-Default_Handle_Sizey;
		m_dst.y=dst.y;
	}
	else if(src.y>dst.y)
	{
		m_src.y=src.y;
		m_dst.y=dst.y-Default_Handle_Sizey;
	}
	else
	{
		m_src.y=src.y-Default_Handle_Sizey/2;
		m_dst.y=dst.y-Default_Handle_Sizey/2;
	}

	CHandle handlesrc(m_src);
	m_handles.push_back(handlesrc);
	CHandle handledst(m_dst);
	m_handles.push_back(handledst);
}

CLineTracker::~CLineTracker()
{

}

// 点鼠标左键后，是否点中了绘制对象的Tracker上
///////////////////////无法调用到这个方法，就不用了////////////////////////////
// int CLineTracker::isHitTracker(CPoint hitPoint)
// {
// 	if(m_handles[1].getHandleRect().PtInRect(hitPoint))
// 		return HP_RIGHT_BOTTOM;
// 
// 	return CTracker::isHitTracker(hitPoint);
// }

// 移动Tracker的第nHandle号句柄到point点上
// CRect CLineTracker::moveTrackerHandle(int nHandle, CPoint point)
// {
// 	CRect rect=CTracker::moveTrackerHandle(nHandle,point);
// 	
// 	return rect;
// }
