// Elipse.h: interface for the CElipse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELIPSE_H__C8BEC427_116B_41D5_AC70_799A532218C3__INCLUDED_)
#define AFX_ELIPSE_H__C8BEC427_116B_41D5_AC70_799A532218C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

// #include "DrawnObj.h"
#include "Rectangle.h"

class CElipse : public CRectangle // CDrawnObj  
{
public:
	CElipse();
	CElipse(CRect rect);
	virtual ~CElipse();

	// 属性
	
	string getType();                     // 获取绘制对象的类型
	// 	POINT getSrc();     // 获取起点坐标
	// 	POINT getDst();     // 获取终点坐标
// 	CTracker getTracker();   // 获取选中框
	
	// 方法
	virtual void Serialize(CArchive &ar);
	
	void draw(CDC *pDC);                // 屏幕上绘制
	BOOL isHitMe(CPoint hitPoint);      // 点鼠标左键后，是否点中了该绘制对象
	void move(CSize moveShift);            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点

protected:
	DECLARE_SERIAL(CElipse);


private:
// 	CRect m_rect;
};

#endif // !defined(AFX_ELIPSE_H__C8BEC427_116B_41D5_AC70_799A532218C3__INCLUDED_)
