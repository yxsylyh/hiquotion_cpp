// MovingInfo.h: interface for the CMovingInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVINGINFO_H__41AECCF5_BC40_49F6_9B43_FD04DC90C0CA__INCLUDED_)
#define AFX_MOVINGINFO_H__41AECCF5_BC40_49F6_9B43_FD04DC90C0CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 针对运动的起点和终点，在最小移动步长以及最大总移动时间（毫秒）的约束下，给出运动步长
class CMovingInfo  
{
public:
	CMovingInfo();
	virtual ~CMovingInfo();

	// 针对运动的起点和终点，在最小移动步长以及最大总移动时间（毫秒）的约束下，给出运动步长
	// 如果不规定最小移动步长或最大总移动时间，则相应值设置为0
	// 如果最小移动步长和最大总移动时间都为0，则返回 to - from
	static float getMovingStep(float from, float to, float frameRate, float minStep=10, int maxTotalInterval=500);

	static float getMovingStep(float from, float to, float frameRate, int maxTotalInterval=500);


	static CSize getMovingStep2D(CPoint from, CPoint to, float frameRate, CPoint minStep=CPoint(10, 10), int maxTotalInterval=500);
};

#endif // !defined(AFX_MOVINGINFO_H__41AECCF5_BC40_49F6_9B43_FD04DC90C0CA__INCLUDED_)
