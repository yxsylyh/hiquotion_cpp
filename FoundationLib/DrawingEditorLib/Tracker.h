// Tracker.h: interface for the CTracker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRACKER_H__05C7D39B_A0B8_460E_ACAD_6BAB36931DC9__INCLUDED_)
#define AFX_TRACKER_H__05C7D39B_A0B8_460E_ACAD_6BAB36931DC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "Handle.h"
#include <vector>
using namespace std;

// Selected Handle Position
#define HP_NONE_SELECTED -1
#define HP_LEFT_TOP      0
#define HP_TOP           1
#define HP_RIGHT_TOP     2
#define HP_LEFT          3
#define HP_RIGHT         4
#define HP_LEFT_BOTTOM   5
#define HP_BOTTOM        6
#define HP_RIGHT_BOTTOM  7

//////////////////////////////////////////////////////////////////////////
// 对象被选中后出现的选择框

class CTracker  
{
public:
	CTracker();
	CTracker(CRect rect);
	virtual ~CTracker();

	// 属性
// 	virtual int getHandleCount();     // 获取句柄个数
// 	virtual list<CHandle> getTrackerItems();

	// 方法
	virtual void drawTracker(CDC *DC);
	virtual int isHitTracker(CPoint hitPoint);  // 点鼠标左键后，是否点中了绘制对象的Tracker上
	virtual CRect moveTrackerHandle(int nHandle, CPoint point);  // 移动Tracker的第nHandle号句柄到point点上

protected:
	CRect m_rect;
	vector<CHandle> m_handles;
};

#endif // !defined(AFX_TRACKER_H__05C7D39B_A0B8_460E_ACAD_6BAB36931DC9__INCLUDED_)
