// B.cpp: implementation of the CB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EVENTEMU.h"
#include "B.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CB::CB()
{

}

CB::~CB()
{

}

void CB::raiseF1()
{
	IEvent e(this, "F1");
	OnF1.raiseEvent(this, &e);
}

void CB::raiseF2()
{
	IEvent e(this, "F2");
	OnF2.raiseEvent(this, &e);
}

void CB::raise3()
{
	IEvent e(this, "3");
	On3.raiseEvent(this, &e);
}
