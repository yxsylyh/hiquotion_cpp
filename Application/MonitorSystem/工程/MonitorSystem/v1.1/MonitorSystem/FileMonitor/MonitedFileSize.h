#pragma once
#include "../MonitorLib/Interface/IMonitedObject.h"

#include <C++\3rdParty\PugiXmlLib\pugixml.hpp>
#include "filesizeTarget.h"

class CMonitedFileSize :
	public IMonitedObject
{
public:
	CMonitedFileSize(void);
	CMonitedFileSize(string type, string status);
	~CMonitedFileSize(void);

	BOOL readConfig(pugi::xml_node configRoot);
	BOOL isConditionSatisfied();

	string toString();

protected:
	void getStatus(ITarget *status);
	string translatePath(string path);

private:
	string m_path;
	string m_translatedPath;
	string m_condition;

	int condition;

	CFileSizeTarget m_lastStatus;

};
