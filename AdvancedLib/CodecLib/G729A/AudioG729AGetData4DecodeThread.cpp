#include "stdafx.h"
#include "AudioG729AGetData4DecodeThread.h"

CAudioG729AGetData4DecodeThread::CAudioG729AGetData4DecodeThread(void)
{
}

CAudioG729AGetData4DecodeThread::~CAudioG729AGetData4DecodeThread(void)
{
}

// 判断数据是否足够
BOOL CAudioG729AGetData4DecodeThread::isDataEnough()
{
	if(m_cycledBuffer.getDataLength()<10)
		return FALSE;
	
	return TRUE;
}

// 数据足够时，可以拿出的数据长度
unsigned int CAudioG729AGetData4DecodeThread::getEnoughDataLength()
{
// 	unsigned int length=m_cycledBuffer.getDataLength();
// 	unsigned int count=length/10;
// 	length=count*10;
// 	return length;
	return m_cycledBuffer.getDataLength()/10*10;
}
