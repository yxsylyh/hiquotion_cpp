#include "StdAfx.h"
#include "ThreadList.h"
#include <C++/FoudationLib/SystemLib/systemoperation.h>

CThreadList::CThreadList(void)
: m_toStopThread(TRUE)
{
	m_isSelfDestroy=TRUE;
}

CThreadList::~CThreadList(void)
{
	// 基类的默认设置已经保证了 removeAll() 的调用
// 	if(m_toStopThread)
// 		removeAll();
}

void CThreadList::startAll()
{
	for(int i=0;i<(int)size();i++)
	{
		CThreadBase *thrd=at(i);
		if(thrd)
			thrd->start();
	}
}

void CThreadList::stopAll()
{
	for(int i=0;i<(int)size();i++)
	{
		CThreadBase *thrd=at(i);
		if(!thrd)
			continue;

		ThreadStatus status=thrd->getStatus();
		if(status==Running || status==Paused)
			thrd->stop();
	}
}

void CThreadList::removeAll()
{
	stopAll();
	for(int i=0;i<(int)size();i++)
	{
		CThreadBase *thrd=at(i);
		if(!thrd)
			continue;

		ThreadStatus status=thrd->getStatus();
		if(status==Running || status==Paused || status==ToStop)
		{
			if(status==Running || status==Paused)
				thrd->stop();

			while(thrd->getStatus()==Running || thrd->getStatus()==ToStop)
			{
// 				DWORD dwRet = WaitForSingleObject(thrd->getThreadHandle(),INFINITE);
// 				if ( dwRet == WAIT_TIMEOUT )
// 					thrd->terminate();

				// DoEvents
				CSystemOperation::DoEvents();
			}
		}
	}
	destroyAll();
}

int CThreadList::getAliveCount()
{
	int count=0;
	for(int i=0;i<(int)size();i++)
	{
		CThreadBase *thrd=at(i);
		if(!thrd)
			continue;

		ThreadStatus status=thrd->getStatus();
		if(status==Created || status==Running || status==Paused || status==ToStop)
			count++;
	}
	return count;
}

int CThreadList::getStartedCount()
{
	int count=0;
	for(int i=0;i<(int)size();i++)
	{
		CThreadBase *thrd=at(i);
		if(!thrd)
			continue;
		
		ThreadStatus status=thrd->getStatus();
		if(status==Running || status==Paused || status==ToStop)
			count++;
	}
	return count;
}

void CThreadList::dontStopThread()
{
	m_toStopThread=FALSE;
}
