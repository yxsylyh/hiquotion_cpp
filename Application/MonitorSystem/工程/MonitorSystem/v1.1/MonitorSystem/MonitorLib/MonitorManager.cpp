#include "StdAfx.h"
#include "MonitorManager.h"

CMonitorManager::CMonitorManager(void)
{
}

CMonitorManager::~CMonitorManager(void)
{
	for(int i=0;i<(int)size();i++)
	{
		CMonitor *monitor=at(i);
		if(monitor)
		{
			delete monitor->MonitedObject;
			delete monitor->Alertor;
			delete monitor;
		}
	}
}

void CMonitorManager::startAll()
{
	for(int i=0;i<(int)size();i++)
	{
		CMonitor *monitor=at(i);
		if(monitor)
			monitor->start();
	}
}

void CMonitorManager::start(int index)
{
	if(index>=0 && index<(int)size())
	{
		CMonitor *monitor=at(index);
		if(monitor)
			monitor->start();
	}
}

void CMonitorManager::stopAll()
{
	for(int i=0;i<(int)size();i++)
	{
		CMonitor *monitor=at(i);
		if(monitor)
			monitor->stop();
	}
}

void CMonitorManager::stop(int index)
{
	if(index>=0 && index<(int)size())
	{
		CMonitor *monitor=at(index);
		if(monitor)
			monitor->stop();
	}
}

void CMonitorManager::setEventLogPath(CString path)
{
	for(int i=0;i<(int)size();i++)
	{
		CString tmp;
		tmp.Format("%s%d.log",path,i);
		CMonitor *monitor=at(i);
		if(monitor)
			monitor->setEventLogFile((LPTSTR)(LPCSTR)tmp);
	}

}
