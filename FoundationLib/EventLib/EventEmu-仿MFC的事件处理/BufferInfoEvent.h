#pragma once
#include "ievent.h"

class CBufferInfoEvent :
	public IEvent
{
public:
	CBufferInfoEvent(void);
	CBufferInfoEvent(IEventRaisable *sender, string eventId, char *data, int bufferLength, int returnCode=0, string returnMessage="");
	~CBufferInfoEvent(void);

	char * getBuffer() const { return m_buffer; }
	int getBufferLength() const { return m_bufferLength; }

private:
	char *m_buffer;
	int m_bufferLength;
};
