// TaskDispatcher.cpp: implementation of the CTaskDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskDispatcher.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskDispatcher::CTaskDispatcher()
: m_isStarted(FALSE), m_totalTaskCount(0)
{

}

CTaskDispatcher::~CTaskDispatcher()
{
	for(int i=0;i<(int)m_runningList.size();i++)
	{
		ITask *task=m_runningList.at(i);
		if(!task)
			continue;

		task->stop();
	}

	m_waitList.destroyAll();
	m_doneList.destroyAll();
	m_runningList.destroyAll();
}

Begin_Event_Map(CTaskDispatcher)
Event_List_Map(m_runningList, "TaskCompleted", OnTaskCompleted)
Event_List_Map(m_runningList, "TaskStarted", OnTaskStarted)
Event_List_Map(m_runningList, "TaskPaused", OnTaskPaused)
Event_List_Map(m_runningList, "TaskStopped", OnTaskStopped)
// 	if(e->getEventId()!="")
// 	{
// 		if(e->getEventId()=="TaskCompleted")
// 		{
// 			OnTaskCompleted(e);
// 			return 0;
// 		}
// 		else if(e->getEventId()=="TaskStarted")
// 		{
// 			OnTaskStarted(e);
// 			return 0;
// 		}
// 		else if(e->getEventId()=="TaskPaused")
// 		{
// 			OnTaskPaused(e);
// 			return 0;
// 		}
// 		else if(e->getEventId()=="TaskStopped")
// 		{
// 			OnTaskStopped(e);
// 			return 0;
// 		}
// 	}
End_Event_Map()

void CTaskDispatcher::addTask( ITask *task )
{
	if(!task)
		return;

	task->TaskCompleted+=this;
	m_waitList.push_back(task);

	m_totalTaskCount++;
}

BOOL CTaskDispatcher::start()
{
	m_lock.Lock();
	int count=min((int)m_waitList.size(), m_maxRunningTaskCount);
	if(count>0)
		addTaskToRunning(count);
	m_lock.Unlock();

	return TRUE;
}

BOOL CTaskDispatcher::pause()
{
	for(int i=0;i<(int)m_runningList.size();i++)
	{
		ITask *task=m_runningList.at(i);
		if(!task)
			continue;

		task->pause();
	}
	return TRUE;
}

BOOL CTaskDispatcher::stop()
{
	for(int i=0;i<(int)m_runningList.size();i++)
	{
		ITask *task=m_runningList.at(i);
		if(!task)
			continue;
		
		task->stop();
	}
	return TRUE;
}

void CTaskDispatcher::OnTaskCompleted( IEvent *e )
{
	if(!e)
		return;

	ITask *task=(ITask *)e->getSender();
	if(!task)
		return;

	if(!m_runningList.contain(task))
		return;

	m_lock.Lock();
	removeTaskToDone((ITask *)e->getSender());
	addTaskToRunning(1);
	m_lock.Unlock();

	// 计算任务进度
	int progress=(int)(m_doneList.size()*100.0/(m_runningList.size()+m_waitList.size()));
	if(progress>100)
		progress=100;
	else if(progress<0)
		progress=0;

	IEvent progressE(this, "DispatchProgress", progress);
	TotalTaskProgress.raiseEvent(this, &progressE);

	if(m_runningList.size()<=0)
	{
		IEvent e(this, "DispatchCompleted");
		DispatchCompleted.raiseEvent(this, &e);
	}
}

void CTaskDispatcher::OnTaskStarted(IEvent *e)
{

}

void CTaskDispatcher::OnTaskPaused(IEvent *e)
{

}

void CTaskDispatcher::OnTaskStopped(IEvent *e)
{

}

void CTaskDispatcher::setMaxRunningTaskCount( int val )
{
	if(val>0 && val!=m_maxRunningTaskCount)
	{
		if(m_isStarted)
		{
			m_lock.Lock();
			arrangeTask(m_maxRunningTaskCount);
			m_lock.Unlock();
		}

		m_maxRunningTaskCount = val;
	}
}

void CTaskDispatcher::arrangeTask( int maxRunningTaskCountNew )
{
	int count=maxRunningTaskCountNew-m_maxRunningTaskCount;
	if(count>0)
	{
		addTaskToRunning(count);
	}
	else
	{
		count=-count;
		removeTaskToWait(count);
	}
}

void CTaskDispatcher::addTaskToRunning( int count )
{
	int minn=min((int)m_waitList.size(), count);
	if(minn>0)
	{
		for(int i=0;i<minn;i++)
		{
			ITask *task=m_waitList.at(0);
			m_waitList.remove(0);

			if(!task)
				continue;

			m_runningList.push_back(task);
			task->start();
		}
	}
}

void CTaskDispatcher::removeTaskToWait( int count )
{
	int minn=min((int)m_runningList.size(), count);
	if(minn>0)
	{
		for(int i=0;i<minn;i++)
		{
			ITask *task=m_runningList.at(m_runningList.size()-1);
			m_runningList.remove(m_runningList.size()-1);
			task->pause();
			m_waitList.insert(m_waitList.begin(), task);
		}
	}
}

void CTaskDispatcher::removeTaskToDone( ITask *task )
{
	if(!task)
		return;

	m_runningList.remove(task);
	m_doneList.push_back(task);
}
