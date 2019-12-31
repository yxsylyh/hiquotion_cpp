#pragma once

void CALLBACK OnTimer(HWND hWnd,UINT nMsg,UINT_PTR nTimerid,DWORD dwTime);

#include <C++\FoundationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include <C++\FoundationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>

/*

  C++ Timer 用法


  方法一：
  调用SetTimer时指定窗口句柄hWnd，nIDEvent中指定计时器ID，将lpTimerFunc置NULL从而不使用TimerProc。
  在窗口过程中处理WM_TIMER消息。调用KillTimer时，使用SetTimer中指定的hWnd和id。


  方法二：
  调用SetTimer时指定窗口句柄hWnd，nIDEvent中指定计时器ID，lpTimerFunc参数不为NULL而指定为TimerProc函数的指针。
  这种方法使用TimerProc函数(名字可自定)处理WM_TIMER消息


  方法三：
  调用SetTimer时不指定窗口句柄(为NULL)，iTimerID参数自然被忽略，lpTimerFunc不为NULL而指定为TimerProc的指针。
  正如上面SetTimer的讨论中所说的，此时SetTimer的返回值正是新建立的计时器的ID，需将这个ID保存以供KillTimer销毁计时器时所用。
  当然，KillTimer的hWnd参数也置为NULL。这种方法同样用TimerProc处理WM_TIMER消息。
  

*/

class CTimer : public IEventRaisable
{
public:
	CTimer(void);
	CTimer(int interval);
	~CTimer(void);

	BOOL start();
	// 为了使用回调函数而定义
	BOOL start(TIMERPROC TimerProc);

	void stop();

	int getInterval();
	void setInterval(int interval);

	HWND getHwnd() const { return m_hwnd; }
	void setHwnd(HWND val) { m_hwnd = val; }

	UINT_PTR getTimerId();

	CDelegate Timer;

protected:
	BOOL createTimer(int interval);
	BOOL createTimer(int interval, TIMERPROC TimerProc);
	void destroyTimer();

protected:
	HWND m_hwnd;
	UINT_PTR m_timerId;
	int m_interval;   // 时间间隔，以毫秒为单位
};
