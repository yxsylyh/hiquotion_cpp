#include "StdAfx.h"
#include "MonitedObjectCreator.h"
#include "MonitedFileSize.h"

CMonitedObjectCreator::CMonitedObjectCreator(void)
{
}

CMonitedObjectCreator::~CMonitedObjectCreator(void)
{
}

IMonitedObject *CMonitedObjectCreator::create(string type, string status)
{
	CString stype=type.c_str();
	stype=stype.MakeUpper();
	CString sstatus=status.c_str();
	sstatus=sstatus.MakeUpper();
	if(stype=="FILE")
	{
		if(sstatus=="SIZE")
			return new CMonitedFileSize();
	}

	return NULL;
}
