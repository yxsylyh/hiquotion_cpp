#pragma once

#include "Monitor.h"

class CMonitorBuilder
{
public:
	CMonitorBuilder(void);
	CMonitorBuilder(string xmlPath, vector<CMonitor *> *monitorList);
	~CMonitorBuilder(void);

	int build();

private:
	string m_xmlPath;
	vector<CMonitor *> *m_monitorList;
};
