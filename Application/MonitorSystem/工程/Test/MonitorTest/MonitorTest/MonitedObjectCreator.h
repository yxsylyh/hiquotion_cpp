#pragma once

#include "imonitedobject.h"

class CMonitedObjectCreator
{
public:
	CMonitedObjectCreator(void);
	~CMonitedObjectCreator(void);

	static IMonitedObject *create(string type, string status);
};
