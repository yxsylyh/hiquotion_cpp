// KleenStarRegularExpression.cpp: implementation of the CKleenStarRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KleenStarRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\RE2SGConverter\RE2SGConverter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKleenStarRegularExpression::CKleenStarRegularExpression()
: m_regularExpression(NULL)
{

}

CKleenStarRegularExpression::CKleenStarRegularExpression(IRegularExpression *regularExpression)
: m_regularExpression(regularExpression)
{
	
}

CKleenStarRegularExpression::~CKleenStarRegularExpression()
{

}

// CStatusGraphic *CKleenStarRegularExpression::genStatusGraphic()
// {
// 	return CRE2SGConverter::genFromKleenStarRE(this);
// }

// 需要外部释放指针
// ICharChecker *CKleenStarRegularExpression::getChecker()
// {
// 	return m_regularExpression->getChecker();
// }

// 该正则表达式是否接受 ch 字符
BOOL CKleenStarRegularExpression::accept(char *ch)
{
	if(!ch)
		return TRUE;

	if(ch[0]=='\0')
		return TRUE;

	return m_regularExpression->accept(ch);
}
