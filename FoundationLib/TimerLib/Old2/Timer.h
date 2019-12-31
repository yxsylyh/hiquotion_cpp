#pragma once

void CALLBACK OnTimer(HWND hWnd,UINT nMsg,UINT_PTR nTimerid,DWORD dwTime);

#include <C++\FoundationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include <C++\FoundationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>

class CTimer : public IEventRaisable
{
public:
	CTimer(void);
	CTimer(int interval);
	~CTimer(void);

	BOOL start();
	void stop();

	int getInterval();
	void setInterval(int interval);

	HWND getHwnd() const { return m_hwnd; }
	void setHwnd(HWND val) { m_hwnd = val; }

	CDelegate Timer;

protected:
	BOOL createTimer(int interval);
	void destroyTimer();

protected:
	HWND m_hwnd;
	UINT_PTR m_timerId;
	int m_interval;   // 时间间隔，以毫秒为单位
};
