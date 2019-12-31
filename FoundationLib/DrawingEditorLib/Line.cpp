// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "Line.h"
#include "LineTracker.h"
#include <math.h>
#include "SystemPropertyLoader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4786)

IMPLEMENT_SERIAL(CLine, CLineObj, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine() : CLineObj()
{
	m_src.x=0;
	m_src.y=0;
	m_dst.x=0;
	m_dst.y=0;

	m_properties=new CLinePropertySet(this);
}

CLine::CLine(CRect rect) : CLineObj(rect)
{
	m_src=m_rect.TopLeft();
	m_dst=m_rect.BottomRight();
	
	m_properties=new CLinePropertySet(this);
}

CLine::CLine(POINT src, POINT dst)
{
	m_src=src;
	m_dst=dst;

	CRect rc(min(m_src.x,m_dst.x),min(m_src.y,m_dst.y),
		     max(m_src.x,m_dst.x),max(m_src.y,m_dst.y));
	CDrawnObj::setRect(rc);
	
	m_properties=new CLinePropertySet(this);
}

CLine::~CLine()
{
	if(m_properties)
		delete m_properties;
}

// 属性

string CLine::getType()                   // 获取绘制对象的类型
{
	return "CLine";
}

POINT CLine::getSrc()     // 获取起点
{
	return m_src;
}

POINT CLine::getDst()     // 获取终点
{
	return m_dst;
}

// 获取和设置起点、终点的横纵坐标
int CLine::getX1()
{
	return m_src.x;
}

void CLine::setX1(int x1)
{
	m_src.x=x1;
}

int CLine::getY1()
{
	return m_src.y;
}

void CLine::setY1(int y1)
{
	m_src.y=y1;
}

int CLine::getX2()
{
	return m_dst.x;
}

void CLine::setX2(int x2)
{
	m_dst.x=x2;
}

int CLine::getY2()
{
	return m_dst.y;
}

void CLine::setY2(int y2)
{
	m_dst.y=y2;
}

CTracker CLine::getTracker()   // 获取选中框
{
	CLineTracker lineTracker(m_src,m_dst);
	return lineTracker;
}

// 根据矩形的左上角和右下角点，确定直线的两个端点位置
void CLine::setPoints(CPoint oldPoint,CPoint newPoint)
{
	m_src.x=oldPoint.x;
	m_src.y=oldPoint.y;
	m_dst.x=newPoint.x;
	m_dst.y=newPoint.y;
}


// 方法

void CLine::draw(CDC *pDC)                // 屏幕上绘制
{
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = m_lineColor;


	CPen pen;
	// PS_ENDCAP_ROUND 表示圆点
// 	pen.CreatePen(m_lineStyle|PS_GEOMETRIC|PS_ENDCAP_ROUND, 2, &logBrush);
	pen.CreatePen(m_lineStyle|PS_GEOMETRIC|PS_ENDCAP_SQUARE,m_lineWidth, &logBrush);
	CPen *oldPen=pDC->SelectObject(&pen);

	pDC->MoveTo(m_src);
	pDC->LineTo(m_dst);

	pDC->SelectObject(oldPen);

}

// 在创建绘制对象的时候绘制（如果draw绘制很复杂，在创建绘制对象的时候，用这个方法简化绘制，以提高动态绘制的效率）
void CLine::drawOnCreating(CDC *pDC)
{
	draw(pDC);
}

BOOL CLine::isHitMe(CPoint hitPoint)      // 点鼠标左键后，是否点中了该绘制对象
{
	float ab=0.0,ca=0.0,cb=0.0;
	ab=sqrt((m_src.x-m_dst.x)*(m_src.x-m_dst.x)+(m_src.y-m_dst.y)*(m_src.y-m_dst.y));
	ca=sqrt((hitPoint.x-m_src.x)*(hitPoint.x-m_src.x)+(hitPoint.y-m_src.y)*(hitPoint.y-m_src.y));
	cb=sqrt((hitPoint.x-m_dst.x)*(hitPoint.x-m_dst.x)+(hitPoint.y-m_dst.y)*(hitPoint.y-m_dst.y));
	if(ca+cb-ab<0.05)
		return TRUE;
	else
		return FALSE;
}

void CLine::move(CSize moveShift)            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
{
	m_src.x+=moveShift.cx;
	m_src.y+=moveShift.cy;
	
	m_dst.x+=moveShift.cx;
	m_dst.y+=moveShift.cy;
}

void CLine::moveHandle(int nHandle, CPoint point)  // 移动绘制对象Tracker的第nHandle号句柄到point点上
{
	if(nHandle==1)
		nHandle=HP_RIGHT_BOTTOM;

	CRect rect=getTracker().moveTrackerHandle(nHandle,point);
	
	if(nHandle==HP_LEFT_TOP)
	{
		m_src=rect.TopLeft();
	}
	else if(nHandle==HP_RIGHT_BOTTOM)
	{
		m_dst=rect.BottomRight();
	}

}

// 判断该直线是否与指定的矩形相交
BOOL CLine::intersection(CRect rc)
{
	// 首先，如果线段的两个端点中的一个，在矩形内，则说明相交
	if(rc.PtInRect(m_src) || rc.PtInRect(m_dst))
		return TRUE;

	CPoint p1(rc.TopLeft()),
		p2(rc.left,rc.bottom),
		p3(rc.BottomRight()),
		p4(rc.right,rc.top);

	if(intersectionTwoLines(m_src,m_dst,p1,p2)
		|| intersectionTwoLines(m_src,m_dst,p2,p3)
		|| intersectionTwoLines(m_src,m_dst,p3,p4)
		|| intersectionTwoLines(m_src,m_dst,p4,p1))
		return TRUE;
	else
		return FALSE;
}
// 判断两个线段是否相交
BOOL CLine::intersectionTwoLines(CPoint line1P1,CPoint line1P2,CPoint line2P1,CPoint line2P2)
{
// 	X1 = Line1.X1: X2 = Line1.X2: Y1 = Line1.Y1: Y2 = Line1.Y2
// 	A1 = Line2.X1: A2 = Line2.X2: B1 = Line2.Y1: B2 = Line2.Y2
// 	a = F(X1, Y1, X2, Y2, A1, B1)
// 	b = F(X1, Y1, X2, Y2, A2, B2)
// 	If a * b = 0 Then
// 		Print "两直线有交叉。"
// 	ElseIf a * b > 0 Then
// 		Print "两直线没有交叉。"
// 	Else
// 		a = F(A1, B1, A2, B2, X1, Y1)
// 		b = F(A1, B1, A2, B2, X2, Y2)
// 		If a * b <= 0 Then
// 			Print "两直线有交叉。"
// 		Else
// 			Print "两直线没有交叉。"
// 		End If
// 	End If
	int x1=line1P1.x,
		y1=line1P1.y,
		x2=line1P2.x,
		y2=line1P2.y,

		a1=line2P1.x,
		b1=line2P1.y,
		a2=line2P2.x,
		b2=line2P2.y;

	float a=f(CPoint(x1,y1),CPoint(x2,y2),CPoint(a1,b1)),
		b=f(CPoint(x1,y1),CPoint(x2,y2),CPoint(a2,b2));

	if(a*b==0)
		return TRUE;
	else if(a*b>0)
		return FALSE;
	else
	{
		a=f(CPoint(a1,b1),CPoint(a2,b2),CPoint(x1,y1));
		b=f(CPoint(a1,b1),CPoint(a2,b2),CPoint(x2,y2));

		if(a*b<=0)
			return TRUE;
		else
			return FALSE;
	}
}

int CLine::f(CPoint a,CPoint b,CPoint c)   // 判断两个线段是否相交所用到的方法
{
//	Private Function F(ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long, ByVal X As Long, ByVal Y As Long) As Long
// 	Dim K As Long
// 	K = (Y2 - Y1) * X - (X2 - X1) * Y + X2 * Y1 - X1 * Y2
	return (b.y-a.y)*c.x-(b.x-a.x)*c.y+b.x*a.y-a.x*b.y;
}

void CLine::Serialize(CArchive &ar)
{
	CLineObj::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_src.x;
		ar << m_src.y;
		
		ar << m_dst.x;
		ar << m_dst.y;
	}
	else
	{
		ar >> m_src.x;
		ar >> m_src.y;
		
		ar >> m_dst.x;
		ar >> m_dst.y;
	}
	
}
