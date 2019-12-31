// KleenStartPlusRegularExpression.cpp: implementation of the CKleenStartPlusRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KleenStartPlusRegularExpression.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKleenStartPlusRegularExpression::CKleenStartPlusRegularExpression()
: m_regularExpression(NULL)
{

}

CKleenStartPlusRegularExpression::CKleenStartPlusRegularExpression(IRegularExpression *regularExpression)
: m_regularExpression(regularExpression)
{
	
}

CKleenStartPlusRegularExpression::~CKleenStartPlusRegularExpression()
{

}

// 该正则表达式是否接受 ch 字符
BOOL CKleenStartPlusRegularExpression::accept(char *ch)
{
	if(!ch)
		return FALSE;
	
	if(ch[0]=='\0')
		return FALSE;
	
	return m_regularExpression->accept(ch);
}
