// ConcatRegularExpression.cpp: implementation of the CConcatRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConcatRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\RE2SGConverter\RE2SGConverter.h"
// #include "..\CharChecker\AndChecker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConcatRegularExpression::CConcatRegularExpression()
: m_regularExpression1(NULL), m_regularExpression2(NULL)
{

}

CConcatRegularExpression::CConcatRegularExpression(IRegularExpression *regularExpression1, IRegularExpression *regularExpression2)
: m_regularExpression1(regularExpression1), m_regularExpression2(regularExpression2)
{

}

CConcatRegularExpression::~CConcatRegularExpression()
{

}

void CConcatRegularExpression::setRegularExpression(IRegularExpression *regularExpression1, IRegularExpression *regularExpression2)
{
	m_regularExpression1=regularExpression1;
	m_regularExpression2=regularExpression2;
}

// CStatusGraphic *CConcatRegularExpression::genStatusGraphic()
// {
// 	return CRE2SGConverter::genFromConcatRE(this);
// }

// 需要外部释放指针
// ICharChecker *CConcatRegularExpression::getChecker()
// {
// 	return new CAndChecker(m_regularExpression1->getChecker(), m_regularExpression2->getChecker());
// }

// ch 字符是否符合该正则表达式
BOOL CConcatRegularExpression::accept(char *ch)
{
	if(!m_regularExpression1 || !m_regularExpression2)
		return FALSE;

	if(m_regularExpression1->accept(ch) && m_regularExpression2->accept(ch))
		return TRUE;

	return FALSE;
};
