#pragma once
#include <C++/FoundationLib/EventLib/EventEmu-仿MFC的事件处理/IEvent.h>

class CDataEvent :
	public IEvent
{
public:
	CDataEvent(IEventRaisable* sender, string eventId);
	CDataEvent(IEventRaisable* sender, string eventId, char* data, long dataLength);
	~CDataEvent();

	char* getData() const { return m_data; }
	void setData(char* val) { m_data = val; }
	long getDataLength() const { return m_dataLength; }
	void setDataLength(long val) { m_dataLength = val; }

protected:
	char* m_data;
	long m_dataLength;
};

