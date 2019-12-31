// SymbolCharChecker.cpp: implementation of the CSymbolCharChecker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SymbolCharChecker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSymbolCharChecker::CSymbolCharChecker()
: CCharChecker()
{

}

CSymbolCharChecker::CSymbolCharChecker(char c)
: CCharChecker(c)
{
	
}

CSymbolCharChecker::~CSymbolCharChecker()
{

}
