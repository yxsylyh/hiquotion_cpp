// PokerUI.h: interface for the CPokerUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POKERUI_H__70596F65_94B3_4F27_A43F_F908F88484D6__INCLUDED_)
#define AFX_POKERUI_H__70596F65_94B3_4F27_A43F_F908F88484D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "C++\FOUDATIONLIB\UIHANDLERLIB\IUIHandler.h"
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventHandler.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include "Poker.h"
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>
#include "MovingThread.h"
#include "PokerArea.h"
#include "HandArea.h"
#include "FreeArea.h"
#include "PokerSet.h"

class CPokerUI : public IUIHandler, public IEventHandler, public IEventRaisable
{
public:
	CPokerUI();
	virtual ~CPokerUI();

	void animateMovingPoker(CPoint pointTo);
	void animateMovingPoker(CPoker *poker, CPoint pointTo);

	void play();

	CDelegate PokerAnimateMovingDone;

	Declare_Event_Map()

protected:
	IPokerArea *getPokerMovedArea(CPoint point);

	void OnAnimateMovingStep(IEvent *e);
	void OnAnimateMovingDone(IEvent *e);
	
	// 继承
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnSize(int cx, int cy);
private:
	CMovingThread m_movingThread;
	BOOL m_isAnimateMoving;
	BOOL m_canDropped;

	CPokerArea m_pokerArea;
	CHandArea m_handArea;
	CFreeArea m_freeArea;

	IPokerArea *m_areas[3];

	CPokerSet m_pokerSet;

	CRect m_rectMoveFrom;
	IPokerArea *m_areaFrom;
	IPokerArea *m_areaTo;

};

#endif // !defined(AFX_POKERUI_H__70596F65_94B3_4F27_A43F_F908F88484D6__INCLUDED_)
