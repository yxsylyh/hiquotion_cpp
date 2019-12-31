#include "StdAfx.h"
#include "TimerBase.h"

CTimerBase::CTimerBase(void)
{
	m_interval=1000; // 默认1秒
	m_timerId=0;
	m_hwnd=NULL;

	timerBase=this;
}

CTimerBase::CTimerBase(int interval)
{
	if(interval>0)
		m_interval=interval;

	m_timerId=0;
	m_hwnd=NULL;
	
	timerBase=this;
}

CTimerBase::~CTimerBase(void)
{
	destroyTimer();
}

BOOL CTimerBase::start()
{
	if(m_interval<=0)
		return FALSE;

// 	if(!m_hwnd)
// 		return FALSE;

	return createTimer(m_interval);
}

// 为了使用回调函数而定义
// BOOL CTimerBase::start(TIMERPROC TimerProc)
// {
// 	if(m_interval<=0)
// 		return FALSE;
// 	
// // 	if(!m_hwnd)
// // 		return FALSE;
// 
// 	return createTimer(m_interval, TimerProc);
// }


void CTimerBase::stop()
{
	destroyTimer();
}

BOOL CTimerBase::createTimer(int interval)
{
// 	if(!m_hwnd)
// 		return FALSE;
	
	if(m_timerId)
		destroyTimer();

	m_timerId=SetTimer(m_hwnd, (UINT_PTR)this, m_interval, (TIMERPROC)&OnTimerCallback);
// 	m_timerId=SetTimer(AfxGetApp()->GetMainWnd()->m_hWnd, (UINT_PTR)this, m_interval, (TIMERPROC)&OnTimer);
// 	m_timerId=SetTimer(NULL, (UINT_PTR)this, m_interval, (TIMERPROC)&OnTimer);

// 	CString msg;
// 	msg.Format("SetTimer return value is %d", m_timerId);
// 	MessageBox(0, msg, "", MB_OK);

	if(m_timerId>0)
		return TRUE;
	else
		return FALSE;
}

// BOOL CTimerBase::createTimer(int interval, TIMERPROC TimerProc)
// {
// // 	if(!m_hwnd)
// // 		return FALSE;
// 	
// 	if(m_timerId)
// 		destroyTimer();
// 	
// 	m_timerId=SetTimer(m_hwnd, (UINT_PTR)this, m_interval, TimerProc);
// // 	m_timerId=SetTimer(NULL, (UINT_PTR)this, m_interval, TimerProc);
// // 	m_timerId=SetTimer(NULL, NULL, m_interval, TimerProc);
// // 	m_timerId=SetTimer(AfxGetApp()->GetMainWnd()->m_hWnd, (UINT_PTR)this, m_interval, TimerProc);
// 
// 	// for debug
// // 	CString timerId;
// // 	timerId.Format("Timer ID is %d", m_timerId);
// // 	MessageBox(NULL, timerId, "", MB_OK);
// 
// 	if(m_timerId>0)
// 		return TRUE;
// 	else
// 		return FALSE;
// }

void CTimerBase::destroyTimer()
{
// 	CString msg;
// 	msg.Format("m_timerId is %d", m_timerId);
// 	MessageBox(0, msg, "", MB_OK);

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

int CTimerBase::getInterval()
{
	return m_interval;
}

void CTimerBase::setInterval(int interval)
{
	m_interval = interval;
}

UINT_PTR CTimerBase::getTimerId()
{
// 	if(!m_hwnd)
		return m_timerId;
// 	else
// 		return (UINT_PTR)this;
}

void CTimerBase::TimerCallback(HWND hWnd,UINT nMsg,UINT_PTR nTimerid,DWORD dwTime)
{
	OnTimer(hWnd, nMsg, nTimerid, dwTime);
}


void CALLBACK OnTimerCallback(HWND hWnd,UINT nMsg,UINT_PTR nTimerid,DWORD dwTime)
{
// 	if(hWnd)
// 	{
// 		CTimerBase *timer=(CTimerBase *)nTimerid;
// 		if(!timer)
// 			return;
// 		
// 		IEvent e(timer, "Timer");
// 		timer->Timer.raiseEvent(timer, &e);
// 	}

	if(!timerBase)
		return;

	timerBase->TimerCallback(hWnd, nMsg, nTimerid, dwTime);
}

