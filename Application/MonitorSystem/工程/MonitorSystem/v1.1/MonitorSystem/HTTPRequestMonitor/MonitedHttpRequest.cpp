#include "stdafx.h"
#include "MonitedHttpRequest.h"

CMonitedHttpRequest::CMonitedHttpRequest(void)
{
}

CMonitedHttpRequest::CMonitedHttpRequest(std::string type, string status)
	:IMonitedObject(type, status)
{
}

CMonitedHttpRequest::~CMonitedHttpRequest()
{}

BOOL CMonitedHttpRequest::readConfig(pugi::xml_node configRoot)
{
	try
	{
		m_url = configRoot.child_value("Url");
		m_response = configRoot.child_value("Response");
	}
	catch (CException* e)
	{
		return FALSE;
	}
	return TRUE;

}

BOOL CMonitedHttpRequest::isConditionSatisfied()
{
	int ret=m_httpRequest.connect("MonitorSystem", m_url, "GET");
	if (ret != 0)
	{
		return FALSE;
	}

	ResponseHead head;
	ret = m_httpRequest.sendData(NULL, 0, head);
	if (ret != 0)
	{
		return FALSE;
	}

	if (head.statusCode != "200")
	{
		return FALSE;
	}

	string response;
	ret = m_httpRequest.readString(response);
	if (ret != 0)
	{
		return FALSE;
	}

	if (response != m_response)
		return FALSE;

	return TRUE;
}

