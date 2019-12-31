// RangeCharChecker.cpp: implementation of the CRangeCharChecker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RangeCharChecker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRangeCharChecker::CRangeCharChecker()
: m_charFrom(NULL), m_charTo(NULL)
{

}

CRangeCharChecker::CRangeCharChecker(char from, char to)
: m_charFrom(from), m_charTo(to)
{

}

CRangeCharChecker::~CRangeCharChecker()
{

}

BOOL CRangeCharChecker::accept(char c)
{
	if(m_charFrom<=c && c<=m_charTo)
		return TRUE;

	return FALSE;
}
