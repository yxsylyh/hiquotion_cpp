// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__C69410E0_F0F8_4A47_9BDE_6E3C5E524CE7__INCLUDED_)
#define AFX_LINE_H__C69410E0_F0F8_4A47_9BDE_6E3C5E524CE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "LineObj.h"
#include "PropertyList.h"
#include "LinePropertySet.h"

class CLine : public CLineObj  
{
public:
	CLine();
	CLine(CRect rect);
	CLine(POINT src, POINT dst);
	virtual ~CLine();

	// 属性
	
	string getType();                     // 获取绘制对象的类型

	POINT getSrc();     // 获取起点
	POINT getDst();     // 获取终点

	// 获取和设置起点、终点的横纵坐标
	int getX1();
	void setX1(int x1);
	int getY1();
	void setY1(int y1);
	int getX2();
	void setX2(int x2);
	int getY2();
	void setY2(int y2);

	CTracker getTracker();   // 获取选中框
	// 根据矩形的左上角和右下角点，确定直线的两个端点位置
	void setPoints(CPoint oldPoint,CPoint newPoint);

	// 方法
	virtual void Serialize(CArchive &ar);

	void draw(CDC *pDC);                // 屏幕上绘制
	// 在创建绘制对象的时候绘制（如果draw绘制很复杂，在创建绘制对象的时候，用这个方法简化绘制，以提高动态绘制的效率）
	void drawOnCreating(CDC *pDC);
	BOOL isHitMe(CPoint hitPoint);      // 点鼠标左键后，是否点中了该绘制对象
	void move(CSize moveShift);            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
	void moveHandle(int nHandle, CPoint point);  // 移动绘制对象Tracker的第nHandle号句柄到point点上

	// 判断该直线是否与指定的矩形相交
	BOOL intersection(CRect rc);

protected:
	DECLARE_SERIAL(CLine);

	// 判断两个线段是否相交
	BOOL intersectionTwoLines(CPoint line1P1,CPoint line1P2,CPoint line2P1,CPoint line2P2);
	int f(CPoint a,CPoint b,CPoint c);   // 判断两个线段是否相交所用到的方法

	CLinePropertySet *m_properties;
// 	CPropertyList *m_properties;

	POINT m_src,m_dst;

};

#endif // !defined(AFX_LINE_H__C69410E0_F0F8_4A47_9BDE_6E3C5E524CE7__INCLUDED_)
