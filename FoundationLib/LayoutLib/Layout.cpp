// Layout.cpp: implementation of the CLayout class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Layout.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLayout::CLayout()
: m_rect(0, 0, 10, 10)
{

}

CLayout::CLayout(CRect rect)
{
	m_rect.left=rect.left;
	m_rect.top=rect.top;
	m_rect.right=rect.right;
	m_rect.bottom=rect.bottom;
}

CLayout::CLayout(RECT rc)
{
	m_rect.left=rc.left;
	m_rect.top=rc.top;
	m_rect.right=rc.right;
	m_rect.bottom=rc.bottom;
}

CLayout::CLayout(int left, int top, int width, int height)
: m_rect(left, top, left+width, top+height)
{
	
}

CLayout::~CLayout()
{

}

void CLayout::setRect(CRect rect)
{
	m_rect.left=rect.left;
	m_rect.top=rect.top;
	m_rect.right=rect.right;
	m_rect.bottom=rect.bottom;
}

void CLayout::setSize(SIZE size)
{
	m_rect.right=m_rect.left+size.cx;
	m_rect.bottom=m_rect.top+size.cy;
}

void CLayout::setSize(int cx, int cy)
{
	m_rect.right=m_rect.left+cx;
	m_rect.bottom=m_rect.top+cy;
}
