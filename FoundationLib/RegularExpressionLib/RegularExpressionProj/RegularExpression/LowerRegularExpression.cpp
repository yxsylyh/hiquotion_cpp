// LowerRegularExpression.cpp: implementation of the CLowerRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LowerRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\RE2SGConverter\RE2SGConverter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLowerRegularExpression::CLowerRegularExpression()
: CRangeRegularExpression('a', 'z')
{

}

CLowerRegularExpression::~CLowerRegularExpression()
{

}

// CStatusGraphic *CLowerRegularExpression::genStatusGraphic()
// {
// 	return CRE2SGConverter::genFromRangeRE(this);
// }

