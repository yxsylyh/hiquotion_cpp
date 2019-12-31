#include "stdafx.h"
#include "AudioData4PlayThread.h"

CAudioData4PlayThread::CAudioData4PlayThread(void)
{
}

CAudioData4PlayThread::~CAudioData4PlayThread(void)
{
}

// 判断数据是否足够
BOOL CAudioData4PlayThread::isDataEnough()
{
	if(m_cycledBuffer.getDataLength()<=100)
		return FALSE;

	return TRUE;
}

// 数据足够时，可以拿出的数据长度
unsigned int CAudioData4PlayThread::getEnoughDataLength()
{
	return m_cycledBuffer.getDataLength();
}
