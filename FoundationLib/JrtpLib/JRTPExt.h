#pragma once

// for sending

#include <C++\3rdParty\jrtplib3\jrtplib3.h>
#include <c++\foudationlib\bufferlib\cycledbuffer.h>

#define JRTP_MAX_PACKAGE_LENGTH 1200

#define TIME_STAMP 16


// for receiving

#include <C++/FoudationLib/eventlib/eventemu-仿mfc的事件处理/ieventraisable.h>
#include <C++/FoudationLib/eventlib/eventemu-仿mfc的事件处理/delegate.h>
#include <C++\3rdParty\jrtplib3\rtppacket.h>
#include <C++\3rdParty\jrtplib3\rtpsourcedata.h>
#include <c++/foudationlib/bufferlib/cycledbuffer.h>


class CJRTPExt :
	public RTPSession, public IEventRaisable
{
public:
	CJRTPExt(void);
	~CJRTPExt(void);

	// for sending

	int SendPacket(const void *data,size_t len, uint8_t pt,uint32_t timestampinc);

	// for receiving

	// 接收到的数据，首先判断 PayloadType 值是否与事先已指定 PayloadType 值相同
	// 如果相同，则放入缓冲区
	// 如果是最后一包，则抛出收到数据的事件，事件参数是继承 IEvent 接口的 
	// 初始化缓冲区
	void initBuffer();

	void setPayloadType(int payloadType);

	BOOL isWaitMark() const { return m_isWaitMark; }
	void setWaitMark(BOOL val) { m_isWaitMark = val; }

	CDelegate DataGot;
	CDelegate ByePacket;
	CDelegate NewSource;

private:
	char *m_multiSendBuffer;
	CCycledBuffer m_buffer4Sending;

protected:
	void OnPollThreadStep();
	// 在这里处理收到的包，判断类型是否正确，数据是否足够（对于一包数据来说），以及是否需要抛出数据到达的事件等等
	void ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack);
	// 继承该方法，实现代码要先执行 CJrtpSession::OnNewSource(data); 然后再执行自己的代码
	void OnNewSource(RTPSourceData *dat);
	// 继承该方法，实现代码要先执行 CJrtpSession::OnBYEPacket(data); 然后再执行自己的代码
	void OnBYEPacket(RTPSourceData *dat);

private:

#define H264  96
#define G729A 18

	int m_payloadType;

	CCycledBuffer m_buffer4Receiving;

	BOOL m_isWaitMark;
};

class CJRTPReceiverEvent :
	public IEvent
{
public:
	CJRTPReceiverEvent(IEventRaisable *sender, string eventId, string ip, char *buffer, int bufferLength, unsigned int timestamp);
	~CJRTPReceiverEvent(void);

	char *getBuffer() const { return m_buffer; }
	int getBufferLength() const { return m_bufferLength; }
	string getIp() const { return m_ip; }
	unsigned int getTimestamp() const { return m_timestamp; }

private:
	string m_ip;
	char *m_buffer;
	int m_bufferLength;
	unsigned int m_timestamp;
};
