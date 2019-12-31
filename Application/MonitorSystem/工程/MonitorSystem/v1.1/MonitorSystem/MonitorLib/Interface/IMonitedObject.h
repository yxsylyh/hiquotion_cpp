#pragma once

#include "ITarget.h"
#include <C++\3rdParty\PugiXmlLib\pugixml.hpp>

class IMonitedObject
{
public:
	IMonitedObject(void);
	IMonitedObject(string type,string status);
	~IMonitedObject(void);

	virtual BOOL readConfig(pugi::xml_node configRoot){return TRUE;};
	virtual BOOL isConditionSatisfied(){return TRUE;};
	virtual string toString(){return "";};

public:
	string Type;
	string Status;

protected:
	virtual ITarget *getStatus(){return NULL;};

};
