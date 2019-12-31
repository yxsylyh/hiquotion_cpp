// ILine.h: interface for the ILine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILINE_H__CD54F328_5D71_403B_83B4_FC0F404F8DED__INCLUDED_)
#define AFX_ILINE_H__CD54F328_5D71_403B_83B4_FC0F404F8DED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IShape.h"

class ILine : public IShape  
{
public:
	ILine();
	virtual ~ILine();

	// 属性
	
	CPoint getFirstPoint();
	CPoint getSrc();     // 获取起点
	CPoint getDst();     // 获取终点
	
	// 获取和设置起点、终点的横纵坐标
	int getX1();
	void setX1(int x1);
	int getY1();
	void setY1(int y1);
	int getX2();
	void setX2(int x2);
	int getY2();
	void setY2(int y2);
	
	// 设置线条的两个端点
	void setPoints(CPoint src,CPoint dst);
	
	// 线条属性
	
	// 线条颜色
	int getLineColor() const { return m_lineColor; }
	void setLineColor(int val) { m_lineColor = val; }
	// 线条样式
	int getLineStyle() const { return m_lineStyle; }
	void setLineStyle(int val) { m_lineStyle = val; }
	// 线条宽度
	int getLineWidth() const { return m_lineWidth; }
	void setLineWidth(int val) { m_lineWidth = val; }
	
	// 线条端点（起点、终点）的形状
	int getSrcPointCap() const { return m_srcPointCap; }
	void setSrcPointCap(int val) { m_srcPointCap = val; }
	int getDstPointCap() const { return m_dstPointCap; }
	void setDstPointCap(int val) { m_dstPointCap = val; }
	
	// 方法
	virtual void draw(CDC *pDC, CPoint point=CPoint(0, 0));
	virtual void drawMe(CDC *pDC, CPoint point);
	void move(CSize moveShift);  // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点

protected:
	virtual void preparePen(CDC *pDC);  // 在绘图前，先准备好笔
	virtual void restorePen(CDC *pDC);  // 绘图之后，恢复原来的笔

protected:
	CPoint m_start,m_end;
	
	int m_lineColor;
	int m_lineWidth;
	int m_lineStyle;
	int m_srcPointCap;
	int m_dstPointCap;

	CPen pen;
	CPen *oldPen;
};

#endif // !defined(AFX_ILINE_H__CD54F328_5D71_403B_83B4_FC0F404F8DED__INCLUDED_)
