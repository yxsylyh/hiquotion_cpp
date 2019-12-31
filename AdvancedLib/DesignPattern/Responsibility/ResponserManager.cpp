// ResponserManager.cpp: implementation of the CResponserManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Responsibility.h"
#include "ResponserManager.h"
#include "ResponserException.h"
#include <wtypes.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResponserManager::CResponserManager()
{

}

CResponserManager::~CResponserManager()
{

}

void CResponserManager::addResponer(IResponser *responer)
{
	m_responsers.push_back(responer);
}


BOOL CResponserManager::handleRequest(IRequest *request)
{
	BOOL isHandled=FALSE;

	for(int i=0;i<(int)m_responsers.size();i++)
	{
		IResponser *responser=m_responsers.at(i);
		if(!responser)
			continue;

		try
		{
			isHandled=responser->handleRequest(request);
		}
		catch (CResponserException* e)
		{
			CString err;
			err.Format("到第 %d 个责任人时，该责任人在处理请求时抛出如下异常：%s", i+1, e->getErrMessage());
			throw e;
		}

		if(isHandled)
			return TRUE;
	}

	return isHandled;
}
