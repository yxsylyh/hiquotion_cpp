// Button.h: interface for the CButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUTTON_H__3B57E9B7_C96E_47C8_8AF9_5C2B70F59CEE__INCLUDED_)
#define AFX_BUTTON_H__3B57E9B7_C96E_47C8_8AF9_5C2B70F59CEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IEventRaisable.h"
#include "Delegate.h"

class CMyButton : public IEventRaisable  
{
public:
	CMyButton();
	virtual ~CMyButton();

	void Clicked();
	void MousePressed();

	CDelegate Click;
	CDelegate MousePress;

};

#endif // !defined(AFX_BUTTON_H__3B57E9B7_C96E_47C8_8AF9_5C2B70F59CEE__INCLUDED_)
