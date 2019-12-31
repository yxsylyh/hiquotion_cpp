// MyException.h: interface for the CMyException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYEXCEPTION_H__77B9451D_4B03_49F1_BAFA_4D8BAC71851C__INCLUDED_)
#define AFX_MYEXCEPTION_H__77B9451D_4B03_49F1_BAFA_4D8BAC71851C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum eExceptionType
{
	// 未知异常，没啥说的
	// 内部异常，与用户操作有关但没有直接关系的异常
	// 这时候，如果程序处于调试状态，则显示 m_reason4Debug 的出错原因，便于调试；否则不显示 m_reason4Debug。
	// 外部异常，与用户操作直接关系的异常

	EXCEPTION_UNKNOWN,  //  0
	EXCEPTION_INTERNAL, // 1
	EXCEPTION_EXTERNAL, // 2
};

class CMyException 
{
public:
	CMyException(eExceptionType exceptionType,string description="",string reason="",string reason4Debug="");
	virtual ~CMyException();

	void showMessage();
	string toString(BOOL showDebugReason=FALSE);

	string m_description;
	string m_reason;
	string m_reason4Debug;   // 说明出错在哪个文件，哪个类，哪个方法里、或调用什么的时候出现的异常，便于调试的时候定位

protected:
	void showUnknownMessage();
	void showInternalMessage();
	void showExternalMessage();

	eExceptionType m_exceptionType;

};

#endif // !defined(AFX_MyEXCEPTION_H__77B9451D_4B03_49F1_BAFA_4D8BAC71851C__INCLUDED_)
