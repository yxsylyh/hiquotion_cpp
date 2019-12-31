#pragma once
#include "../MonitorLib/Interface/ITarget.h"

class CFileSizeTarget :
	public ITarget
{
public:
	CFileSizeTarget(void);
	CFileSizeTarget(int fileSize);
	~CFileSizeTarget(void);

	// 0：相等，-1：比参数中的状态小，1：比参数中的状态大
	int compare(ITarget *target);

public:
	ULONGLONG FileSize;

};
