#include "StdAfx.h"
#include "Monitor.h"

CMonitor::CMonitor(void)
{
	MonitedObject=NULL;
	Alertor=NULL;
	Interval=0;
	Times=0;

	m_timerId=0;
	m_currTimes=0;
}

CMonitor::	CMonitor(IMonitedObject *monitedObject, IAlertor *alertor, int interval, int times)
{
	MonitedObject=monitedObject;
	Alertor=alertor;
	if(interval>0)
		Interval=interval;
	else
		Interval=60; // 默认60秒监控一次
	if(times>0)
		Times=times;
	else
		Times=1;     // 默认满足一次即报警

	m_timerId=0;
}

CMonitor::~CMonitor(void)
{
	if(m_timerId>0)
	{
		KillTimer(NULL, m_timerId);
		m_timerId=0;
	}
}

// BOOL CMonitor::readConfig()
// {
// 	CString file=CFolderOperation::addGang(CFolderOperation::GetModulePath())+"config.xml";
// 	pugi::xml_document doc;
// 	pugi::xml_parse_result result=doc.load_file((LPTSTR)(LPCSTR)file);
// 	if (result.status!=pugi::status_ok)
// 	{
// 		return FALSE;
// 	}
// 
// 	pugi::xml_node node = doc.child("MonitorSystem").child("Monitor");
// 	std::string interval = node.attribute("interval").value();
// 
// }

BOOL CMonitor::start()
{
	if(!MonitedObject || !Alertor || Interval==0)
		return FALSE;

	m_timerId=SetTimer(NULL, (UINT_PTR)this, Interval*1000, (TIMERPROC)&OnTimer);
	return TRUE;
}

void CMonitor::stop()
{
	KillTimer(NULL, m_timerId);
	m_timerId=0;
}

void CMonitor::monite()
{
	if(!MonitedObject || !Alertor || Interval==0)
		return;

	if(MonitedObject->isConditionSatisfied())
	{
		m_currTimes++;
		
		if(m_currTimes==Times)
		{
			Alertor->alert();
			m_currTimes=0;
		}
	}
}

void CALLBACK OnTimer(HWND hWnd,UINT nMsg,UINT_PTR nTimerid,DWORD dwTime)
{
	CMonitor *monitor=(CMonitor *)nTimerid;
	if(!monitor)
		return;

	monitor->monite();
}
