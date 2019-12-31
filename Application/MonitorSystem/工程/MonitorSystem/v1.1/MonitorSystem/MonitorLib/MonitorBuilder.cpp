#include "StdAfx.h"
#include "MonitorBuilder.h"
#include <C++\FoudationLib\FileSysLib\FileOperation.h>
#include <sstream>
#include "monitedobjectcreator.h"
#include "commandalertor.h"

CMonitorBuilder::CMonitorBuilder(void)
{
	m_xmlPath="";
}

CMonitorBuilder::CMonitorBuilder(string xmlPath, vector<CMonitor *> *monitorList)
{
	m_xmlPath=xmlPath;
	m_monitorList=monitorList;
}

CMonitorBuilder::~CMonitorBuilder(void)
{
}

// 返回值：
// 0：成功
// -1：xml文件路径字符串为空
// -2：xml文件不存在
// -3：xml文件加载失败
int CMonitorBuilder::build()
{
	if(m_xmlPath=="")
		return -1;

	if(!CFileOperation::isFileExist(m_xmlPath.c_str()))
		return -2;

	pugi::xml_document doc;
	pugi::xml_parse_result result=doc.load_file(m_xmlPath.c_str());
	if (result.status!=pugi::status_ok)
	{
		return -3;
	}

// 	pugi::xml_node node = doc.child("MonitorSystem").child("Monitor");
	pugi::xpath_node_set tools = doc.select_nodes("//MonitorSystem/Monitor");
	for (pugi::xpath_node_set::const_iterator it = tools.begin(); it !=  tools.end(); ++it)
	{
		pugi::xpath_node node = *it;
		std::string sinterval = node.node().attribute("interval").value();
		int interval=0;
		stringstream ss;
		ss<< sinterval;
		ss>> interval;

		if(interval<=0)
			interval=60;

		std::string stimes = node.node().attribute("times").value();
		int times=0;
		ss.clear();
		ss<< stimes;
		ss>> times;

		if(times<=0)
			times=1;

		pugi::xml_node nodeObj = node.node().child("MonitedObject");
		string stype = nodeObj.attribute("type").value();
		string status = nodeObj.attribute("status").value();

		if(stype=="" || status=="")
		{
			continue;
		}

		IMonitedObject *obj=CMonitedObjectCreator::create(stype, status);
		if(obj==NULL)
		{
			continue;
		}

		if(!obj->readConfig(nodeObj))
		{
			continue;
		}

		pugi::xml_node nodeAlertor = node.node().child("Alertor");

		CCommandAlertor *alertor=new CCommandAlertor();
		if(!alertor->readConfig(nodeAlertor))
		{
			continue;
		}

		CMonitor *monitor=new CMonitor(obj, alertor, interval, times);
		m_monitorList->push_back(monitor);
	}

	return 0;
}
