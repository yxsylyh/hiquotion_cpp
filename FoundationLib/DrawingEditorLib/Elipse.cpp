// Elipse.cpp: implementation of the CElipse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "Elipse.h"
#include "RectangleTracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4786)

IMPLEMENT_SERIAL(CElipse, CRectangle, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CElipse::CElipse() : CRectangle()
{

}

CElipse::CElipse(CRect rect) : CRectangle(rect)
{
// 	m_rect=rect;
}

CElipse::~CElipse()
{

}

// 属性

string CElipse::getType()                   // 获取绘制对象的类型
{
	return "CElipse";
}

// CTracker CElipse::getTracker()   // 获取选中框
// {
// 	CRectangleTracker rectTracker(m_rect);
// 	return rectTracker;
// }



// 方法

void CElipse::draw(CDC *pDC)                // 屏幕上绘制
{
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = m_borderColor;
	
	CPen pen;
	// PS_ENDCAP_ROUND 表示圆点
	// 	pen.CreatePen(m_lineStyle|PS_GEOMETRIC|PS_ENDCAP_ROUND, 2, &logBrush);
	pen.CreatePen(m_borderStyle|PS_GEOMETRIC|PS_ENDCAP_SQUARE,m_borderWidth, &logBrush);
// 	CPen pen;
// 	pen.CreatePen(m_borderStyle,m_borderWidth,m_borderColor);
	CPen *oldPen=pDC->SelectObject(&pen);
	
	CBrush brush;
	CBrush *oldBrush=NULL;
	switch(m_fillStyle)
	{
	case 0:  // 实心填充
		brush.CreateSolidBrush(m_backColor);
		oldBrush=pDC->SelectObject(&brush);
		break;
	case 1:  // 透明填充
		
		// 		brush.CreateSysColorBrush(0);
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:  // Hatch 填充
		brush.CreateHatchBrush(m_fillStyle-2,m_backColor);
		oldBrush=pDC->SelectObject(&brush);
		break;
	}

	pDC->MoveTo(m_rect.TopLeft());
	pDC->Ellipse(m_rect);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}

BOOL CElipse::isHitMe(CPoint hitPoint)      // 点鼠标左键后，是否点中了该绘制对象
{
	refreshRect();
	float a=m_rect.Width()/2.0,b=m_rect.Height()/2.0;
	CPoint center=m_rect.CenterPoint();
	if((hitPoint.x-center.x)*(hitPoint.x-center.x)/(a*a)+(hitPoint.y-center.y)*(hitPoint.y-center.y)/(b*b)<1.0)
		return TRUE;
	else
		return FALSE;
}

void CElipse::move(CSize moveShift)            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
{
	m_rect.OffsetRect(moveShift);
}

void CElipse::Serialize(CArchive &ar)
{
	CRectangle::Serialize(ar);
	if (ar.IsStoring())
	{

	}
	else
	{

	}
	
}
