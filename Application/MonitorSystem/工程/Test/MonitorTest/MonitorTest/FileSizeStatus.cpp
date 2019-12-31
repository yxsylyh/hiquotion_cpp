#include "StdAfx.h"
#include "FileSizeStatus.h"

CFileSizeStatus::CFileSizeStatus(void)
{
}

CFileSizeStatus::~CFileSizeStatus(void)
{
}

// 0：相等，-1：比参数中的状态小，1：比参数中的状态大
int CFileSizeStatus::compare(IStatus *status)
{
	CFileSizeStatus *fstatus=(CFileSizeStatus *)status;
	if(FileSize > fstatus->FileSize)
		return 1;
	else if(FileSize < fstatus->FileSize)
		return -1;
	else
		return 0;
}
