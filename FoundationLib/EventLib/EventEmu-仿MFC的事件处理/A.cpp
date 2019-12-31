// A.cpp: implementation of the CA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EVENTEMU.h"
#include "A.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CA::CA()
{

}

CA::~CA()
{

}

void CA::raiseE1()
{
	IEvent e(this, "E1");
	OnE1.raiseEvent(this, &e);
}

void CA::raiseE2()
{
	IEvent e(this, "E2");
	OnE2.raiseEvent(this, &e);
}

void CA::raise3()
{
	IEvent e(this, "3");
	On3.raiseEvent(this, &e);
}
