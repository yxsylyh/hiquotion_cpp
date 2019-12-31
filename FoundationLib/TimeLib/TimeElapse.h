#pragma once

class CTimeElapse
{
public:
	CTimeElapse(void);
	~CTimeElapse(void);

	void start();     // 如果status不是0，则直接返回，否则置为1
	void end();       // 如果status不是1，则直接返回，否则置为2
	int getElapse();  // 如果status不是2，则返回0，否则置为0

private:
	DWORD m_start;
	DWORD m_end;

	int m_status; // 0：初始化，1：调用了start，2：调用了end，只有在2的时候，才可以取时间差
};
