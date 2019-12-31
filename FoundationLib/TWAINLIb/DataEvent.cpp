#include "stdafx.h"
#include "DataEvent.h"

CDataEvent::CDataEvent(IEventRaisable* sender, string eventId)
	: IEvent(sender, eventId), m_data(NULL), m_dataLength(0)
{

}

CDataEvent::CDataEvent(IEventRaisable* sender, string eventId, char* data, long dataLength)
	: IEvent(sender, eventId), m_data(data), m_dataLength(dataLength)
{

}

CDataEvent::~CDataEvent()
{

}
