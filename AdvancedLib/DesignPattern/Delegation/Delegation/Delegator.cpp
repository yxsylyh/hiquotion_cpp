// Delegator.cpp: implementation of the CDelegator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Delegation.h"
#include "Delegator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDelegator::CDelegator()
{

}

CDelegator::~CDelegator()
{

}

void CDelegator::regist(IAgent *agent)
{
	if(agent)
		m_agentList.push_back(agent);
}

int CDelegator::delegate(IParameter *para)
{
	for(int i=0;i<m_agentList.size();i++)
		m_agentList[i]->agent(para);

	return 0;
}
