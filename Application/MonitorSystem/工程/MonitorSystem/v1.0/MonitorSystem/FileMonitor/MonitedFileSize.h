#pragma once
#include "../MonitorLib/Interface/IMonitedObject.h"

#include <pugixmllib/pugixml.hpp>
#include "filesizestatus.h"

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
	void getStatus(IStatus *status);
	string translatePath(string path);

private:
	string m_path;
	string m_translatedPath;
	string m_condition;

	int condition;

	CFileSizeStatus m_lastStatus;

};
