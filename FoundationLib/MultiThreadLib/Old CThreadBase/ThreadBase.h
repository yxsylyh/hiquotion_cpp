#pragma once

#include "ithread.h"
#include <afxmt.h>

#define Thread_Normal_Exit 0;          // 线程正常退出
#define Thread_Error 0xE0000000;       // 线程异常退出
#define Thread_To_Stop 0xE0000001;     // 线程准备退出
#define Thread_Stop_Forced 0xE0000002; // 线程被强制退出

class CThreadBase : public IThread
{
public:
	CThreadBase(void);
	virtual ~CThreadBase(void);

	HANDLE getThreadHandle();
	void start();
	void pause();
	virtual void stop();
	void terminate();
	UINT run();
	DWORD getExitCode();
	ThreadStatus getStatus(){return m_status;};
// 	// 停止线程，并等待线程结束
// 	// 等待 ms 毫秒之后，如果返回值是失败或取消，则直接结束线程
// 	void join(int ms=INFINITE);

	string getMessage(){return m_message;};

protected:
	// 继承CThread类的子类，需要重写该方法，来完成线程需要完成的任务
	virtual UINT threadRun(){return 0;};

	HANDLE m_handle;
	DWORD m_threadId;
	ThreadStatus m_status;
	BOOL m_toStop;  // 标识客户是否希望线程立即自行终止，即调用了stop方法
	string m_message;
	UINT m_returnValue;

	CEvent m_threadEvent;
};
