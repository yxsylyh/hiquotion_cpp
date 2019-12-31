#include "stdafx.h"
#include "JRTPExt.h"

CJRTPExt::CJRTPExt(void)
: m_payloadType(0), m_isWaitMark(TRUE)
{
	m_multiSendBuffer=new char[JRTP_MAX_PACKAGE_LENGTH];

#ifdef WIN32
	WSADATA dat;
	WSAStartup(MAKEWORD(2,2),&dat);
#endif // WIN32
}

CJRTPExt::~CJRTPExt(void)
{
	delete m_multiSendBuffer;

	BYEDestroy(RTPTime(10,0),0,0);

#ifdef WIN32
	WSACleanup();
#endif // WIN32
}

int CJRTPExt::SendPacket(const void *data,size_t len, uint8_t pt,uint32_t timestampinc)
{
	if(len<=JRTP_MAX_PACKAGE_LENGTH)
		return RTPSession::SendPacket(data, len, pt, true, timestampinc);

	int rest=len % JRTP_MAX_PACKAGE_LENGTH;
	int count=len / JRTP_MAX_PACKAGE_LENGTH;
// 	int lastPackage=count-1;
// 	if(rest>0)
// 		lastPackage++;

	m_buffer4Sending.init();

	m_buffer4Sending.write((char *)data, len);

	int ret=0;
	bool lastPackageFlag=false;
	for(int i=0;i<count;i++)
	{
		BOOL ret=m_buffer4Sending.read(m_multiSendBuffer, JRTP_MAX_PACKAGE_LENGTH);
		if(i==count-1 && rest==0)
			lastPackageFlag=true;
		else
			lastPackageFlag=false;
		ret=RTPSession::SendPacket(m_multiSendBuffer, JRTP_MAX_PACKAGE_LENGTH, pt, lastPackageFlag, timestampinc);
		if(ret!=0)
		{
			return ret;
		}

		Sleep(1);

	}
	if(rest>0)
	{
		m_buffer4Sending.read(m_multiSendBuffer, rest);
		ret=RTPSession::SendPacket(m_multiSendBuffer, rest, pt, true, timestampinc);
	}
	return ret;
}

// 初始化缓冲区
void CJRTPExt::initBuffer()
{
	// 	m_buffer.redimBufferSize(10240000, FALSE);
	m_buffer4Sending.init();
	m_buffer4Receiving.init();
}

void CJRTPExt::setPayloadType(int payloadType)
{
	m_payloadType=payloadType;
}

void CJRTPExt::OnNewSource(RTPSourceData *dat)
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

void CJRTPExt::OnBYEPacket(RTPSourceData *dat)
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

void CJRTPExt::OnPollThreadStep()
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

void CJRTPExt::ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack)
{
	// You can inspect the packet and the source's info here
	// 	uint32_t num=rtppack.GetExtendedSequenceNumber();
	// 	uint32_t ssrc=srcdat.GetSSRC();

	char *data=(char *)rtppack.GetPayloadData();
	if(!data)
		return;

	int length=rtppack.GetPayloadLength();
	if(length<=0)
		return;

	uint8_t pt=rtppack.GetPayloadType();
	if(pt!=m_payloadType)
		return;

	CString ip="127.0.0.1";
	const RTPIPv4Address *addr=(RTPIPv4Address *)srcdat.GetRTPDataAddress();
	if(addr)
	{
		uint32_t nip=addr->GetIP();
		in_addr  inaddr; 
		inaddr.s_addr=nip; 
		ip=inet_ntoa(inaddr); 
	}

	// 如果不需要等待最后一包，则直接抛出事件
	if(!m_isWaitMark)
	{
		CJRTPReceiverEvent e(this, "JrtpDataGot", (LPTSTR)(LPCSTR)ip, data, length, rtppack.GetTimestamp());
		DataGot.raiseEvent(this, &e);
		return;
	}

	// 否则，把数据写到缓冲区
	m_buffer4Receiving.write((char *)rtppack.GetPayloadData(), rtppack.GetPayloadLength());

	// 如果是最后一包，则取出缓冲区中的所有数据，并抛出事件
	if(rtppack.HasMarker())  // 为真，表示是最后一包
	{
		int len=m_buffer4Receiving.getDataLength();
		CJRTPReceiverEvent e(this, "JrtpDataGot", (LPTSTR)(LPCSTR)ip, m_buffer4Receiving.getCycledBuffer(), len, rtppack.GetTimestamp());
		DataGot.raiseEvent(this, &e);
		m_buffer4Receiving.init();
	}

	// 	std::cout << "Got packet " << rtppack.GetExtendedSequenceNumber() << " from SSRC " << srcdat.GetSSRC() << std::endl;
}


CJRTPReceiverEvent::CJRTPReceiverEvent(IEventRaisable *sender, string eventId, string ip, char *buffer, int bufferLength, unsigned int timestamp)
: IEvent(sender, eventId), m_ip(ip), m_buffer(buffer), m_bufferLength(bufferLength), m_timestamp(timestamp)
{
}

CJRTPReceiverEvent::~CJRTPReceiverEvent(void)
{
}
