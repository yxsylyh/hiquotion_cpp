// IEventHandler.cpp: implementation of the IEventHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IEventHandler.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IEventHandler::IEventHandler()
{

}

IEventHandler::~IEventHandler()
{

}

int IEventHandler::handleEvent(IEventRaisable *sender, IEvent *e)
{
	return 0;
}
