// GridLayout.cpp: implementation of the CGridLayout class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GridLayout.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGridLayout::CGridLayout()
: CLayout(), m_rowCount(1), m_colCount(1)
{

}

CGridLayout::CGridLayout(CRect rect)
: CLayout(rect), m_rowCount(1), m_colCount(1)
{
	
}

CGridLayout::CGridLayout(RECT rc)
: CLayout(rc), m_rowCount(1), m_colCount(1)
{
	
}

CGridLayout::CGridLayout(int left, int top, int width, int height)
: CLayout(left, top, width, height), m_rowCount(1), m_colCount(1)
{
	
}

CGridLayout::CGridLayout(int rowCount, int colCount)
: m_rowCount(rowCount), m_colCount(colCount)
{
	
}

CGridLayout::CGridLayout(CRect rect, int rowCount, int colCount)
: CLayout(rect), m_rowCount(rowCount), m_colCount(colCount)
{
	
}

CGridLayout::CGridLayout(RECT rc, int rowCount, int colCount)
: CLayout(rc), m_rowCount(rowCount), m_colCount(colCount)
{
	
}

CGridLayout::CGridLayout(int left, int top, int width, int height, int rowCount, int colCount)
: CLayout(left, top, width, height), m_rowCount(rowCount), m_colCount(colCount)
{
	
}

CGridLayout::~CGridLayout()
{

}

void CGridLayout::getRect(int index, CRect &rect)
{
	int row=index / m_rowCount;
	int col=index % m_rowCount;

	getRect(row, col, rect);
}

void CGridLayout::getRect(int rowIndex, int colIndex, CRect &rect)
{
	if(m_rowCount==1 && m_colCount==1)
	{
		rect.left=m_rect.left;
		rect.top=m_rect.top;
		rect.right=m_rect.right;
		rect.bottom=m_rect.bottom;

		return;
	}

	int gridWidth=m_rect.Width()/m_colCount;
	int gridHeight=m_rect.Height()/m_rowCount;

	rect.left=colIndex*gridWidth;
	rect.top=rowIndex*gridHeight;

	rect.right=rect.left+gridWidth;
	rect.bottom=rect.top+gridHeight;
}

void CGridLayout::getFullScreenRect(CRect &rect)
{
	rect.left=m_rect.left;
	rect.top=m_rect.top;
	rect.right=m_rect.right;
	rect.bottom=m_rect.bottom;
}
