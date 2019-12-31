// PokerUI.cpp: implementation of the CPokerUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PokerUI.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPokerUI::CPokerUI()
: m_movingThread(15, 30, 250), m_isAnimateMoving(FALSE), m_canDropped(FALSE), m_areaFrom(FALSE), m_areaTo(FALSE)
{
	setBorderStyle(-1);   // 无边框
// 	setFillStyle(2);  // 背景透明

	m_areas[0]=&m_pokerArea;
	m_areas[1]=&m_handArea;
	m_areas[2]=&m_freeArea;

	for(int i=0;i<3;i++)
	{
		m_areas[i]->setBorderStyle(-1);
		m_areas[i]->setFillStyle(TRANSPARENT);
		m_areas[i]->setMovingEffected(ChildHandled);

		addUIHandler(m_areas[i]);
	}
}

CPokerUI::~CPokerUI()
{

}

Begin_Event_Map(CPokerUI)
Event_Map(&m_movingThread, "AnimateMovingStep", OnAnimateMovingStep)
Event_Map(&m_movingThread, "AnimateMovingDone", OnAnimateMovingDone)
End_Event_Map()

void CPokerUI::animateMovingPoker(CPoint pointTo)
{
	if(!m_handlerSelected)
		return;
	
	animateMovingPoker((CPoker *)m_handlerSelected, pointTo);
}

void CPokerUI::animateMovingPoker(CPoker *poker, CPoint pointTo)
{
	if(!poker)
		return;
	
	m_movingThread.setPoker(poker);
	m_movingThread.setPointTo(pointTo);
	m_isAnimateMoving=TRUE;

	m_movingThread.AnimateMovingStep+=this;
	m_movingThread.AnimateMovingDone+=this;

	m_movingThread.start();
}

void CPokerUI::play()
{
	m_pokerSet.shuffle();
	CPoker *poker=NULL;
	int i=0;

	// 在纸牌区放置 7x7 张牌（右上边的牌是扣着的）
	for(i=0;i<7;i++)
	{
		for(int j=0;j<7;j++)
		{
			poker=m_pokerSet.getShuffledPoker(7*i+j);
			if(poker)
			{
				if(j>i)
					poker->setOff(TRUE);
				m_pokerArea.add(j, poker);
			}
		}
	}
	
	// 在手动纸牌区放置剩余的 3 张牌
	for(i=49;i<52;i++)
	{
		poker=m_pokerSet.getShuffledPoker(i);
		if(poker)
			m_handArea.add(i-49, poker);
	}

	// 更新界面
	updateUI();
}

void CPokerUI::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_isAnimateMoving)
		return;

	IUIHandler::OnLButtonDown(nFlags, point);

	if(!m_handlerSelected)
		return;

	CPoker *poker=(CPoker *)m_handlerSelected;

	m_areaFrom=getPokerMovedArea(point);
	if(!m_areaFrom)
		return;

// 	// 已选择纸牌在顶层窗口的相对位置
// 	CPoint offset=CPoint(poker->getAbsoluteX(), poker->getAbsoluteY());
// 
// 	m_areaFrom->pickup(poker);
// 	m_handlerSelected->move(offset);
// 
// 	m_rectMoveFrom=poker->getRect();
// // 	m_rectMoveFrom.OffsetRect(offset);
// 	
// 	addUIHandler(m_handlerSelected);
}

IPokerArea *CPokerUI::getPokerMovedArea(CPoint point)
{
	CRect areaRect;
	for(int i=0;i<3;i++)
	{
		areaRect=m_areas[i]->getRect();
		if(areaRect.PtInRect(point))
			return m_areas[i];
	}

	return NULL;
}

void CPokerUI::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(!m_handlerSelected)
		return;

	// 首先获取纸牌移动到了哪个区域内
	m_areaTo=getPokerMovedArea(point);
	if(!m_areaTo)  // 这种情况应该不可能出现
		return;

// 	// 如果可以落牌，则移动到落牌区域
// 	if(m_areaTo->canDrop((CPoker *)m_handlerSelected, m_areaTo->getRect().TopLeft()))
// 	{
// 		m_canDropped=TRUE;
// 		CPoint pointTo=m_areaTo->getNextDrop();
// 		animateMovingPoker(pointTo);
// 	}
// 	else
// 	{
// 		// 否则，把牌移回原位置
// 		m_canDropped=FALSE;
// 		CPoint pointFrom=m_rectMoveFrom.TopLeft();
// 		animateMovingPoker(pointFrom);
// 	}
}

void CPokerUI::OnAnimateMovingStep(IEvent *e)
{
	updateUI();
}

void CPokerUI::OnAnimateMovingDone(IEvent *e)
{
	m_isAnimateMoving=FALSE;

	m_movingThread.AnimateMovingStep-=this;
	m_movingThread.AnimateMovingDone-=this;

	if(m_handlerSelected)
	{
		
// 		if(m_canDropped)
// 		{
// 			removeUIHandler(m_handlerSelected);
// 			if(m_areaTo)
// 				m_areaTo->drop((CPoker *)m_handlerSelected);
// 		}
// 		else
// 		{
// 			if(m_areaFrom)
// 				m_areaFrom->drop((CPoker *)m_handlerSelected);
// 		}
	}

	IEvent ee(this, "PokerAnimateMovingDone");
	PokerAnimateMovingDone.raiseEvent(this, &ee);
}

void CPokerUI::OnSize(int cx, int cy)
{
	m_handArea.setRect(0, 0, cx/2, cy*2/7);
	m_freeArea.setRect(cx/2, 0, cx, cy*2/7);
	
	m_pokerArea.setRect(0, cy*2/7, cx, cy);
	
	int width=m_pokerArea.getPokerWidth();
	m_pokerSet.setPokerSize(width, width*DEFAULT_POKER_HEIGHT/DEFAULT_POKER_WIDTH);
}
