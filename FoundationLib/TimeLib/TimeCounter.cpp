#include "StdAfx.h"
#include "TimeCounter.h"

CTimeCounter::CTimeCounter(void)
{
	init();
}

CTimeCounter::~CTimeCounter(void)
{
}

void CTimeCounter::init()
{
	m_sum=0;
	m_counter.clear();
	m_average=0;
	m_count=0;
}

void CTimeCounter::addTime(DWORD time)
{
	m_counter.push_back(time);
	m_sum+=time;
	m_count++;
	m_average=(float)m_sum/(float)m_count;
}

void CTimeCounter::addTime(DWORD time, int times)
{
	m_counter.push_back(time);
	m_sum+=time;
	m_count+=times;
	m_average=(float)m_sum/(float)m_count;
}

int CTimeCounter::getCount()
{
	return m_count;
}

float CTimeCounter::getAverage()
{
	return m_average;
}

DWORD CTimeCounter::getSum()
{
	return m_sum;
}

CString CTimeCounter::toCString()
{
	CString tmp="";
	tmp.Format("%.1f(%d)",getAverage(),getCount());
	return tmp;
}
