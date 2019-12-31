#pragma once

#include "interface\imonitedobject.h"
#include "interface\ialertor.h"
#include <FileLogLib\FileLogLib\FileLog.h>

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

	string toString();

	void setEventLogFile(string path);
	string getEventLogFile();

protected:

public:
	IMonitedObject *MonitedObject;
	IAlertor *Alertor;
	int Interval;
	int Times;

private:
	UINT_PTR m_timerId;

	int m_currTimes;

	CFileLog *m_eventLog;

	string m_eventLogFile;
};
