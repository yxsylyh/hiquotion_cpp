#include "stdafx.h"
#include "JRTPSender.h"

CJRTPSender::CJRTPSender(void)
{
	m_multiSendBuffer=new char[JRTP_MAX_PACKAGE_LENGTH];
}

CJRTPSender::~CJRTPSender(void)
{
	delete m_multiSendBuffer;
}

int CJRTPSender::SendPacket(const void *data,size_t len, uint8_t pt,uint32_t timestampinc)
{
	if(len<=JRTP_MAX_PACKAGE_LENGTH)
		return RTPSession::SendPacket(data, len, pt, true, timestampinc);

	int rest=len % JRTP_MAX_PACKAGE_LENGTH;
	int count=len / JRTP_MAX_PACKAGE_LENGTH;
// 	int lastPackage=count-1;
// 	if(rest>0)
// 		lastPackage++;

	m_buffer.init();

	m_buffer.write((char *)data, len);

	int ret=0;
	bool lastPackageFlag=false;
	for(int i=0;i<count;i++)
	{
		BOOL ret=m_buffer.read(m_multiSendBuffer, JRTP_MAX_PACKAGE_LENGTH);
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
		m_buffer.read(m_multiSendBuffer, rest);
		ret=RTPSession::SendPacket(m_multiSendBuffer, rest, pt, true, timestampinc);
	}
	return ret;
}
