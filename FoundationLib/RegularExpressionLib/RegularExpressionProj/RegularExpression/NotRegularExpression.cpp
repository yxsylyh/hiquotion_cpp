// NotRegularExpression.cpp: implementation of the CNotRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NotRegularExpression.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNotRegularExpression::CNotRegularExpression()
: m_re(NULL)
{

}

CNotRegularExpression::CNotRegularExpression(IRegularExpression *re)
: m_re(re)
{
	
}

CNotRegularExpression::~CNotRegularExpression()
{

}

BOOL CNotRegularExpression::accept( char *ch )
{
	if(!m_re)
		return FALSE;

	return !m_re->accept(ch);
}
