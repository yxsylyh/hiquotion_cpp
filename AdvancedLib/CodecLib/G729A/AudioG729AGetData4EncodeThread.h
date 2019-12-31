#pragma once

#include <c++\AdvancedLib\multithreadpattern\productorconsumer\ProductConsumeEventThreadBase.h>

class CAudioG729AGetData4EncodeThread :
	public CProductConsumeEventThreadBase
{
public:
	CAudioG729AGetData4EncodeThread(void);
	~CAudioG729AGetData4EncodeThread(void);

	// 判断数据是否足够
	virtual BOOL isDataEnough();

	// 数据足够时，可以拿出的数据长度
	virtual unsigned int getEnoughDataLength();

};
