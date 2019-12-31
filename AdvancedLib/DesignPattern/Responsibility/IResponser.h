// IResponser.h: interface for the IResponser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IRESPONSER_H__AAE8669E_07A6_447E_B266_93BBC48B5137__INCLUDED_)
#define AFX_IRESPONSER_H__AAE8669E_07A6_447E_B266_93BBC48B5137__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IRequest.h"

class IResponser  
{
public:
	IResponser();
	virtual ~IResponser();

	BOOL handleRequest(IRequest *request);

};

#endif // !defined(AFX_IRESPONSER_H__AAE8669E_07A6_447E_B266_93BBC48B5137__INCLUDED_)
