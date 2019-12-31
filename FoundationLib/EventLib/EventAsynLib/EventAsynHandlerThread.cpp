// EventAsynHandlerThread.cpp: implementation of the CEventAsynHandlerThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EventAsynHandlerProject.h"
#include "EventAsynHandlerThread.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEventAsynHandlerThread::CEventAsynHandlerThread(CProductorConsumerPattern<IEvent *> *consumer)
: m_consumer(consumer)
{

}

CEventAsynHandlerThread::~CEventAsynHandlerThread()
{

}

UINT CEventAsynHandlerThread::threadRun()
{
	if(!m_consumer)
		return 0;

	while(m_status==Running)
	{
		IEvent *e=NULL;
		m_consumer->comsume(&e);
		if(!e)
			return 0;

		Consume.raiseEvent(this, e);
	}

	return 1;
}
