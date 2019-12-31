#pragma once

#include "threadstatus.h"

// 定义多线程标志
// 凡是继承该接口的类，在使用时，该标志会自动生效
#define SUPPORT_MULTI_THREAD

class IThread
{
public:
	IThread(void){};
	virtual ~IThread(void){};

	virtual HANDLE getThreadHandle(){return NULL;};
	virtual BOOL start(){ return FALSE; };
	virtual int pause(){ return 0; };
	virtual void stop(){};
	virtual void terminate(){};
	virtual UINT run(){return 0;};
	virtual ThreadStatus getStatus(){return Terminated;};
	virtual void join(){};
};
