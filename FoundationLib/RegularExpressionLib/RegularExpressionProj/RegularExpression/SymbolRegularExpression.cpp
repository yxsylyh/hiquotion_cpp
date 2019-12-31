// SymbolRegularExpression.cpp: implementation of the CSymbolRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SymbolRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\RE2SGConverter\RE2SGConverter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSymbolRegularExpression::CSymbolRegularExpression()
: m_char(NULL)
{

}

CSymbolRegularExpression::CSymbolRegularExpression(char c)
: m_char(c)
{
	
}

CSymbolRegularExpression::~CSymbolRegularExpression()
{

}

// CStatusGraphic *CSymbolRegularExpression::genStatusGraphic()
// {
// 	return CRE2SGConverter::genFromSymbolRE(this);
// }

// 该正则表达式是否接受 ch 字符
BOOL CSymbolRegularExpression::accept(char *ch)
{
	if(!ch)
		return FALSE;

	if(m_char==ch[0])
		return TRUE;

	return FALSE;
}

