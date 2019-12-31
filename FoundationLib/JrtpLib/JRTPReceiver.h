#pragma once

#include <C++\3rdParty\jrtplib3\jrtplib3.h>
#include <C++/FoudationLib/eventlib/eventemu-仿mfc的事件处理/ieventraisable.h>
#include <C++/FoudationLib/eventlib/eventemu-仿mfc的事件处理/delegate.h>
#include <C++\3rdParty\jrtplib3\rtppacket.h>
#include <C++\3rdParty\jrtplib3\rtpsourcedata.h>
#include <c++/foudationlib/bufferlib/cycledbuffer.h>

#ifdef RTP_SUPPORT_THREAD
	#undef RTP_SUPPORT_THREAD
#endif

// JRTP 数据接收类
// 接收到的数据，首先判断 PayloadType 值是否与事先已指定 PayloadType 值相同
// 如果相同，则放入缓冲区
// 如果是最后一包，则抛出收到数据的事件，事件参数是继承 IEvent 接口的 CJRTPReceiverEvent 类
class CJRTPReceiver : public RTPSession, public IEventRaisable
{
public:
	CJRTPReceiver();
	~CJRTPReceiver(void);

	// 初始化缓冲区
	void initBuffer();

	void setPayloadType(int payloadType);

	CDelegate DataGot;
	CDelegate ByePacket;
	CDelegate NewSource;

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

	CCycledBuffer m_buffer;
};


class CJRTPReceiverEvent :
	public IEvent
{
public:
	CJRTPReceiverEvent(IEventRaisable *sender, string eventId, char *buffer, int bufferLength);
	~CJRTPReceiverEvent(void);

	char *getBuffer() const { return m_buffer; }
	int getBufferLength() const { return m_bufferLength; }

private:
	char *m_buffer;
	int m_bufferLength;
};
