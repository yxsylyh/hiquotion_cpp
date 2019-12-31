// MovingThread.h: interface for the CMovingThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVINGTHREAD_H__1BE4E963_2F59_4928_9FFF_716C41651C8C__INCLUDED_)
#define AFX_MOVINGTHREAD_H__1BE4E963_2F59_4928_9FFF_716C41651C8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FOUDATIONLIB\MULTITHREADLIB\ThreadBase.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include "Poker.h"
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>

class CMovingThread : public CThreadBase, public IEventRaisable
{
public:
	CMovingThread(float minStep, float frameRate, int maxTotalTime);
	CMovingThread(CPoker *poker, CPoint pointTo, float minStep, float frameRate, int maxTotalTime);
	virtual ~CMovingThread();

	CPoker * getPoker() const { return m_poker; }
	void setPoker(CPoker * val) { m_poker = val; }

	CPoint getPointTo() const { return m_pointTo; }
	void setPointTo(CPoint val) { m_pointTo = val; }

protected:
	virtual UINT threadRun();

	void raiseAnimateMovingStep();
	void raiseAnimateMovingDone();

public:
	CDelegate AnimateMovingStep;
	CDelegate AnimateMovingDone;

private:
	CPoker *m_poker;
	CPoint m_pointTo;
	float m_minStep;
	float m_frameRate;
	int m_maxTotalTime;
};

#endif // !defined(AFX_MOVINGTHREAD_H__1BE4E963_2F59_4928_9FFF_716C41651C8C__INCLUDED_)
