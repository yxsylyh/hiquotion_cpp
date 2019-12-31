#pragma once
#include <c++\AdvancedLib\multithreadpattern\productorconsumer\ProductConsumeEventThreadBase.h>

class CAudioData4PlayThread :
	public CProductConsumeEventThreadBase
{
public:
	CAudioData4PlayThread(void);
	~CAudioData4PlayThread(void);

	// 判断数据是否足够
	virtual BOOL isDataEnough();

	// 数据足够时，可以拿出的数据长度
	virtual unsigned int getEnoughDataLength();

};
