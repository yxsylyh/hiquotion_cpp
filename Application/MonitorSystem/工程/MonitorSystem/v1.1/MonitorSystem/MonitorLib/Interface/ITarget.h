#pragma once

class ITarget
{
public:
	ITarget(void);
	~ITarget(void);

	// 0：相等，-1：比参数中的状态小，1：比参数中的状态大
	virtual int compare(ITarget *status)=0;
};
