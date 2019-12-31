// Polygon.cpp: implementation of the CPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Figure.h"
#include "Polygon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPolygon::CPolygon()
{

}

CPolygon::~CPolygon()
{
	m_pointList.destroyAll();
}

void CPolygon::addPoint(POINT point)
{
	m_pointList.push_back(new CPoint(point));
}

void CPolygon::addPoint(POINT point, int indexAfter)  // 在索引 indexAfter 之后添加 point
{
	if(indexAfter<=0)
		return;
	
	m_pointList.insert(m_pointList.begin()+indexAfter, new CPoint(point));
}

CPoint *CPolygon::getPoint(int index)
{
	return m_pointList.at(index);
}

int CPolygon::getPointIndex(CPoint *point)
{
	return m_pointList.getIndexOf(point);
}

void CPolygon::removePoint(CPoint *point)
{
	int index=m_pointList.getIndexOf(point);
	if(index<=0)
		return;
	
	m_pointList.erase(m_pointList.begin()+index);
}

void CPolygon::removePoint(int index)
{
	if(index<0 || index>=m_pointList.size())
		return;
	
	m_pointList.erase(m_pointList.begin()+index);
}

void CPolygon::movePoint(CPoint *from, POINT to)
{
	int index=m_pointList.getIndexOf(from);
	if(index<=0)
		return;
	
	movePoint(index, to);
}

void CPolygon::movePoint(int index, POINT to)
{
	m_pointList.at(index)->x=to.x;
	m_pointList.at(index)->y=to.y;
}

void CPolygon::drawMe(CDC *pDC, CPoint point)
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
	
	for(i=0;i<count;i++)
	{
		pointArray[i].x+=point.x;
		pointArray[i].y+=point.y;
	}
	
	pDC->Polygon(pointArray, count);
	
	delete pointArray;
}
