// RoundRectangle.h: interface for the CRoundRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROUNDRECTANGLE_H__E5C1589D_D9CE_43B3_9B3B_5179852E340F__INCLUDED_)
#define AFX_ROUNDRECTANGLE_H__E5C1589D_D9CE_43B3_9B3B_5179852E340F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4786)

// #include "DrawnObj.h"
#include "Rectangle.h"

class CRoundRectangle : public CRectangle //CDrawnObj  
{
public:
	CRoundRectangle();
	CRoundRectangle(CRect rect, POINT roundCenter=CPoint(15,15), BOOL isDrawRoundHandle=FALSE);
	virtual ~CRoundRectangle();

	// 属性
	
	string getType();                     // 获取绘制对象的类型
	// 	POINT getSrc();     // 获取起点坐标
	// 	POINT getDst();     // 获取终点坐标
	CTracker getTracker();   // 获取选中框
	void setDrawRoundHandle(BOOL isDrawRoundHandle);   // 设置是否绘制调节圆角弧度的句柄

	int getRoundPointX();          // 获取圆角点的水平坐标
	void setRoundPointX(int x);    // 设置圆角点的水平坐标

	int getRoundPointY();          // 获取圆角点的垂直坐标
	void setRoundPointY(int y);    // 设置圆角点的垂直坐标

	// 方法
	virtual void Serialize(CArchive &ar);

	void draw(CDC *pDC);                // 屏幕上绘制
// 	// 在创建绘制对象的时候绘制（如果draw绘制很复杂，在创建绘制对象的时候，用这个方法简化绘制，以提高动态绘制的效率）
// 	void drawOnCreating(CDC *pDC);
	BOOL isHitMe(CPoint hitPoint);      // 点鼠标左键后，是否点中了该绘制对象
	void move(CSize moveShift);            // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
	void moveHandle(int nHandle, CPoint point);  // 移动绘制对象Tracker的第nHandle号句柄到point点上

protected:
	DECLARE_SERIAL(CRoundRectangle);
		
private:
// 	void refreshRect();    // 当绘制图形的矩形区域反转了的时候，通过该方法转变回来

// 	CRect m_rect;
	POINT m_roundCenter;
	BOOL m_drawRoundHandle;
};

#endif // !defined(AFX_ROUNDRECTANGLE_H__E5C1589D_D9CE_43B3_9B3B_5179852E340F__INCLUDED_)
