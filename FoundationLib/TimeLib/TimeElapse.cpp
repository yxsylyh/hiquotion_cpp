#include "StdAfx.h"
#include "TimeElapse.h"

CTimeElapse::CTimeElapse(void)
{
	m_status=0;
	m_start=0;
	m_end=0;
}

CTimeElapse::~CTimeElapse(void)
{
}

// 如果status不是0，则直接返回，否则置为1
void CTimeElapse::start()
{
	if(m_status!=0)
		return;

	m_start=GetTickCount();
	m_status=1;
}

// 如果status不是1，则直接返回，否则置为2
void CTimeElapse::end()
{
	if(m_status!=1)
		return;

	m_end=GetTickCount();
	m_status=2;
}

// 如果status不是2，则返回0，否则置为0
int CTimeElapse::getElapse()
{
	if(m_status!=2)
		return 0;

	int interval=m_end-m_start;
	m_start=0;
	m_end=0;
	m_status=0;

	return interval;
}
