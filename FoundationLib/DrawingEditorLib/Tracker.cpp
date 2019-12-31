// Tracker.cpp: implementation of the CTracker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawFigure.h"
#include "Tracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTracker::CTracker()
{
	
}

CTracker::CTracker(CRect rect) : m_rect(rect)
{

}

CTracker::~CTracker()
{

}

// 属性
// int CTracker::getHandleCount()     // 获取句柄个数
// {
// 	return m_handles.size();
// }
// 
// list<CHandle> CTracker::getTrackerItems()
// {
// 	return m_handles;
// }

// 方法
void CTracker::drawTracker(CDC *DC)
{
	if(m_handles.size()>0)
	{
		vector<CHandle>::iterator handlePosition;
		for(handlePosition=m_handles.begin();handlePosition!=m_handles.end();handlePosition++)
		{
			(*handlePosition).drawHandle(DC);
		}
	}
}

// 点鼠标左键后，是否点中了绘制对象的Tracker上
int CTracker::isHitTracker(CPoint hitPoint)
{
	if(m_handles.size()<=0)
		return -1;
	for(int i=0;i<m_handles.size();i++)
	{
		if(m_handles[i].getHandleRect().PtInRect(hitPoint))
			return i;
	}
	return -1;
}

// 移动Tracker的第nHandle号句柄到point点上
CRect CTracker::moveTrackerHandle(int nHandle, CPoint point)
{
	CRect rect(m_rect);
	switch(nHandle)
	{
	case HP_LEFT_TOP:
		rect.left=point.x;
		rect.top=point.y;
		break;
	case  HP_TOP:
		rect.top=point.y;
		break;
	case  HP_RIGHT_TOP:
		rect.top=point.y;
		rect.right=point.x;
		break;
	case  HP_RIGHT:
		rect.right=point.x;
		break;
	case  HP_RIGHT_BOTTOM:
		rect.right=point.x;
		rect.bottom=point.y;
		break;
	case  HP_BOTTOM:
		rect.bottom=point.y;
		break;
	case  HP_LEFT_BOTTOM:
		rect.left=point.x;
		rect.bottom=point.y;
		break;
	case  HP_LEFT:
		rect.left=point.x;
		break;
	}

	return rect;
}
