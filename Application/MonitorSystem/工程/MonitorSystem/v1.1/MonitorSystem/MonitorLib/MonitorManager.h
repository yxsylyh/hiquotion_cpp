#pragma once

#include "monitor.h"

class CMonitorManager :
	public vector<CMonitor *>
{
public:
	CMonitorManager(void);
	~CMonitorManager(void);

	void startAll();
	void start(int index);
	void stopAll();
	void stop(int index);

	void setEventLogPath(CString path);
};
