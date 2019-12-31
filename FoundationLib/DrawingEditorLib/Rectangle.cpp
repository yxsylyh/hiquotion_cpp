// Rect.cpp: implementation of the CRect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "Rectangle.h"
#include "RectangleTracker.h"
#include "RectanglePropertySet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4786)

IMPLEMENT_SERIAL(CRectangle, CShapeObj, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangle::CRectangle() : CShapeObj()
{

}

CRectangle::CRectangle(CRect rect) : CShapeObj(rect)
{

}

CRectangle::~CRectangle()
{

}

// 属性

string CRectangle::getType()                   // 获取绘制对象的类型
{
	return "CRectangle";
}

CTracker CRectangle::getTracker()   // 获取选中框
{
	CRectangleTracker rectTracker(m_rect);
	return rectTracker;
}

void CRectangle::setRect(CRect rect)  // 设置矩形的大小 
{
	m_rect=rect;
}

// 方法

void CRectangle::draw(CDC *pDC)                // 屏幕上绘制
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
	pDC->Rectangle(m_rect);
	
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}

// 在创建绘制对象的时候绘制（如果draw绘制很复杂，在创建绘制对象的时候，用这个方法简化绘制，以提高动态绘制的效率）
void CRectangle::drawOnCreating(CDC *pDC)
{
	pDC->MoveTo(m_rect.TopLeft());
	pDC->Rectangle(m_rect);
}

BOOL CRectangle::isHitMe(CPoint hitPoint)      // 点鼠标左键后，是否点中了该绘制对象
{
	refreshRect();
	return m_rect.PtInRect(hitPoint);
}

void CRectangle::move(CSize moveShift)            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
{
	m_rect.OffsetRect(moveShift);
}

void CRectangle::refreshRect()    // 当绘制图形的矩形区域反转了的时候，通过该方法转变回来
{
	if(m_rect.right<m_rect.left)
	{
		long tmp=m_rect.left;
		m_rect.left=m_rect.right;
		m_rect.right=tmp;
	}
	if(m_rect.bottom<m_rect.top)
	{
		long tmp=m_rect.bottom;
		m_rect.bottom=m_rect.top;
		m_rect.top=tmp;
	}
}

void CRectangle::Serialize(CArchive &ar)
{
	CShapeObj::Serialize(ar);
	if (ar.IsStoring())
	{

	}
	else
	{

	}
	
}

