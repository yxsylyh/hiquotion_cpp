// RoundRectangle.cpp: implementation of the CRoundRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoundRectangle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoundRectangle::CRoundRectangle()
: CRectangle(), m_roundCenter(CPoint(5, 5))
{

}

CRoundRectangle::CRoundRectangle(int left, int top, int right, int bottom, POINT roundCenter)
: CRectangle(left, top, right, bottom), m_roundCenter(roundCenter)
{

}

CRoundRectangle::CRoundRectangle(CRect rect, POINT roundCenter)
: CRectangle(rect), m_roundCenter(roundCenter)
{

}

CRoundRectangle::~CRoundRectangle()
{

}

// 属性

int CRoundRectangle::getRoundPointX()          // 获取圆角点的水平坐标
{
	return m_roundCenter.x;
}

void CRoundRectangle::setRoundPointX(int x)    // 设置圆角点的水平坐标
{
	m_roundCenter.x=x;
}

int CRoundRectangle::getRoundPointY()          // 获取圆角点的垂直坐标
{
	return m_roundCenter.y;
}

void CRoundRectangle::setRoundPointY(int y)    // 设置圆角点的垂直坐标
{
	m_roundCenter.y=y;
}

// 方法

void CRoundRectangle::drawMe(CDC *pDC, CPoint point)
{
	CPoint p=point;
	p.Offset(m_rect.TopLeft());
	pDC->MoveTo(p);
	CRect rect(p, m_rect.Size());
	pDC->RoundRect(rect, m_roundCenter);
}

void CRoundRectangle::createRng(CPoint point)
{
	CPoint p=point;
	p.Offset(m_rect.TopLeft());
	CRect rect(p, m_rect.Size());

	if(m_rgn.GetSafeHandle())
		m_rgn.DeleteObject();

	m_rgn.CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, m_roundCenter.x, m_roundCenter.y);

}

void CRoundRectangle::move(CSize moveShift)            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
{
	m_rect.OffsetRect(moveShift);
}
