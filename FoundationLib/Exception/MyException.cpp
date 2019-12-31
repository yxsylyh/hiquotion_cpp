// Exception.cpp: implementation of the CException class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyException::CMyException(eExceptionType exceptionType,string description,string reason,string reason4Debug)
{
	m_exceptionType=exceptionType;
	m_description=description;
	m_reason=reason;
	m_reason4Debug=reason4Debug;
}

CMyException::~CMyException()
{

}

void CMyException::showMessage()
{
	switch(m_exceptionType)
	{
// 		EXCEPTION_UNKNOWN,  //  0
// 		EXCEPTION_INTERNAL, // 1
// 		EXCEPTION_EXTERNAL, // 2

		// 未知异常，没啥说的
		// 内部异常，与用户操作有关但没有直接关系的异常
			// 这时候，如果程序处于调试状态，则显示 m_reason4Debug 的出错原因，便于调试；否则不显示 m_reason4Debug。
		// 外部异常，与用户操作直接关系的异常

		case EXCEPTION_UNKNOWN:
			showUnknownMessage();
			break;
		case EXCEPTION_INTERNAL:
			showInternalMessage();
			break;
		case EXCEPTION_EXTERNAL:
			showExternalMessage();
			break;
	}
}

string CMyException::toString(BOOL showDebugReason)
{
	string str="\n异常输出：\n异常类型：";
	switch(m_exceptionType)
	{
		case EXCEPTION_UNKNOWN:
			str+="未知异常";
			break;
		case EXCEPTION_INTERNAL:
			str+="内部异常";
			break;
		case EXCEPTION_EXTERNAL:
			str+="外部异常";
			break;
	}
	str+="\n异常描述："+m_description;
	str+="\n异常原因："+m_reason;
	if(showDebugReason)
		str+="\n异常原因(调试环境)："+m_reason4Debug;
	str+="\n异常输出完毕\n";

	return str;
}

void CMyException::showUnknownMessage()
{
	AfxMessageBox("程序遇到未知异常");
}

void CMyException::showInternalMessage()
{
	string msg="程序运行期间遇到了下面的异常，如果给您带来了不便，我们深表歉意。\n\n";
	msg = msg + "异常描述：" + m_description +"\n\n";
	msg = msg + "异常原因：" + m_reason +"\n\n";
#ifdef _DEBUG
	msg = msg + "调试信息：" + m_reason4Debug;
#endif
	AfxMessageBox(msg.c_str());
}

void CMyException::showExternalMessage()
{
	string msg="程序运行期间遇到了下面的异常，如果给您带来了不便，我们深表歉意。\n\n";
	msg = msg + "异常描述：" + m_description +"\n\n";
	msg = msg + "异常原因：" + m_reason;
	AfxMessageBox(msg.c_str());
}
