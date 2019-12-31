// PokerArea.cpp: implementation of the CPokerArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PokerArea.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPokerArea::CPokerArea()
: IPokerArea(POKER_COLUMN_COUNT, CPoint(0, 30))
{

}

CPokerArea::~CPokerArea()
{

}

// 判断是否可以落牌的方法
BOOL CPokerArea::canDrop(CPoker *poker, CPoint relativeTopLeft)
{
	if(!poker)
		return FALSE;

	// 如果 poker 与哪一列相交，则返回该列是否可以落牌的判断结果
	// 否则不可以落牌

	CRect pokerRect=poker->getRect();

	CRect rect;
	for(int i=0;i<POKER_COLUMN_COUNT;i++)
	{
		// pokerRect 在最顶层，m_areaRect[i]
		CRect areaRect=m_areaRect[i];
		areaRect.OffsetRect(relativeTopLeft);

		if(rect.IntersectRect(&pokerRect, &areaRect))
		{
			if(m_pokerColumnArea[i]->canDrop(poker, areaRect.TopLeft()))
			{
				m_pokerDropIndex=i;
				return TRUE;
			}
		}
	}

	return FALSE;
}

// 事件处理
void CPokerArea::OnSize(int cx, int cy)
{
	int left=cx*3/80;
	int width=cx/10;
	int interval=cx*3/80;

	int top=cy/20;
	int height=cy*9/10;

	for(int i=0;i<POKER_COLUMN_COUNT;i++)
	{
		m_areaRect[i].left=left+i*(width+interval);
		m_areaRect[i].top=top;
		m_areaRect[i].right=m_areaRect[i].left+width;
		m_areaRect[i].bottom=top+height;

		m_pokerColumnArea[i]->setRect(m_areaRect[i]);
	}

	m_pokerWidth=width;
}
