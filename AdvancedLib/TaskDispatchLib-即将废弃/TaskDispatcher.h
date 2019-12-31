// TaskDispatcher.h: interface for the CTaskDispatcher class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKDISPATCHER_H__9D56682D_4879_4D66_9D48_79EB0DBEAF34__INCLUDED_)
#define AFX_TASKDISPATCHER_H__9D56682D_4879_4D66_9D48_79EB0DBEAF34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventHandler.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEvent.h>
#include <C++\FoudationLib\DataStructLib\PointerList.h>
#include "ITask.h"
#include <afxmt.h>

class CTaskDispatcher : public IEventRaisable, public IEventHandler
{
public:
	CTaskDispatcher();
	virtual ~CTaskDispatcher();

	void addTask(ITask *task);

	BOOL start();
	BOOL pause();
	BOOL stop();

	int getMaxRunningTaskCount() const { return m_maxRunningTaskCount; }
	void setMaxRunningTaskCount(int val);

	CDelegate DispatchCompleted;
	CDelegate TotalTaskProgress;

protected:
	void OnTaskCompleted(IEvent *e);
	void OnTaskStarted(IEvent *e);
	void OnTaskPaused(IEvent *e);
	void OnTaskStopped(IEvent *e);

protected:
	Declare_Event_Map();

private:
	void arrangeTask(int maxRunningTaskCountNew);
	void addTaskToRunning(int count);
	void removeTaskToWait(int count);
	void removeTaskToDone(ITask *task);

private:
	CPointerList<ITask *> m_waitList;
	CPointerList<ITask *> m_runningList;
	CPointerList<ITask *> m_doneList;

	int m_maxRunningTaskCount;

	CCriticalSection m_lock;

	BOOL m_isStarted;

	int m_totalTaskCount;
};

#endif // !defined(AFX_TASKDISPATCHER_H__9D56682D_4879_4D66_9D48_79EB0DBEAF34__INCLUDED_)
