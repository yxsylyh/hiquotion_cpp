// Bezier.cpp: implementation of the CBezier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Figure.h"
#include "Bezier.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBezier::CBezier()
{

}

CBezier::~CBezier()
{
	m_pointList.destroyAll();
}

void CBezier::addPoint(POINT point, POINT leftControl, POINT rightControl, BOOL symmetrical)
{
	BesierPointStruct *bps=new BesierPointStruct;
	bps->p.x=point.x;
	bps->p.y=point.y;
	bps->leftControl.x=leftControl.x;
	bps->leftControl.y=leftControl.y;
	bps->rightControl.x=rightControl.x;
	bps->rightControl.y=rightControl.y;
	bps->symmetrical=symmetrical;

	m_pointList.push_back(bps);
}

void CBezier::addPoint(POINT point, POINT leftControl, POINT rightControl, BOOL symmetrical, int indexAfter)  // 在索引 indexAfter 之后添加 point
{
	if(m_pointList.size()>0 && (indexAfter<0 || indexAfter>=m_pointList.size()))
		return;
	
	BesierPointStruct *bps=new BesierPointStruct;
	bps->p.x=point.x;
	bps->p.y=point.y;
	bps->leftControl.x=leftControl.x;
	bps->leftControl.y=leftControl.y;
	bps->rightControl.x=rightControl.x;
	bps->rightControl.y=rightControl.y;
	bps->symmetrical=symmetrical;

	if(m_pointList.size()<=0)
		m_pointList.push_back(bps);

	m_pointList.insert(m_pointList.begin()+indexAfter, bps);
}

BesierPointStruct *CBezier::getBesierPointStruct(int index)
{
	return m_pointList.at(index);
}

int CBezier::getBesierPointStructIndex(BesierPointStruct *point)
{
	return m_pointList.getIndexOf(point);
}

void CBezier::removePoint(BesierPointStruct *point)
{
	int index=m_pointList.getIndexOf(point);
	if(index<=0)
		return;
	
	m_pointList.erase(m_pointList.begin()+index);
}

void CBezier::removePoint(int index)
{
	if(index<0 || index>=m_pointList.size())
		return;
	
	m_pointList.erase(m_pointList.begin()+index);
}

void CBezier::movePoint(BesierPointStruct *from, POINT to)
{
	int index=m_pointList.getIndexOf(from);
	if(index<=0)
		return;
	
	movePoint(index, to);
}

void CBezier::movePoint(int index, POINT to)
{
	m_pointList.at(index)->p.x=to.x;
	m_pointList.at(index)->p.y=to.y;
}

void CBezier::moveLeftControl(BesierPointStruct *from, POINT to)
{
	int index=m_pointList.getIndexOf(from);
	if(index<=0)
		return;
	
	moveLeftControl(index, to);
}

void CBezier::moveLeftControl(int index, POINT to)
{
	BesierPointStruct *bps=m_pointList.at(index);
	if(!bps)
		return;

	bps->leftControl.x=to.x;
	bps->leftControl.y=to.y;

	if(bps->symmetrical)
	{
		bps->rightControl.x=2*bps->p.x-bps->leftControl.x;
		bps->rightControl.y=2*bps->p.y-bps->leftControl.y;
	}
}

void CBezier::moveRightControl(BesierPointStruct *from, POINT to)
{
	int index=m_pointList.getIndexOf(from);
	if(index<=0)
		return;
	
	moveRightControl(index, to);
}

void CBezier::moveRightControl(int index, POINT to)
{
	BesierPointStruct *bps=m_pointList.at(index);
	if(!bps)
		return;
	
	bps->rightControl.x=to.x;
	bps->rightControl.y=to.y;

	if(bps->symmetrical)
	{
		bps->leftControl.x=2*bps->p.x-bps->rightControl.x;
		bps->leftControl.y=2*bps->p.y-bps->rightControl.y;
	}
}

BOOL CBezier::getSymmetrical(BesierPointStruct *from)
{
	int index=m_pointList.getIndexOf(from);
	if(index<=0)
		return FALSE;
	
	return getSymmetrical(index);
}

BOOL CBezier::getSymmetrical(int index)
{
	return m_pointList.at(index)->symmetrical;
}

void CBezier::setSymmetrical(BesierPointStruct *from, BOOL symmetrical)
{
	int index=m_pointList.getIndexOf(from);
	if(index<=0)
		return;
	
	setSymmetrical(index, symmetrical);
}

void CBezier::setSymmetrical(int index, BOOL symmetrical)
{
	m_pointList.at(index)->symmetrical=symmetrical;
}

void CBezier::drawMe(CDC *pDC, CPoint point)
{
	int count=m_pointList.size();
	int arrayCount=4+(count-2)*3;
	POINT *pointArray=new POINT[arrayCount];
	BesierPointStruct *bps=m_pointList.at(0);
	pointArray[0].x=bps->p.x;
	pointArray[0].y=bps->p.y;
	pointArray[1].x=bps->rightControl.x;
	pointArray[1].y=bps->rightControl.y;
	
	POINT start;
	start.x=bps->p.x;
	start.y=bps->p.y;
	
	int i=0;
	for(i=1;i<count-1;i++)
	{
		BesierPointStruct *bps=m_pointList.at(i);
		if(!bps)
		{
			count--;
			continue;
		}
		pointArray[3*i-1].x=bps->leftControl.x;
		pointArray[3*i-1].y=bps->leftControl.y;
		
		pointArray[3*i].x=bps->p.x;
		pointArray[3*i].y=bps->p.y;
		
		pointArray[3*i+1].x=bps->rightControl.x;
		pointArray[3*i+1].y=bps->rightControl.y;
	}
	
	bps=m_pointList.at(count-1);
	pointArray[arrayCount-2].x=bps->leftControl.x;
	pointArray[arrayCount-2].y=bps->leftControl.y;
	pointArray[arrayCount-1].x=bps->p.x;
	pointArray[arrayCount-1].y=bps->p.y;
	
	// point 不是(0,0)，则移动
	if(point.x!=0 || point.y!=0)
	{
		for(i=0;i<arrayCount;i++)
		{
			pointArray[i].x+=point.x;
			pointArray[i].y+=point.y;
		}
	}
	
	pDC->MoveTo(start);
	pDC->PolyBezier(pointArray, arrayCount);
	
	delete pointArray;
}
