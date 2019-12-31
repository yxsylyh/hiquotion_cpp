// OrRegularExpression.cpp: implementation of the COrRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OrRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\RE2SGConverter\RE2SGConverter.h"
// #include "..\CharChecker\OrChecker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COrRegularExpression::COrRegularExpression()
: m_regularExpression1(NULL), m_regularExpression2(NULL)
{

}

COrRegularExpression::COrRegularExpression(IRegularExpression *regularExpression1, IRegularExpression *regularExpression2)
: m_regularExpression1(regularExpression1), m_regularExpression2(regularExpression2)
{
	
}

COrRegularExpression::~COrRegularExpression()
{

}

void COrRegularExpression::setRegularExpression(IRegularExpression *regularExpression1, IRegularExpression *regularExpression2)
{
	m_regularExpression1=regularExpression1;
	m_regularExpression2=regularExpression2;
}

// CStatusGraphic *COrRegularExpression::genStatusGraphic()
// {
// 	return CRE2SGConverter::genFromOrRE(this);
// }

// 需要外部释放指针
// ICharChecker *COrRegularExpression::getChecker()
// {
// 	return new COrChecker(m_regularExpression1->getChecker(), m_regularExpression2->getChecker());
// }

// 该正则表达式是否接受 ch 字符
BOOL COrRegularExpression::accept(char *ch)
{
	if(!m_regularExpression1 || !m_regularExpression2)
		return FALSE;

	if(m_regularExpression1->accept(ch) || m_regularExpression2->accept(ch))
		return TRUE;

	return FALSE;
}

