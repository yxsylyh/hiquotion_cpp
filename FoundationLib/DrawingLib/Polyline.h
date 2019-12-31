// Polygram.h: interface for the CPolygram class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYGRAM_H__DB352AEB_F352_4CB1_BE06_64E734E2E04C__INCLUDED_)
#define AFX_POLYGRAM_H__DB352AEB_F352_4CB1_BE06_64E734E2E04C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Line.h"
#include <C++\FoudationLib\DataStructLib\PointerList.h>

// 折线类
class CPolyline : public CLine
{
public:
	CPolyline();
	virtual ~CPolyline();

	void addPoint(POINT point);
	void addPoint(POINT point, int indexAfter);  // 在索引 indexAfter 之后添加 point

	CPoint *getPoint(int index);
	int getPointIndex(CPoint *point);

	void removePoint(CPoint *point);
	void removePoint(int index);
	
	void movePoint(CPoint *from, POINT to);
	void movePoint(int index, POINT to);

	virtual void drawMe(CDC *pDC, CPoint point);

protected:
	CPointerList<CPoint *> m_pointList;
};

#endif // !defined(AFX_POLYGRAM_H__DB352AEB_F352_4CB1_BE06_64E734E2E04C__INCLUDED_)
