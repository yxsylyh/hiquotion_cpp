// TaskThread1.h: interface for the CTaskThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASKTHREAD1_H__0B9C7C6F_A76F_48BF_A7B2_EF525D81B521__INCLUDED_)
#define AFX_TASKTHREAD1_H__0B9C7C6F_A76F_48BF_A7B2_EF525D81B521__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\MultiThreadLib\ThreadBase.h>
#include "ITask.h"

class CTaskThread : public CThreadBase  
{
public:
	CTaskThread();
	virtual ~CTaskThread();
	
	std::string getErrMsg() const { return m_errMsg; }

	ITask * getTask() const { return m_task; }
	void setTask(ITask * val) { m_task = val; }

private:
	UINT threadRun();

protected:
	std::string m_errMsg;
	ITask *m_task;
};

#endif // !defined(AFX_TASKTHREAD1_H__0B9C7C6F_A76F_48BF_A7B2_EF525D81B521__INCLUDED_)
