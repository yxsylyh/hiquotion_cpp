// IResponser.cpp: implementation of the IResponser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Responsibility.h"
#include "IResponser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IResponser::IResponser()
{

}

IResponser::~IResponser()
{

}

BOOL IResponser::handleRequest(IRequest *request)
{
	return FALSE;
}
