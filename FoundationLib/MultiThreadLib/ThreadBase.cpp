#include "StdAfx.h"
#include "ThreadBase.h"
#include "threadentry.h"

CThreadBase::CThreadBase(BOOL createNow)
: m_hThread(NULL)
{
	m_returnValue=0;
	m_toStop=FALSE;

	if(createNow)
		create();
}

CThreadBase::~CThreadBase(void)
{
	if(m_status==Running || m_status==Paused || m_status==ToStop)
		terminate();
}

BOOL CThreadBase::create()
{
	if(m_hThread)
		terminate();

	m_hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadEntry,this,CREATE_SUSPENDED,&m_threadId);
	if(!m_threadId)
	{
		m_message="线程创建失败！";
		m_status=Error;
		return FALSE;
	}
	else
	{
		m_status=Created;
		return TRUE;
	}
}

void CThreadBase::close()
{
	ExitThread(m_returnValue);// 这个是关闭主线程的，不应该调用这个函数！！！！！！！！
	m_hThread=NULL;
	m_status=Closed;
}

HANDLE CThreadBase::getThreadHandle()
{
	return m_hThread;
}

BOOL CThreadBase::start()
{
	if(m_status==Stopped)
		create();

	DWORD ret=ResumeThread(m_hThread);
// 	if(ResumeThread(m_hThread)==(DWORD)-1)
	if(ret==(DWORD)-1)
	{
		m_message="启动线程失败！";
		m_status=Error;
		return FALSE;
	}
	else
	{
		m_status=Running;
		return TRUE;
	}
}

BOOL CThreadBase::pause()
{
	if(SuspendThread(m_hThread)==(DWORD)-1)
	{
		m_message="暂停线程失败！";
		m_status=Error;
		return FALSE;
	}
	else
	{
		m_status=Paused;
		return TRUE;
	}
}

void CThreadBase::stop()
{
	if(m_status==Paused)
		start();

	m_status=ToStop;
	m_toStop=TRUE;
}

void CThreadBase::terminate()
{
	if(m_status!=Error && m_status!=Terminated && m_status!=Stopped)
	{
		m_returnValue=Thread_Stop_Forced;
		TerminateThread(m_hThread,(DWORD)m_returnValue);
		m_hThread=NULL;
		m_status=Terminated;
	}
}

UINT CThreadBase::run()
{
	if(m_status==Error)
	{
		m_returnValue=Thread_Error;
		return Thread_Error;
	}

	m_status=Running;

	m_toStop=FALSE;
	m_returnValue=threadRun();

	m_status=Stopped;

	return 0;
}

DWORD CThreadBase::getExitCode()
{
	return m_returnValue;
}

// 	// 停止线程，并等待线程结束
// 	// 等待 ms 毫秒之后，如果返回值是失败或取消，则直接结束线程
// 	// 注意：调用该方法之前，请不要调用 stop 方法
// void CThreadBase::join(int ms)
// {
// 	if(m_status!=Running && m_status!=Paused)
// 		return;
// 
// 	stop();
// 	DWORD ret=WaitForSingleObject(m_hThread, ms);
// 	switch(ret)
// 	{
// 	case WAIT_ABANDONED:
// 	case WAIT_TIMEOUT:
// 	case WAIT_FAILED:
// 		terminate();
// 		break;
// 	default:
// 
// 		break;
// 	}
// }

// 循环判断状态是不是 ToStop，不是则返回
// 调用该 join 方法之前，不需要先调用 stop 方法，因为如果线程已经停止了，该方法会使线程处于ToStop状态，从而无法退出循环      xxxxxx，使线程状态改变成 ToStop，否则还没进入循环就直接返回了
// 加 virtual 的意思，是如果子类中包含同步对象，并且已经锁定，该函数默认不会处理，就会使程序死在这个循环里
// 所以如果子类有同步对象，那么需要重写该方法，并在调用父类的该方法之前，唤醒同步对象
void CThreadBase::join()
{
	if(m_status!=Running && m_status!=Paused && m_status!=ToStop)
		return;

	stop();

	while(m_status==ToStop)
	{
		Sleep(1);
	}
}
