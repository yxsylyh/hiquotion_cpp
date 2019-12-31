// ICharChecker.h: interface for the ICharChecker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICHARCHECKER_H__1AE533F2_97A9_48E2_B7D7_85DB93A5FED1__INCLUDED_)
#define AFX_ICHARCHECKER_H__1AE533F2_97A9_48E2_B7D7_85DB93A5FED1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ICharChecker  
{
public:
	ICharChecker();
	virtual ~ICharChecker();

	virtual BOOL accept(char c){return FALSE;};
};

#endif // !defined(AFX_ICHARCHECKER_H__1AE533F2_97A9_48E2_B7D7_85DB93A5FED1__INCLUDED_)
