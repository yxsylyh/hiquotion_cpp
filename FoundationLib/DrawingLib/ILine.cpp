// ILine.cpp: implementation of the ILine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ILine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ILine::ILine()
: oldPen(NULL)
{
	m_start.x=0;
	m_start.y=0;
	m_end.x=0;
	m_end.y=0;
	
	m_lineColor=RGB(0,0,0);
	m_lineStyle=PS_SOLID;
	m_lineWidth=0;
	
	m_srcPointCap=PS_ENDCAP_SQUARE;
	m_dstPointCap=PS_ENDCAP_SQUARE;
}

ILine::~ILine()
{

}

// 属性

CPoint ILine::getFirstPoint()
{
	return m_start;
}

CPoint ILine::getSrc()     // 获取起点
{
	return m_start;
}

CPoint ILine::getDst()     // 获取终点
{
	return m_end;
}

// 获取和设置起点、终点的横纵坐标
int ILine::getX1()
{
	return m_start.x;
}

void ILine::setX1(int x1)
{
	m_start.x=x1;
}

int ILine::getY1()
{
	return m_start.y;
}

void ILine::setY1(int y1)
{
	m_start.y=y1;
}

int ILine::getX2()
{
	return m_end.x;
}

void ILine::setX2(int x2)
{
	m_end.x=x2;
}

int ILine::getY2()
{
	return m_end.y;
}

void ILine::setY2(int y2)
{
	m_end.y=y2;
}

// 设置线条的两个端点
void ILine::setPoints(CPoint src,CPoint dst)
{
	m_start.x=src.x;
	m_start.y=src.y;
	m_end.x=dst.x;
	m_end.y=dst.y;
}


// 方法

void ILine::preparePen(CDC *pDC)  // 在绘图前，先准备好笔
{
	// PS_ENDCAP_ROUND 表示圆点
	pen.CreatePen(m_lineStyle|PS_GEOMETRIC|m_srcPointCap|m_dstPointCap,m_lineWidth, m_lineColor);
	CPen *oldPen=pDC->SelectObject(&pen);
}

void ILine::restorePen(CDC *pDC)  // 绘图之后，恢复原来的笔
{
	if(oldPen)
	{
		pDC->SelectObject(oldPen);
		oldPen=NULL;
	}

	if(pen.GetSafeHandle())
		pen.DeleteObject();
}

void ILine::draw(CDC *pDC, CPoint point)
{
	preparePen(pDC);

	drawMe(pDC, point);
	
	restorePen(pDC);
}

void ILine::drawMe(CDC *pDC, CPoint point)
{
	CPoint src=m_start;
	CPoint dst=m_end;
	src.Offset(point);
	dst.Offset(point);

	pDC->MoveTo(src);
	pDC->LineTo(dst);
}

void ILine::move(CSize moveShift)            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
{
	m_start.x+=moveShift.cx;
	m_start.y+=moveShift.cy;
	
	m_end.x+=moveShift.cx;
	m_end.y+=moveShift.cy;
}
