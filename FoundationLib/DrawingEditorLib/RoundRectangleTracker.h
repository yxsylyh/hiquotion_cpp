// RoundRectangleTracker.h: interface for the CRoundRectangleTracker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROUNDRECTANGLETRACKER_H__DEB732CE_5529_4439_9116_F176C1C48E16__INCLUDED_)
#define AFX_ROUNDRECTANGLETRACKER_H__DEB732CE_5529_4439_9116_F176C1C48E16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RectangleTracker.h"

class CRoundRectangleTracker : public CRectangleTracker  
{
public:
	CRoundRectangleTracker(CRect rect, POINT roundCenter, BOOL isDrawRoundHandle=FALSE);
	virtual ~CRoundRectangleTracker();

	// ·½·¨
//	virtual void drawTracker(CDC *DC);

protected:
	POINT m_roundCenter;
};

#endif // !defined(AFX_ROUNDRECTANGLETRACKER_H__DEB732CE_5529_4439_9116_F176C1C48E16__INCLUDED_)
