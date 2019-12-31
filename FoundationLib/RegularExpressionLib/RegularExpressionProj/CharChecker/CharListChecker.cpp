// CharListChecker.cpp: implementation of the CCharListChecker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CharListChecker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCharListChecker::CCharListChecker()
: m_isOrChecker(TRUE)
{

}

CCharListChecker::CCharListChecker(BOOL isOrCheck)
: m_isOrChecker(isOrCheck)
{
	
}

CCharListChecker::~CCharListChecker()
{

}


BOOL CCharListChecker::accept(char c)
{
	if(m_isOrChecker)
		return orCheck(c);
	else
		return andCheck(c);
}

BOOL CCharListChecker::orCheck(char c)
{
	for(int i=0;i<size();i++)
	{
		ICharChecker *checker=at(i);
		if(!checker)
			continue;
		
		if(checker->accept(c))
			return TRUE;
	}
	
	return FALSE;
}

BOOL CCharListChecker::andCheck(char c)
{
	for(int i=0;i<size();i++)
	{
		ICharChecker *checker=at(i);
		if(!checker)
			continue;
		
		if(!checker->accept(c))
			return FALSE;
	}
	
	return TRUE;
}
