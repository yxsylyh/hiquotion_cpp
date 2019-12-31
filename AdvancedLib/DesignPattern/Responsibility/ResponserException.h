// ResponserException.h: interface for the CResponserException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESPONSEREXCEPTION_H__3D743092_E361_4531_98EE_E26A617E6900__INCLUDED_)
#define AFX_RESPONSEREXCEPTION_H__3D743092_E361_4531_98EE_E26A617E6900__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CResponserException  
{
public:
	CResponserException(CString errMessage);
	virtual ~CResponserException();

	CString getErrMessage() const { return m_errMessage; }
// 	void setErrMessage(CString val) { m_errMessage = val; }

protected:
	CString m_errMessage;
};

#endif // !defined(AFX_RESPONSEREXCEPTION_H__3D743092_E361_4531_98EE_E26A617E6900__INCLUDED_)
