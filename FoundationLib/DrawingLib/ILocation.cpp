// ILocation.cpp: implementation of the ILocation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ILocation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ILocation::ILocation()
: m_rect(0,0,10,10)
{

}

ILocation::ILocation( int left, int top, int right, int bottom )
: m_rect(left, top, right, bottom)
{
	
}

ILocation::ILocation( CRect rect )
: m_rect(rect)
{
	
}

ILocation::~ILocation()
{

}

void ILocation::getRect(CRect &rect)
{
	rect=m_rect;
}

CRect ILocation::getRect()
{
	return m_rect;
}

CPoint ILocation::getFirstPoint()
{
	return m_rect.TopLeft();
}

CRect *ILocation::getRectAddr()
{
	return &m_rect;
}

void ILocation::setRect(CRect rect)
{
	m_rect.left=rect.left;
	m_rect.top=rect.top;
	m_rect.right=rect.right;
	m_rect.bottom=rect.bottom;
	
	OnSize(m_rect.Width(), m_rect.Height());
}

void ILocation::setRect(int left, int top, int right, int bottom)
{
	m_rect.left=left;
	m_rect.top=top;
	m_rect.right=right;
	m_rect.bottom=bottom;
	
	OnSize(m_rect.Width(), m_rect.Height());
}

void ILocation::refreshRect()    // 当绘制图形的矩形区域反转了的时候，通过该方法转变回来
{
	if(m_rect.right<m_rect.left)
	{
		long tmp=m_rect.left;
		m_rect.left=m_rect.right;
		m_rect.right=tmp;
	}
	if(m_rect.bottom<m_rect.top)
	{
		long tmp=m_rect.bottom;
		m_rect.bottom=m_rect.top;
		m_rect.top=tmp;
	}
}
