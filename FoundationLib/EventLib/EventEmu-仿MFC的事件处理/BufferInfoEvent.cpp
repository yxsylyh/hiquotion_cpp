#include "StdAfx.h"
#include "BufferInfoEvent.h"

CBufferInfoEvent::CBufferInfoEvent(void)
: m_buffer(NULL), m_bufferLength(0)
{
}

CBufferInfoEvent::CBufferInfoEvent(IEventRaisable *sender, string eventId, char *data, int bufferLength, int returnCode, string returnMessage)
: IEvent(sender, eventId, returnCode, returnMessage), m_buffer(NULL), m_bufferLength(0)
{
	if(data && bufferLength>0)
	{
		m_buffer=new char[bufferLength];
		memcpy(m_buffer, data, bufferLength);
		m_bufferLength=bufferLength;
	}
}

CBufferInfoEvent::~CBufferInfoEvent(void)
{
}
