// AndChecker.cpp: implementation of the CAndChecker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AndChecker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAndChecker::CAndChecker()
: m_checker1(NULL), m_checker2(NULL)
{

}

CAndChecker::CAndChecker(ICharChecker *checker1, ICharChecker *checker2)
: m_checker1(checker1), m_checker2(checker2)
{
	
}

CAndChecker::~CAndChecker()
{
	if(m_checker1)
		delete m_checker1;
	if(m_checker2)
		delete m_checker2;
}

BOOL CAndChecker::accept(char c)
{
	BOOL r1=FALSE, r2=FALSE;
	
	if(!m_checker1)
		r1=TRUE;
	else
		r1=m_checker1->accept(c);
	
	if(!m_checker2)
		r2=TRUE;
	else
		r2=m_checker2->accept(c);
	
	if(r1 && r2)
		return TRUE;
	
	return FALSE;
}
