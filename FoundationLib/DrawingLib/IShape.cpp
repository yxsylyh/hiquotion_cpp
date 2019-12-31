// IShape.cpp: implementation of the IShape class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IShape.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IShape::IShape()
: IDrawing(), m_oldPen(NULL), m_oldBrush(NULL), m_isUseClip(FALSE), m_parentRgn(NULL), m_pTmpRgn(NULL)
{
	m_backColor=RGB(255,255,255);
	m_fillStyle=BS_SOLID;
	m_borderColor=RGB(0,0,0);
	m_borderStyle=PS_SOLID;
	m_borderWidth=1;
// 	m_figureMap.clear();
}

IShape::IShape(int left, int top, int right, int bottom)
: IDrawing(), ILocation(left, top, right, bottom), m_oldPen(NULL), m_oldBrush(NULL), m_isUseClip(FALSE), m_parentRgn(NULL), m_pTmpRgn(NULL)
{
	m_backColor=RGB(255,255,255);
	m_fillStyle=BS_SOLID;
	m_borderColor=RGB(0,0,0);
	m_borderStyle=PS_SOLID;
	m_borderWidth=1;
// 	m_figureMap.clear();
}

IShape::IShape(CRect rect)
: IDrawing(), ILocation(rect), m_oldPen(NULL), m_oldBrush(NULL), m_isUseClip(FALSE), m_parentRgn(NULL), m_pTmpRgn(NULL)
{
	m_backColor=RGB(255,255,255);
	m_fillStyle=BS_SOLID;
	m_borderColor=RGB(0,0,0);
	m_borderStyle=PS_SOLID;
	m_borderWidth=1;
// 	m_figureMap.clear();
}

IShape::~IShape()
{

}

// 方法

void IShape::preparePenAndBrush(CDC *pDC)  // 在绘图前，先准备好笔和画刷
{
	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = m_borderColor;
	
	// PS_ENDCAP_ROUND 表示圆点
	// 	pen.CreatePen(m_lineStyle|PS_GEOMETRIC|PS_ENDCAP_ROUND, 2, &logBrush);
	if(m_borderStyle>=0)
	{
		m_pen.CreatePen(m_borderStyle|PS_GEOMETRIC|PS_ENDCAP_SQUARE,m_borderWidth, &logBrush);
	}
	else
		m_pen.CreateStockObject(NULL_PEN);
	m_oldPen=pDC->SelectObject(&m_pen);

	switch(m_fillStyle)
	{
	case 0:  // 实心填充
		m_brush.CreateSolidBrush(m_backColor);
		m_oldBrush=pDC->SelectObject(&m_brush);
		break;
	case 1:  // 透明填充
		// 		brush.CreateSysColorBrush(0);
		m_brush.CreateStockObject(NULL_BRUSH);
		m_oldBrush=pDC->SelectObject(&m_brush);
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:  // Hatch 填充
		m_brush.CreateHatchBrush(m_fillStyle-2,m_backColor);
		m_oldBrush=pDC->SelectObject(&m_brush);
		break;
	}
}

void IShape::restorePenAndBrush(CDC *pDC)  // 绘图之后，恢复原来的笔和画刷
{
	if(m_oldBrush)
	{
		pDC->SelectObject(m_oldBrush);
		m_oldBrush=NULL;
	}

	if(m_oldPen)
	{
		pDC->SelectObject(m_oldPen);
		m_oldPen=NULL;
	}

	if(m_pen.GetSafeHandle())
		m_pen.DeleteObject();

	if(m_brush.GetSafeHandle())
		m_brush.DeleteObject();
}

void IShape::draw(CDC *pDC, CPoint point, CRgn *parentRgn)
{
	if(!pDC)
		return;
	
	if(!pDC->GetSafeHdc())
		return;
	
	preparePenAndBrush(pDC);

	prepareRgn(pDC, point, parentRgn);
	
	drawMe(pDC, point);

	restoreRgn(pDC);

	restorePenAndBrush(pDC);
}

void IShape::drawMe(CDC *pDC, CPoint point)
{
	CPoint p=point;
	p.Offset(m_rect.TopLeft());
	pDC->MoveTo(p);
	CRect rect(p, m_rect.Size());
	
	pDC->Rectangle(&rect);
}

void IShape::prepareRgn(CDC *pDC, CPoint point, CRgn *parentRgn)
{
	if(!pDC)
		return;

	m_parentRgn=parentRgn;

	if(m_isUseClip)
	{
		createRng(point);

// 		pDC->SelectClipRgn(&m_rgn, RGN_AND);

		if(parentRgn)
		{
			// 如果本图形使用区域，并且父区域不空，说明需要将两个区域取交集

			if(m_tmpRgn.GetSafeHandle())
				m_tmpRgn.DeleteObject();
			m_tmpRgn.CreateRectRgn(0,0,1,1);

			int ret=m_tmpRgn.CombineRgn(&m_rgn, parentRgn, RGN_AND);
			switch(ret)
			{
			case 0:  // CombineRgn 操作失败
				m_pTmpRgn=parentRgn;
				break;
			case 1:  // 不相交
				m_pTmpRgn=parentRgn;
				break;
			case 2:  // 相交
			case 3:  // 相交，但存在多个区域
				m_pTmpRgn=&m_tmpRgn;
				break;
			}
		}
		else
		{
			// 如果父区域为空，则只适用本图形的区域

			m_pTmpRgn=&m_rgn;
		}
	}
	else
	{
		// 如果本图形不使用区域，但父区域不空，则直接使用父区域，否则，不改变 pDC 的区域设置
		if(parentRgn)
			m_pTmpRgn=parentRgn;
		else
			m_pTmpRgn=NULL;
	}

	// 设置区域
	if(m_pTmpRgn)
 		pDC->SelectClipRgn(m_pTmpRgn);
}

void IShape::restoreRgn(CDC *pDC)
{
	if(pDC)
		pDC->SelectClipRgn(m_parentRgn);
}

void IShape::createRng(CPoint point)
{
	if(m_rgn.GetSafeHandle())
		m_rgn.DeleteObject();

	CRect rect=m_rect;
	rect.OffsetRect(point);

	m_rgn.CreateRectRgnIndirect(&rect);
}

// 判断相交
// BOOL IShape::intersect(CRect rect)
// {
// 
// }


void IShape::move(CSize moveShift)            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
{
	m_rect.OffsetRect(moveShift);
}

void IShape::moveTo(CPoint point)      // 移动到
{
	m_rect.SetRect(point.x, point.y, point.x+m_rect.Width(), point.y+m_rect.Height());
}

// 附加操作
// 可以由子类重写附加操作的结果
BOOL IShape::attach(CRect *rect)   // 比如 IFigure类A附加了一个rect指针，该rect指针是IFigure类B的rect，那么A改变rect中的值时，B绘制图形的位置会相应改变
{
	return TRUE;
}

BOOL IShape::attach(IDrawing *figure) // 比如实现类似吸附的功能，或者移动时，被附加的IFigure（即参数figure对象）会一起移动
{
	return TRUE;
}
