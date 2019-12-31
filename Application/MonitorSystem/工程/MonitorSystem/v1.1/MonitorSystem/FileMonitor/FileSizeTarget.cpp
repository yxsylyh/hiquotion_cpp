#include "StdAfx.h"
#include "FileSizeTarget.h"

CFileSizeTarget::CFileSizeTarget(void)
{
}

CFileSizeTarget::~CFileSizeTarget(void)
{
}

// 0：相等，-1：比参数中的状态小，1：比参数中的状态大
int CFileSizeTarget::compare(ITarget *target)
{
	CFileSizeTarget *ftarget=(CFileSizeTarget *)target;
	if(FileSize > ftarget->FileSize)
		return 1;
	else if(FileSize < ftarget->FileSize)
		return -1;
	else
		return 0;
}
