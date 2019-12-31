#include "stdafx.h"
#include "AudioG729AGetData4EncodeThread.h"

CAudioG729AGetData4EncodeThread::CAudioG729AGetData4EncodeThread(void)
{
	m_cycledBuffer.redimLength(1024000, FALSE);
}

CAudioG729AGetData4EncodeThread::~CAudioG729AGetData4EncodeThread(void)
{
}

// 判断数据是否足够
BOOL CAudioG729AGetData4EncodeThread::isDataEnough()
{
	if(m_cycledBuffer.getDataLength()<160)
		return FALSE;
	
	return TRUE;
}

// 数据足够时，可以拿出的数据长度
unsigned int CAudioG729AGetData4EncodeThread::getEnoughDataLength()
{
// 	unsigned int length=m_cycledBuffer.getDataLength();
// 	unsigned int count=length/160;
// 	length=count*160;
// 	return length;
	return m_cycledBuffer.getDataLength()/160*160;
// 	return 480;
}
