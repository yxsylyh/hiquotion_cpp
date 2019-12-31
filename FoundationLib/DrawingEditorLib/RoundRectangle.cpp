// RoundRectangle.cpp: implementation of the CRoundRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DRAWFIGURE.h"
#include "RoundRectangle.h"
#include "RoundRectangleTracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CRoundRectangle, CRectangle, 0)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRoundRectangle::CRoundRectangle() : CRectangle()
{
	m_roundCenter=CPoint(15,15);
	m_drawRoundHandle=FALSE;
}

CRoundRectangle::CRoundRectangle(CRect rect, POINT roundCenter, BOOL isDrawRoundHandle) : CRectangle(rect)
{
// 	m_rect=rect;
	m_roundCenter=roundCenter;
	m_drawRoundHandle=isDrawRoundHandle;
}

CRoundRectangle::~CRoundRectangle()
{

}

// 属性

string CRoundRectangle::getType()                   // 获取绘制对象的类型
{
	return "CRoundRectangle";
}

CTracker CRoundRectangle::getTracker()   // 获取选中框
{
	CRoundRectangleTracker rectTracker(m_rect, m_roundCenter,m_drawRoundHandle);
	return rectTracker;
}

void CRoundRectangle::setDrawRoundHandle(BOOL isDrawRoundHandle)   // 设置是否绘制调节圆角弧度的句柄
{
	m_drawRoundHandle=isDrawRoundHandle;
}

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

void CRoundRectangle::draw(CDC *pDC)                // 屏幕上绘制
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
	pDC->RoundRect(m_rect, m_roundCenter);
	
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}

// 在创建绘制对象的时候绘制（如果draw绘制很复杂，在创建绘制对象的时候，用这个方法简化绘制，以提高动态绘制的效率）
// void CRoundRectangle::drawOnCreating(CDC *pDC)
// {
// 	draw(pDC);
// }

BOOL CRoundRectangle::isHitMe(CPoint hitPoint)      // 点鼠标左键后，是否点中了该绘制对象
{
	refreshRect();
	return m_rect.PtInRect(hitPoint);
}

void CRoundRectangle::move(CSize moveShift)            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
{
	m_rect.OffsetRect(moveShift);
}

void CRoundRectangle::moveHandle(int nHandle, CPoint point)  // 移动绘制对象Tracker的第nHandle号句柄到point点上
{
	if(nHandle<=HP_RIGHT_BOTTOM)
		m_rect=getTracker().moveTrackerHandle(nHandle,point);
	else
	{
		m_roundCenter.x=point.x-m_rect.TopLeft().x;
		m_roundCenter.y=point.y-m_rect.TopLeft().y;
		if(m_roundCenter.x<=0)
			m_roundCenter.x=0;
		else if(m_roundCenter.x>=m_rect.Width())
			m_roundCenter.x=m_rect.Width();
		if(m_roundCenter.y<=0)
			m_roundCenter.y=0;
		else if(m_roundCenter.y>=m_rect.Height())
			m_roundCenter.y=m_rect.Height();
	}
	
}

void CRoundRectangle::Serialize(CArchive &ar)
{
	CRectangle::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_roundCenter.x;
		ar << m_roundCenter.y;
		ar << (DWORD)m_drawRoundHandle;
	}
	else
	{
		ar >> m_roundCenter.x;
		ar >> m_roundCenter.y;
		DWORD dtmp=0;
		ar >> dtmp;
		m_drawRoundHandle=(BOOL)dtmp;
	}
	
}

// void CRoundRectangle::refreshRect()    // 当绘制图形的矩形区域反转了的时候，通过该方法转变回来
// {
// 	if(m_rect.right<m_rect.left)
// 	{
// 		long tmp=m_rect.left;
// 		m_rect.left=m_rect.right;
// 		m_rect.right=tmp;
// 	}
// 	if(m_rect.bottom<m_rect.top)
// 	{
// 		long tmp=m_rect.bottom;
// 		m_rect.bottom=m_rect.top;
// 		m_rect.top=tmp;
// 	}
// }

