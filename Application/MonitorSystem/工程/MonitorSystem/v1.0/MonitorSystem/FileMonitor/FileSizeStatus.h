#pragma once
#include "../MonitorLib/Interface/IStatus.h"

class CFileSizeStatus :
	public IStatus
{
public:
	CFileSizeStatus(void);
	CFileSizeStatus(int fileSize);
	~CFileSizeStatus(void);

	// 0：相等，-1：比参数中的状态小，1：比参数中的状态大
	int compare(IStatus *status);

public:
	ULONGLONG FileSize;

};
