// Rect.h: interface for the CRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECT_H__79D00011_2420_4A2C_9C5B_4659FE4C569E__INCLUDED_)
#define AFX_RECT_H__79D00011_2420_4A2C_9C5B_4659FE4C569E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

#include "ShapeObj.h"
#include "PropertyList.h"
#include "RectanglePropertySet.h"

class CRectangle : public CShapeObj  
{
public:
	CRectangle();
	CRectangle(CRect rect);
	virtual ~CRectangle();

	// 属性
	
	virtual string getType();                     // 获取绘制对象的类型
	// 	POINT getSrc();     // 获取起点坐标
	// 	POINT getDst();     // 获取终点坐标
	CTracker getTracker();   // 获取选中框
	void setRect(CRect rect);  // 设置矩形的大小 
	
	// 方法
	virtual void Serialize(CArchive &ar);

	virtual void draw(CDC *pDC);                // 屏幕上绘制
	// 在创建绘制对象的时候绘制（如果draw绘制很复杂，在创建绘制对象的时候，用这个方法简化绘制，以提高动态绘制的效率）
	virtual void drawOnCreating(CDC *pDC);
	
	virtual BOOL isHitMe(CPoint hitPoint);      // 点鼠标左键后，是否点中了该绘制对象
	virtual void move(CSize moveShift);            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点

protected:
	CRectanglePropertySet *m_properties;

	DECLARE_SERIAL(CRectangle);
// 	CRect m_rect;

	void refreshRect();    // 当绘制图形的矩形区域反转了的时候，通过该方法转变回来

private:
};

#endif // !defined(AFX_RECT_H__79D00011_2420_4A2C_9C5B_4659FE4C569E__INCLUDED_)
