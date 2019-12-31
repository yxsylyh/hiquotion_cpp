// IShape.h: interface for the IShape class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISHAPE_H__CA2B6CC1_58CA_453E_BECA_093CAA3DB716__INCLUDED_)
#define AFX_ISHAPE_H__CA2B6CC1_58CA_453E_BECA_093CAA3DB716__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDrawing.h"
#include "ILocation.h"
#include <C++\FoudationLib\DataStructLib\PointerMap.h>

class IShape : public IDrawing, public ILocation
{
public:
	IShape();
	IShape(int left, int top, int right, int bottom);
	IShape(CRect rect);
	virtual ~IShape();

	// 属性设置
	
	// 背景色
	COLORREF getBackColor() const { return m_backColor; }
	void setBackColor(COLORREF val) { m_backColor = val; }
	
	// 背景填充样式
	int getFillStyle() const { return m_fillStyle; }
	void setFillStyle(int val) { m_fillStyle = val; }
	
	// 边框颜色
	COLORREF getBorderColor() const { return m_borderColor; }
	void setBorderColor(COLORREF val) { m_borderColor = val; }
	
	// 边框样式
	int getBorderStyle() const { return m_borderStyle; }
	void setBorderStyle(int val) { m_borderStyle = val; }
	
	// 边框宽度
	virtual int getBorderWidth() const { return m_borderWidth; }
	virtual void setBorderWidth(int val) { m_borderWidth = val; }
	
	// 附加操作
	// 可以由子类重写附加操作的结果
	virtual BOOL attach(CRect *rect);   // 比如 IFigure类A附加了一个rect指针，该rect指针是IFigure类B的rect，那么A改变rect中的值时，B绘制图形的位置会相应改变
	virtual BOOL attach(IDrawing *figure); // 比如实现类似吸附的功能，或者移动时，被附加的IFigure（即参数figure对象）会一起移动
	
	BOOL getFullfill() const { return m_fullfill; }
	void setFullfill(BOOL val) { m_fullfill = val; }
	
	BOOL isUseClip() const { return m_isUseClip; }
	void setUseClip(BOOL val) { m_isUseClip = val; }
	
	// 方法
	virtual void draw(CDC *pDC, CPoint point=CPoint(0, 0), CRgn *parentRgn=NULL);
	virtual void drawMe(CDC *pDC, CPoint point);
	virtual void move(CSize moveShift);            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
	virtual void moveTo(CPoint point);      // 移动到
protected:
	virtual void preparePenAndBrush(CDC *pDC);  // 在绘图前，先准备好笔和画刷
	virtual void restorePenAndBrush(CDC *pDC);  // 绘图之后，恢复原来的笔和画刷

	virtual void prepareRgn(CDC *pDC, CPoint point, CRgn *parentRgn);
	virtual void restoreRgn(CDC *pDC);

	virtual void createRng(CPoint point);

protected:
// 	// 判断相交
// 	virtual BOOL intersect(CRect rect);

protected:
	COLORREF m_backColor;
	int m_fillStyle;
	COLORREF m_borderColor;
	int m_borderStyle;
	int m_borderWidth;

	CPen m_pen;
	CPen *m_oldPen;

	CBrush m_brush;
	CBrush *m_oldBrush;

	BOOL m_fullfill;

	BOOL m_isUseClip;  // 是否使用剪辑功能（默认为 FALSE）
	CRgn m_rgn;
	CRgn *m_parentRgn;
	CRgn m_tmpRgn;
	CRgn *m_pTmpRgn;
};

#endif // !defined(AFX_ISHAPE_H__CA2B6CC1_58CA_453E_BECA_093CAA3DB716__INCLUDED_)
