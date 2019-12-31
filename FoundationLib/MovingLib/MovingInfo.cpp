// MovingInfo.cpp: implementation of the CMovingInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MovingInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMovingInfo::CMovingInfo()
{

}

CMovingInfo::~CMovingInfo()
{

}

// 针对运动的起点和终点，在最小移动步长以及最大总移动时间（毫秒）的约束下，给出运动步长
// 如果不规定最小移动步长或最大总移动时间，则相应值设置为0
// 如果最小移动步长和最大总移动时间都为0，则返回 to - from
float CMovingInfo::getMovingStep(float from, float to, float frameRate, float minStep, int maxTotalInterval)
{
	if(minStep==0 && maxTotalInterval==0)
		return to-from;
	else if(maxTotalInterval==0)
	{
		if(to>=from)
			return minStep;
		else
			return -minStep;
	}
	else
	{
		float frames=frameRate * (float)maxTotalInterval / 1000.0;
		float step=(to-from)/frames;
		if(abs(step)<minStep)
		{
			if(to>=from)
				return minStep;
			else
				return -minStep;
		}
		else
			return step;
	}
}

float CMovingInfo::getMovingStep(float from, float to, float frameRate, int maxTotalInterval)
{
	if(maxTotalInterval==0)
		return to-from;
	else
	{
		float frames=frameRate * (float)maxTotalInterval / 1000.0;
		float step=(to-from)/frames;
		return step;
	}
}


CSize CMovingInfo::getMovingStep2D(CPoint from, CPoint to, float frameRate, CPoint minStep, int maxTotalInterval)
{
	if(minStep==CPoint(0, 0) && maxTotalInterval==0)
		return CSize(to.x-from.x, to.y-from.y);
	else if(maxTotalInterval==0)
	{
		if(to.x<from.x)
			minStep.x=-minStep.x;
		if(to.y<from.y)
			minStep.y=-minStep.y;

		return minStep;
	}
	else
	{
		float frames=frameRate * (float)maxTotalInterval / 1000.0;
		float stepx=(to.x-from.x)/frames;
		float stepy=(to.y-from.y)/frames;

		if(abs(stepx)<minStep.x && abs(stepy)<minStep.y)
		{
			if(to.x<from.x)
				minStep.x=-minStep.x;

			if(to.y<from.y)
				minStep.y=-minStep.y;
		}

		return minStep;
	}
}
