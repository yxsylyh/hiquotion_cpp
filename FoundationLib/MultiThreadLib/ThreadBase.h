#pragma once

#include "ithread.h"
// #include <afxmt.h>

#define Thread_Normal_Exit 0;          // 线程正常退出
#define Thread_Error 0xE0000000;       // 线程异常退出
#define Thread_To_Stop 0xE0000001;     // 线程准备退出
#define Thread_Stop_Forced 0xE0000002; // 线程被强制退出

class CThreadBase : public IThread
{
public:
	CThreadBase(BOOL createNow=TRUE);
	virtual ~CThreadBase(void);

	BOOL create();
	void close();
	HANDLE getThreadHandle();
	BOOL start();
	virtual BOOL pause();
	virtual void stop();
	void terminate();
	UINT run();
	DWORD getExitCode();
	ThreadStatus getStatus(){return m_status;};

// 	// 停止线程，并等待线程结束
// 	// 等待 ms 毫秒之后，如果返回值是失败或取消，则直接结束线程
// 	// 这个方法好像不太好使，就取消了吧
// 	void join(int ms=INFINITE);

	// 循环判断状态是不是 ToStop，不是则返回
	// 调用该 join 方法之前，需要先调用 stop 方法，使线程状态改变成 ToStop，否则还没进入循环就直接返回了
	// 加 virtual 的意思，是如果子类中包含同步对象，并且已经锁定，该函数默认不会处理，就会使程序死在这个循环里
	// 所以如果子类有同步对象，那么需要重写该方法，并在调用父类的该方法之前，唤醒同步对象
	virtual void join();

	string getErrMessage(){return m_message;};

	HANDLE m_hThread;

protected:

	// 继承CThread类的子类，需要重写该方法，来完成线程需要完成的任务
	virtual UINT threadRun(){return 0;};

	DWORD m_threadId;
	ThreadStatus m_status;
	BOOL m_toStop;  // 标识客户是否希望线程立即自行终止，即调用了stop方法
	string m_message;
	UINT m_returnValue;
};
