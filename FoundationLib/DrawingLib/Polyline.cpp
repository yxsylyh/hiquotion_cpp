// Polygram.cpp: implementation of the CPolygram class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Polyline.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4786)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPolyline::CPolyline()
{

}

CPolyline::~CPolyline()
{
	m_pointList.destroyAll();
}

void CPolyline::addPoint(POINT point)
{
	m_pointList.push_back(new CPoint(point));
}

void CPolyline::addPoint(POINT point, int indexAfter)  // 在索引 indexAfter 之后添加 point
{
	if(indexAfter<=0)
		return;

	m_pointList.insert(m_pointList.begin()+indexAfter, new CPoint(point));
}

CPoint *CPolyline::getPoint(int index)
{
	return m_pointList.at(index);
}

int CPolyline::getPointIndex(CPoint *point)
{
	return m_pointList.getIndexOf(point);
}

void CPolyline::removePoint(CPoint *point)
{
	int index=m_pointList.getIndexOf(point);
	if(index<=0)
		return;

	m_pointList.erase(m_pointList.begin()+index);
}

void CPolyline::removePoint(int index)
{
	if(index<0 || index>=m_pointList.size())
		return;

	m_pointList.erase(m_pointList.begin()+index);
}

void CPolyline::movePoint(CPoint *from, POINT to)
{
	int index=m_pointList.getIndexOf(from);
	if(index<=0)
		return;

	movePoint(index, to);
}

void CPolyline::movePoint(int index, POINT to)
{
	m_pointList.at(index)->x=to.x;
	m_pointList.at(index)->y=to.y;
}

void CPolyline::drawMe(CDC *pDC, CPoint point)
{
	POINT *pointArray=new POINT[m_pointList.size()];
	int count=m_pointList.size();
	for(int i=0;i<count;i++)
	{
		CPoint *p=m_pointList.at(i);
		if(!p)
		{
			count--;
			continue;
		}
		
		pointArray[i].x=p->x;
		pointArray[i].y=p->y;
	}
	
	// point 不是(0,0)，则移动
	if(point.x!=0 || point.y!=0)
	{
		for(i=0;i<count;i++)
		{
			pointArray[i].x+=point.x;
			pointArray[i].y+=point.y;
		}
	}
	
	pDC->Polyline(pointArray, count);
	
	delete pointArray;
}
