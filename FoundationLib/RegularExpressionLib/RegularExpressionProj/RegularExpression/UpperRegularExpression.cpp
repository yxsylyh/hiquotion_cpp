// UpperRegularExpression.cpp: implementation of the CUpperRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UpperRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\RE2SGConverter\RE2SGConverter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUpperRegularExpression::CUpperRegularExpression()
: CRangeRegularExpression('A', 'Z')
{

}

CUpperRegularExpression::~CUpperRegularExpression()
{

}

// CStatusGraphic *CUpperRegularExpression::genStatusGraphic()
// {
// 	return CRE2SGConverter::genFromRangeRE(this);
// }
// 
