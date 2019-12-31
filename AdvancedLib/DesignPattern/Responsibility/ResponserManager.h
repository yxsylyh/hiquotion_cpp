// ResponserManager.h: interface for the CResponserManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESPONSERMANAGER_H__5FE8FB6B_2488_4FC8_A66C_D818A0FD939B__INCLUDED_)
#define AFX_RESPONSERMANAGER_H__5FE8FB6B_2488_4FC8_A66C_D818A0FD939B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IRequest.h"
#include <c++\FoudationLib\DataStructLib\PointerList.h>
#include "IResponser.h"

class CResponserManager  
{
public:
	CResponserManager();
	virtual ~CResponserManager();

	void addResponer(IResponser *responer);
	BOOL handleRequest(IRequest *request);

protected:
	CPointerList<IResponser *> m_responsers;
};

#endif // !defined(AFX_RESPONSERMANAGER_H__5FE8FB6B_2488_4FC8_A66C_D818A0FD939B__INCLUDED_)
