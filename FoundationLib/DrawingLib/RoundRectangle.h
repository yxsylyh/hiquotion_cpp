// RoundRectangle.h: interface for the CRoundRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROUNDRECTANGLE_H__E5C1589D_D9CE_43B3_9B3B_5179852E340F__INCLUDED_)
#define AFX_ROUNDRECTANGLE_H__E5C1589D_D9CE_43B3_9B3B_5179852E340F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "Rectangle.h"

class CRoundRectangle : public CRectangle
{
public:
	CRoundRectangle();
	CRoundRectangle(int left, int top, int right, int bottom, POINT roundCenter=CPoint(15,15));
	CRoundRectangle(CRect rect, POINT roundCenter=CPoint(5,5));
	virtual ~CRoundRectangle();

	// 属性
	
	int getRoundPointX();          // 获取圆角点的水平坐标
	void setRoundPointX(int x);    // 设置圆角点的水平坐标

	int getRoundPointY();          // 获取圆角点的垂直坐标
	void setRoundPointY(int y);    // 设置圆角点的垂直坐标

	// 方法
	virtual void drawMe(CDC *pDC, CPoint point);
	void move(CSize moveShift);            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点

protected:
	virtual void createRng(CPoint point);

private:
	POINT m_roundCenter;
};

#endif // !defined(AFX_ROUNDRECTANGLE_H__E5C1589D_D9CE_43B3_9B3B_5179852E340F__INCLUDED_)
