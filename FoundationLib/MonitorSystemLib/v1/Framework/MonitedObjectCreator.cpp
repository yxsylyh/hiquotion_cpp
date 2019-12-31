#include "StdAfx.h"
#include "MonitedObjectCreator.h"
#include "../FileMonitor/MonitedFileSize.h"

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
			return new CMonitedFileSize(type, status);  // 不调用默认构造函数，是这样可以记录下来监控对象是哪个类型的，以及监控对象的哪个状态，以便于界面上看到相关信息
	}

	return NULL;
}
