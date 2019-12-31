// RectangleTracker.h: interface for the CRectangleTracker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLETRACKER_H__4F10C5C3_7708_4968_BBEF_8C777D43A0AC__INCLUDED_)
#define AFX_RECTANGLETRACKER_H__4F10C5C3_7708_4968_BBEF_8C777D43A0AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Tracker.h"

class CRectangleTracker : public CTracker  
{
public:
	CRectangleTracker(CRect rect);
	virtual ~CRectangleTracker();

protected:
// 	CRect m_rect;
};

#endif // !defined(AFX_RECTANGLETRACKER_H__4F10C5C3_7708_4968_BBEF_8C777D43A0AC__INCLUDED_)
