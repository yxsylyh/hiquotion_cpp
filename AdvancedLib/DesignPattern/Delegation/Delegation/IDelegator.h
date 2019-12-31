// IDelegator.h: interface for the IDelegator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDELEGATOR_H__4C70B9E6_D947_4A78_B485_E70E44873411__INCLUDED_)
#define AFX_IDELEGATOR_H__4C70B9E6_D947_4A78_B485_E70E44873411__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IParameter.h"
#include "IAgent.h"

class IDelegator  
{
public:
	IDelegator(){};
	virtual ~IDelegator(){};

	void regist(IAgent *agent);
	virtual int delegate(IParameter *para){return 0;};
};

#endif // !defined(AFX_IDELEGATOR_H__4C70B9E6_D947_4A78_B485_E70E44873411__INCLUDED_)
