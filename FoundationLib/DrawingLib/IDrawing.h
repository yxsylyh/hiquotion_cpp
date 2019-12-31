// IFigure.h: interface for the IFigure class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IFIGURE_H__8368ADB1_4552_410E_BF23_BA49E54A77F8__INCLUDED_)
#define AFX_IFIGURE_H__8368ADB1_4552_410E_BF23_BA49E54A77F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 把下面这句放到 StdAfx.h 头文件的最前面，可以禁用 4786 警告信息
// #pragma warning(disable : 4786)

// 获取系统字体的方法
// GetStockObject(SYSTEM_FONT); 

class IDrawing  
{
public:
	IDrawing();
	virtual ~IDrawing();

	virtual void draw(CDC *pDC, CPoint point=CPoint(0, 0));
	virtual void move(CSize moveShift){};  // 移动绘制对象，对于矩形类型的绘制对象，该点表示矩形的左上角；对于线型（直线或折线），该点表示第一个端点
	virtual void moveTo(CPoint point){};      // 移动到

protected:
};

#endif // !defined(AFX_IFIGURE_H__8368ADB1_4552_410E_BF23_BA49E54A77F8__INCLUDED_)
