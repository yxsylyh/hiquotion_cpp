// NumberRegularExpression.cpp: implementation of the CNumberRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DigitRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\RE2SGConverter\RE2SGConverter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDigitRegularExpression::CDigitRegularExpression()
: CRangeRegularExpression('0', '9')
{

}

CDigitRegularExpression::~CDigitRegularExpression()
{

}

// CStatusGraphic *CNumberRegularExpression::genStatusGraphic()
// {
// 	return CRE2SGConverter::genFromRangeRE(this);
// }
