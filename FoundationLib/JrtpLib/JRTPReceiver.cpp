#include "StdAfx.h"
#include "JRTPReceiver.h"

CJRTPReceiver::CJRTPReceiver()
: m_payloadType(0)
{
#ifdef WIN32
	WSADATA dat;
	WSAStartup(MAKEWORD(2,2),&dat);
#endif // WIN32
}

CJRTPReceiver::~CJRTPReceiver(void)
{
	BYEDestroy(RTPTime(10,0),0,0);

#ifdef WIN32
	WSACleanup();
#endif // WIN32
}

// 初始化缓冲区
void CJRTPReceiver::initBuffer()
{
// 	m_buffer.redimBufferSize(10240000, FALSE);
	m_buffer.init();
}

void CJRTPReceiver::setPayloadType(int payloadType)
{
	m_payloadType=payloadType;
}

void CJRTPReceiver::OnNewSource(RTPSourceData *dat)
{
	if (dat->IsOwnSSRC())
		return;

	uint32_t ip;
	uint16_t port;

	if (dat->GetRTPDataAddress() != 0)
	{
		const RTPIPv4Address *addr = (const RTPIPv4Address *)(dat->GetRTPDataAddress());
		ip = addr->GetIP();
		port = addr->GetPort();

		IEvent e(this, "JrtpNewSource");
		NewSource.raiseEvent(this, &e);

	}
	else if (dat->GetRTCPDataAddress() != 0)
	{
		const RTPIPv4Address *addr = (const RTPIPv4Address *)(dat->GetRTCPDataAddress());
		ip = addr->GetIP();
		port = addr->GetPort()-1;
	}
	else
		return;

	RTPIPv4Address dest(ip,port);
	AddDestination(dest);

	struct in_addr inaddr;
	inaddr.s_addr = htonl(ip);
	std::cout << "Adding destination " << std::string(inet_ntoa(inaddr)) << ":" << port << std::endl;
}

void CJRTPReceiver::OnBYEPacket(RTPSourceData *dat)
{
	if (dat->IsOwnSSRC())
		return;

	uint32_t ip;
	uint16_t port;

	if (dat->GetRTPDataAddress() != 0)
	{
		const RTPIPv4Address *addr = (const RTPIPv4Address *)(dat->GetRTPDataAddress());
		ip = addr->GetIP();
		port = addr->GetPort();

		IEvent e(this, "JrtpByePacket");
		ByePacket.raiseEvent(this, &e);

	}
	else if (dat->GetRTCPDataAddress() != 0)
	{
		const RTPIPv4Address *addr = (const RTPIPv4Address *)(dat->GetRTCPDataAddress());
		ip = addr->GetIP();
		port = addr->GetPort()-1;
	}
	else
		return;

	RTPIPv4Address dest(ip,port);
	DeleteDestination(dest);

	struct in_addr inaddr;
	inaddr.s_addr = htonl(ip);
	std::cout << "Deleting destination " << std::string(inet_ntoa(inaddr)) << ":" << port << std::endl;
}

void CJRTPReceiver::OnPollThreadStep()
{
	BeginDataAccess();

	// check incoming packets
	if (GotoFirstSourceWithData())
	{
		do
		{
			RTPPacket *pack;
			RTPSourceData *srcdat;

			srcdat = GetCurrentSourceInfo();

			while ((pack = GetNextPacket()) != NULL)
			{
				ProcessRTPPacket(*srcdat,*pack);
				DeletePacket(pack);
			}
		} while (GotoNextSourceWithData());
	}

	EndDataAccess();
}

void CJRTPReceiver::ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack)
{
	// You can inspect the packet and the source's info here
// 	uint32_t num=rtppack.GetExtendedSequenceNumber();
// 	uint32_t ssrc=srcdat.GetSSRC();

	if(!rtppack.GetPayloadData())
		return;

	if(rtppack.GetPayloadLength()<=0)
		return;

	uint8_t pt=rtppack.GetPayloadType();
	if(pt!=m_payloadType)
		return;

	int length=rtppack.GetPayloadLength();

	m_buffer.write((char *)rtppack.GetPayloadData(), rtppack.GetPayloadLength());

	if(rtppack.HasMarker())  // 为真，表示是最后一包
	{
		int len=m_buffer.getDataLength();
		CJRTPReceiverEvent e(this, "JrtpDataGot", m_buffer.getCycledBuffer(), len);
		DataGot.raiseEvent(this, &e);
		m_buffer.init();
	}

// 	std::cout << "Got packet " << rtppack.GetExtendedSequenceNumber() << " from SSRC " << srcdat.GetSSRC() << std::endl;
}


CJRTPReceiverEvent::CJRTPReceiverEvent(IEventRaisable *sender, string eventId, char *buffer, int bufferLength)
: IEvent(sender, eventId)
{
	m_buffer=buffer;
	m_bufferLength=bufferLength;
}

CJRTPReceiverEvent::~CJRTPReceiverEvent(void)
{
}
