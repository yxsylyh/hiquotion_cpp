// RoundRectangleTracker.cpp: implementation of the CRoundRectangleTracker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "RoundRectangleTracker.h"
#include "Handle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoundRectangleTracker::CRoundRectangleTracker(CRect rect, POINT roundCenter, BOOL isDrawRoundHandle)
: CRectangleTracker(rect)
{
	m_roundCenter=roundCenter;

	if(isDrawRoundHandle)
	{
		CHandle m_roundCenterHandle(rect.TopLeft()+roundCenter);
		CRectangleTracker::m_handles.push_back(m_roundCenterHandle);
	}
}

CRoundRectangleTracker::~CRoundRectangleTracker()
{

}

// 方法
// void CRoundRectangleTracker::drawTracker(CDC *DC)
// {
// 	// 父类先画
// 	CRectangleTracker::drawTracker(DC);
// 
// 	// 再画圆角的 Handle
// 
// }
