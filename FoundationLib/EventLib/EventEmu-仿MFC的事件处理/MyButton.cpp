// Button.cpp: implementation of the CButton class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EVENTEMU.h"
#include "MyButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyButton::CMyButton()
{

}

CMyButton::~CMyButton()
{

}

void CMyButton::Clicked()
{
	IEvent e(this, "Clicked");
	Click.raiseEvent(this, &e);
}

void CMyButton::MousePressed()
{
	IEvent e(this, "MousePressed");
	MousePress.raiseEvent(this, &e);
}
