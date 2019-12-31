// TaskBase.h: interface for the CTaskBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKBASE_H__2A25215C_B329_4543_8DA9_ADF244EB2C18__INCLUDED_)
#define AFX_TASKBASE_H__2A25215C_B329_4543_8DA9_ADF244EB2C18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\IEventRaisable.h>
#include <C++\FoudationLib\EventLib\EventEmu-仿MFC的事件处理\Delegate.h>

enum TaskStatus
{
	TASK_CREATED,
	TASK_STARTED,
	TASK_PAUSED,
	TASK_STOPPED,
};

class ITask : public IEventRaisable
{
public:
	ITask();
	virtual ~ITask();

	virtual BOOL start();
	virtual BOOL pause();
	virtual void stop();

	CDelegate TaskStarted;
	CDelegate TaskPaused;
	CDelegate TaskStopped;
	CDelegate TaskCompleted;
	CDelegate TaskProgress;

	TaskStatus getTaskStatus() const { return m_taskStatus; }

protected:
	TaskStatus m_taskStatus;
};

#endif // !defined(AFX_TASKBASE_H__2A25215C_B329_4543_8DA9_ADF244EB2C18__INCLUDED_)
