#pragma once

class IStatus
{
public:
	IStatus(void);
	~IStatus(void);

	// 0：相等，-1：比参数中的状态小，1：比参数中的状态大
	virtual int compare(IStatus *status)=0;
};
