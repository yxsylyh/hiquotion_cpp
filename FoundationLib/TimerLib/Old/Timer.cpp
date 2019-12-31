#include "StdAfx.h"
#include "Timer.h"

CTimer::CTimer(void)
{
	m_interval=1000; // 默认1秒
	m_timerId=0;
	m_hwnd=NULL;
}

CTimer::CTimer(int interval)
{
	if(interval>0)
		m_interval=interval;

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

// 	if(!m_hwnd)
// 		return FALSE;

	return createTimer(m_interval);
}

// 为了使用回调函数而定义
BOOL CTimer::start(TIMERPROC TimerProc)
{
	if(m_interval<=0)
		return FALSE;
	
// 	if(!m_hwnd)
// 		return FALSE;

	return createTimer(m_interval, TimerProc);
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
// 	m_timerId=SetTimer(AfxGetApp()->GetMainWnd()->m_hWnd, (UINT_PTR)this, m_interval, (TIMERPROC)&OnTimer);
// 	m_timerId=SetTimer(NULL, (UINT_PTR)this, m_interval, (TIMERPROC)&OnTimer);
	if(m_timerId>0)
		return TRUE;
	else
		return FALSE;
}

BOOL CTimer::createTimer(int interval, TIMERPROC TimerProc)
{
// 	if(!m_hwnd)
// 		return FALSE;
	
	if(m_timerId)
		destroyTimer();
	
	m_timerId=SetTimer(m_hwnd, (UINT_PTR)this, m_interval, TimerProc);
// 	m_timerId=SetTimer(NULL, (UINT_PTR)this, m_interval, TimerProc);
// 	m_timerId=SetTimer(NULL, NULL, m_interval, TimerProc);
// 	m_timerId=SetTimer(AfxGetApp()->GetMainWnd()->m_hWnd, (UINT_PTR)this, m_interval, TimerProc);

	// for debug
// 	CString timerId;
// 	timerId.Format("Timer ID is %d", m_timerId);
// 	MessageBox(NULL, timerId, "", MB_OK);

	if(m_timerId>0)
		return TRUE;
	else
		return FALSE;
}

void CTimer::destroyTimer()
{
	if(m_timerId>0)
	{
		if(!m_hwnd)
			::KillTimer(m_hwnd, m_timerId);
		else
// 			::KillTimer(AfxGetApp()->GetMainWnd()->m_hWnd, m_timerId);
			::KillTimer(m_hwnd, (UINT_PTR)this);

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

UINT_PTR CTimer::getTimerId()
{
// 	if(!m_hwnd)
		return m_timerId;
// 	else
// 		return (UINT_PTR)this;
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

