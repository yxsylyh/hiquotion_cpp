// Handle.cpp: implementation of the CHandle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Handle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHandle::CHandle(POINT handlePosition, BOOL bHandleEnabled)
{
	m_bHandleEnabled=bHandleEnabled;
	m_handlePosition=handlePosition;

	m_handleSize.cx=Default_Handle_Sizex;
	m_handleSize.cy=Default_Handle_Sizey;
}

CHandle::CHandle(int handlePositionX, int handlePositionY, BOOL bHandleEnabled)
{
	m_bHandleEnabled=bHandleEnabled;
	m_handlePosition.x=handlePositionX;
	m_handlePosition.y=handlePositionY;
	
	m_handleSize.cx=Default_Handle_Sizex;
	m_handleSize.cy=Default_Handle_Sizey;
}

CHandle::~CHandle()
{

}

// 属性

BOOL CHandle::isHandleEnabled()    // 这个句柄是不是可以操作的
{
	return m_bHandleEnabled;
}

SIZE CHandle::getHandleSize()      // 获取句柄的尺寸
{
	return m_handleSize;
}

POINT CHandle::getHandlPosition()  // 获取句柄的位置
{
	return m_handlePosition;
}

void CHandle::setHandlePosition(int x, int y) // 设置句柄的位置
{
	m_handlePosition.x=x;
	m_handlePosition.y=y;
}


void CHandle::setHandleSize(SIZE handleSize)  // 设置句柄大小，默认不需要设置
{
	m_handleSize=handleSize;
}

// 方法

void CHandle::drawHandle(CDC *DC)
{
	CRect rect(m_handlePosition,m_handleSize);
	DC->Rectangle(&rect);
}

// 获取句柄所在的Rect
CRect CHandle::getHandleRect()
{
	CRect rc(m_handlePosition,CPoint(m_handlePosition.x+getHandleSize().cx,m_handlePosition.y+getHandleSize().cy));
	return rc;
}
