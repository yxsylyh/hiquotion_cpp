// TaskBase.cpp: implementation of the CTaskBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ITask.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ITask::ITask()
: m_taskStatus(TASK_CREATED)
{

}

ITask::~ITask()
{

}

BOOL ITask::start()
{
	m_taskStatus=TASK_STARTED;
	IEvent e(this, "TaskStarted");
	TaskStarted.raiseEvent(this, &e);
	return TRUE;
}

BOOL ITask::pause()
{
	m_taskStatus=TASK_PAUSED;
	IEvent e(this, "TaskPaused");
	TaskPaused.raiseEvent(this, &e);
	return TRUE;
}

void ITask::stop()
{
	m_taskStatus=TASK_STOPPED;
	IEvent e(this, "TaskStopped");
	TaskStopped.raiseEvent(this, &e);
}
