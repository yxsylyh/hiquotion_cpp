#pragma once

#include "istatus.h"
#include <PugiXmlLib\pugixml.hpp>

class IMonitedObject
{
public:
	IMonitedObject(void);
	~IMonitedObject(void);

	virtual BOOL readConfig(pugi::xml_node configRoot){return TRUE;};
	virtual BOOL isConditionSatisfied(){return TRUE;};

protected:
	virtual IStatus *getStatus(){return NULL;};

};
