// CharChecker.cpp: implementation of the CCharChecker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CharChecker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCharChecker::CCharChecker()
: m_char(NULL)
{

}

CCharChecker::CCharChecker(char c)
: m_char(c)
{
	
}

CCharChecker::~CCharChecker()
{

}

BOOL CCharChecker::accept(char c)
{
	if(m_char==c)
		return TRUE;

	return FALSE;
}
