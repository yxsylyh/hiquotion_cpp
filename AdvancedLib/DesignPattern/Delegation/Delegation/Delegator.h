// Delegator.h: interface for the CDelegator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DELEGATOR_H__D140E14D_0AC2_48DF_800C_B831EDF068BB__INCLUDED_)
#define AFX_DELEGATOR_H__D140E14D_0AC2_48DF_800C_B831EDF068BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDelegator.h"
#include "IAgent.h"
#include <vector>

using namespace std;

class CDelegator : public IDelegator
{
public:
	CDelegator();
	virtual ~CDelegator();

	void regist(IAgent *agent);
	int delegate(IParameter *para);

private:
	vector<IAgent *> m_agentList;
};

#endif // !defined(AFX_DELEGATOR_H__D140E14D_0AC2_48DF_800C_B831EDF068BB__INCLUDED_)
