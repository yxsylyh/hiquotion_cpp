// TaskThread1.cpp: implementation of the CTaskThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TaskThreadLib.h"
#include "TaskThread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaskThread::CTaskThread()
: m_errMsg(""), m_task(NULL)
{

}

CTaskThread::~CTaskThread()
{

}

UINT CTaskThread::threadRun()
{
	if(!m_task)
	{
		m_errMsg="任务指针为空！";
		return -1;
	}

	int ret=m_task->doTask();
	m_errMsg=m_task->getErrMsg();

	return ret;
}