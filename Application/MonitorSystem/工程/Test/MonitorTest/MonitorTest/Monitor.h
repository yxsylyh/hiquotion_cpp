#pragma once

#include "imonitedobject.h"
#include "ialertor.h"

void CALLBACK OnTimer(HWND hWnd,UINT nMsg,UINT_PTR nTimerid,DWORD dwTime);

class CMonitor
{
public:
	CMonitor(void);
	CMonitor(IMonitedObject *monitedObject, IAlertor *alertor, int interval=60, int times=1);
	~CMonitor(void);

// 	BOOL readConfig();
	BOOL start();
	void stop();
	void monite();

protected:

public:
	IMonitedObject *MonitedObject;
	IAlertor *Alertor;
	int Interval;
	int Times;

private:
	int m_timerId;

	int m_currTimes;
};
