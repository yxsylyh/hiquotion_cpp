// Polygon.h: interface for the CPolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYGON_H__DF497E06_EF78_456C_AB93_CFE43E6A8608__INCLUDED_)
#define AFX_POLYGON_H__DF497E06_EF78_456C_AB93_CFE43E6A8608__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IShape.h"
#include <C++\FoudationLib\DataStructLib\PointerList.h>

// 填充的多边形类
class CPolygon : public IShape  
{
public:
	CPolygon();
	virtual ~CPolygon();

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

#endif // !defined(AFX_POLYGON_H__DF497E06_EF78_456C_AB93_CFE43E6A8608__INCLUDED_)
