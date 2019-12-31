#pragma once

// #include <C++\3rdParty\jrtplib3\rtpsession.h>
#include <C++\3rdParty\jrtplib3\jrtplib3.h>
#include <c++\foudationlib\bufferlib\cycledbuffer.h>

#define JRTP_MAX_PACKAGE_LENGTH 1200

#define TIME_STAMP 16

class CJRTPSender :
	public RTPSession
{
public:
	CJRTPSender(void);
	~CJRTPSender(void);

	int SendPacket(const void *data,size_t len, uint8_t pt,uint32_t timestampinc);

private:
	char *m_multiSendBuffer;
	CCycledBuffer m_buffer;
};
