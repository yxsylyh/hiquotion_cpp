// ITask.h: interface for the ITask class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITASK_H__AA32C61C_12E0_4686_AAEE_D4134B921E94__INCLUDED_)
#define AFX_ITASK_H__AA32C61C_12E0_4686_AAEE_D4134B921E94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ITask  
{
public:
	ITask();
	virtual ~ITask();

	virtual int doTask(){ return 0;};

	std::string getErrMsg() const { return m_errMsg; }
protected:
	std::string m_errMsg;

};

#endif // !defined(AFX_ITASK_H__AA32C61C_12E0_4686_AAEE_D4134B921E94__INCLUDED_)
