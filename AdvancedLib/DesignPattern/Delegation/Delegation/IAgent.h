// IAgent.h: interface for the IAgent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IAGENT_H__079E6009_2C4A_4C2F_83BF_01ECEFBA97B4__INCLUDED_)
#define AFX_IAGENT_H__079E6009_2C4A_4C2F_83BF_01ECEFBA97B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IParameter.h"

class IAgent  
{
public:
	IAgent(){};
	virtual ~IAgent(){};

	virtual int agent(IParameter *para){return 0;};
};

#endif // !defined(AFX_IAGENT_H__079E6009_2C4A_4C2F_83BF_01ECEFBA97B4__INCLUDED_)
