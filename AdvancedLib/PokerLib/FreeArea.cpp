// FreeArea.cpp: implementation of the CFreeArea class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FreeArea.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFreeArea::CFreeArea()
: IPokerArea(4, CPoint(0, 10))
{
	setBorderColor(RGB(255,255,255));
	setBorderStyle(BS_SOLID);
	setFillStyle(BS_SOLID);
	setMovingEffected(ChildHandled);
}

CFreeArea::~CFreeArea()
{

}

// 判断是否可以落牌的方法
BOOL CFreeArea::canDrop(CPoker *poker, CPoint relativeTopLeft)
{
	if(!poker)
		return FALSE;

	// 如果drop过来的牌下面还有牌，就不允许放牌
	if(poker->getUIHandler(0))
		return FALSE;

	CRect pokerRect=poker->getRect();

	CRect rect;
	for(int i=0;i<4;i++)
	{
		CRect relativeRect=m_rect[i];
		relativeRect.OffsetRect(relativeTopLeft);
		
		if(rect.IntersectRect(&pokerRect, &relativeRect))
		{
			CPoker *bottom=m_pokerColumnArea[i]->getBottomPoker();
			// 如果自由区无牌，并且所放牌为 A，则可以放牌
			if(!bottom && poker->getPokerValue()==PVAce)
				return TRUE;

			// 或者自由区最底牌（即放在最上面的牌）比drop过来的牌同花色，并且数值小1，则允许放牌
			if(bottom->getPokerType()==poker->getPokerType() && bottom->getPokerValue()==poker->getPokerValue()-1)
				return TRUE;

			return FALSE;
		}
	}

	return FALSE;
}

// 事件处理
void CFreeArea::OnSize(int cx, int cy)
{
	int left=cx/25;
	int width=cx/5;
	int interval=cx/25;
	
	int top=cy/20;
	int height=cy*4/5;
	
	for(int i=0;i<4;i++)
	{
// 		m_areaRect[i].left=left+i*(width+interval);
		m_areaRect[i].left=left+i*(CPoker::getWidth()+interval);
		m_areaRect[i].top=top;
		m_areaRect[i].right=m_areaRect[i].left+CPoker::getWidth(); //width;
		m_areaRect[i].bottom=top+height;
		
		m_pokerColumnArea[i]->setRect(m_areaRect[i]);
	}
}
