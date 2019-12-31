#include "stdafx.h"
#include "EventThread.h"

CEventThread::CEventThread(void)
{
}

CEventThread::~CEventThread(void)
{
}

void CEventThread::raiseEvent(IEventRaisable *sender, std::string eventId, int ret, std::string msg)
{
	IEvent e(sender, eventId, ret, msg);
	ThreadCompleted.raiseEvent(this, &e);
}
