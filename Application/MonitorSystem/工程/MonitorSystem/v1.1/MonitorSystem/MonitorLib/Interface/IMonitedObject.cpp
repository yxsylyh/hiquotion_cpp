#include "StdAfx.h"
#include "IMonitedObject.h"

IMonitedObject::IMonitedObject(void)
{
}

IMonitedObject::IMonitedObject(string type, string status)
{
	Type = type;
	Status = status;
}

IMonitedObject::~IMonitedObject(void)
{
}
