#include "StdAfx.h"
#include "Timer.h"

CTimer::CTimer(void)
{
	m_interval=0;
	m_timerId=0;
	m_hwnd=NULL;
}

CTimer::CTimer(int interval)
{
	if(interval>0)
		m_interval=interval;
	else
		m_interval=1000; // Ä¬ÈÏ1Ãë

	m_timerId=0;
}

CTimer::~CTimer(void)
{
	destroyTimer();
}

BOOL CTimer::start()
{
	if(m_interval<=0)
		return FALSE;

	if(!m_hwnd)
		return FALSE;

	return createTimer(m_interval);
}

void CTimer::stop()
{
	destroyTimer();
}

BOOL CTimer::createTimer(int interval)
{
	if(!m_hwnd)
		return FALSE;
	
	if(m_timerId)
		destroyTimer();

	m_timerId=SetTimer(m_hwnd, (UINT_PTR)this, m_interval, (TIMERPROC)&OnTimer);
	if(m_timerId>0)
		return TRUE;
	else
		return FALSE;
}

void CTimer::destroyTimer()
{
	if(m_timerId>0)
	{
		BOOL ret=::KillTimer(AfxGetApp()->GetMainWnd()->m_hWnd, m_timerId);
		m_timerId=0;
	}
}

int CTimer::getInterval()
{
	return m_interval;
}

void CTimer::setInterval(int interval)
{
	m_interval = interval;
}

void CALLBACK OnTimer(HWND hWnd,UINT nMsg,UINT_PTR nTimerid,DWORD dwTime)
{
	if(hWnd)
	{
		CTimer *timer=(CTimer *)nTimerid;
		if(!timer)
			return;
		
		IEvent e(timer, "Timer");
		timer->Timer.raiseEvent(timer, &e);
	}
}

