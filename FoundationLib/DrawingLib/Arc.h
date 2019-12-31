// Arc.h: interface for the CArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARC_H__07FFACD5_148F_4536_8FEF_50DE476131D1__INCLUDED_)
#define AFX_ARC_H__07FFACD5_148F_4536_8FEF_50DE476131D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ILine.h"

// 绘制椭圆上的一段弧
// 该弧由 start 和 end 点决定
// 这两点不一定在弧上
// 这两点与椭圆圆心相连的直线再与椭圆相交的交点作为弧的起点和终点
class CArc : public ILine  
{
public:
	CArc();
	CArc(int left, int top, int right, int bottom, int startx, int starty, int endx, int endy);
	CArc(int left, int top, int right, int bottom, POINT start, POINT end);
	CArc(RECT rect, int startx, int starty, int endx, int endy);
	CArc(RECT rect, POINT start, POINT end);
	virtual ~CArc();

	virtual void drawMe(CDC *pDC, CPoint point);
};

#endif // !defined(AFX_ARC_H__07FFACD5_148F_4536_8FEF_50DE476131D1__INCLUDED_)
