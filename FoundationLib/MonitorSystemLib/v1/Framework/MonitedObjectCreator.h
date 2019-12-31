#pragma once

#include "Interface/IMonitedObject.h"

class CMonitedObjectCreator
{
public:
	CMonitedObjectCreator(void);
	~CMonitedObjectCreator(void);

	static IMonitedObject *create(string type, string status);
};
