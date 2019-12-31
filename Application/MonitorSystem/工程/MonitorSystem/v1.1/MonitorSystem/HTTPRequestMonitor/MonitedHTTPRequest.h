#pragma once
#include "..\MonitorLib\Interface\IMonitedObject.h"
#include <string>
#include <C++\FoudationLib\HTTPRequest\HttpRequest.h>

class CMonitedHttpRequest
	: public IMonitedObject
{
public:
	CMonitedHttpRequest(void);
	CMonitedHttpRequest(std::string type, string status);
	~CMonitedHttpRequest();

	BOOL readConfig(pugi::xml_node configRoot);
	BOOL isConditionSatisfied();
	string toString(){ return ""; };

private:
	std::string m_url;
	std::string m_response;

	CHttpRequest m_httpRequest;
};
