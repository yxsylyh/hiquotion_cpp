#pragma once

#include <vector>

// 时间计数器
class CTimeCounter
{
public:
	CTimeCounter(void);
	~CTimeCounter(void);

	void init();
	void addTime(DWORD time);
	void addTime(DWORD time, int times);
	int getCount();
	float getAverage();
	DWORD getSum();

	CString toCString();

private:
	vector<DWORD> m_counter;
	DWORD m_sum;
	float m_average;
	int m_count;
};
