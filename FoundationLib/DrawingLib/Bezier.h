// Bezier.h: interface for the CBezier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEZIER_H__8FBF14B4_B2D3_4A2A_9003_32BB4D49BD74__INCLUDED_)
#define AFX_BEZIER_H__8FBF14B4_B2D3_4A2A_9003_32BB4D49BD74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Line.h"
#include <C++\FoudationLib\DataStructLib\PointerList.h>

// 贝塞尔曲线类中点的结构
// 每个点包含左控制点和右控制点
// 起点的左控制点和终点的右控制点没有意义，在绘图时被忽略
struct BesierPointStruct
{
	POINT p;  // 曲线的端点
	POINT leftControl;   // 该端点的左控制点
	POINT rightControl;  // 该端点的右控制点
	BOOL symmetrical;        // 决定左右控制点是否以该点为对称中心

	BOOL operator ==(BesierPointStruct bps)
	{
		if(p.x==bps.p.x && p.y==bps.p.y
			&& leftControl.x==bps.leftControl.x && leftControl.y==bps.leftControl.y
			&& rightControl.x==bps.rightControl.x && rightControl.y==bps.rightControl.y
// 			&& symmetrical==bps.symmetrical
			)
			return TRUE;
		else
			return FALSE;
	}
};

// 贝塞尔曲线类
// MFC GDI 使用左右两点以及左点的右控制点和右点的左控制点来绘制这两点之间的贝塞尔曲线
// 本类使用的结构使每个点包含左右两控制点，这样做的目的是便于逻辑上的理解
// 同时需要指出：起点的左控制点和终点的右控制点没有意义，在绘图时被忽略
class CBezier : public ILine
{
public:
	CBezier();
	virtual ~CBezier();

	void addPoint(POINT point, POINT leftControl, POINT rightControl, BOOL symmetrical=TRUE);
	void addPoint(POINT point, POINT leftControl, POINT rightControl, BOOL symmetrical, int indexAfter);  // 在索引 indexAfter 之后添加 point
	
	BesierPointStruct *getBesierPointStruct(int index);
	int getBesierPointStructIndex(BesierPointStruct *point);
	
	void removePoint(BesierPointStruct *point);
	void removePoint(int index);
	
	void movePoint(BesierPointStruct *from, POINT to);
	void movePoint(int index, POINT to);

	void moveLeftControl(BesierPointStruct *from, POINT to);
	void moveLeftControl(int index, POINT to);
	
	void moveRightControl(BesierPointStruct *from, POINT to);
	void moveRightControl(int index, POINT to);

	BOOL getSymmetrical(BesierPointStruct *from);
	BOOL getSymmetrical(int index);
	
	void setSymmetrical(BesierPointStruct *from, BOOL symmetrical);
	void setSymmetrical(int index, BOOL symmetrical);
	
	virtual void drawMe(CDC *pDC, CPoint point);
	
protected:
	CPointerList<BesierPointStruct *> m_pointList;
};

#endif // !defined(AFX_BEZIER_H__8FBF14B4_B2D3_4A2A_9003_32BB4D49BD74__INCLUDED_)
