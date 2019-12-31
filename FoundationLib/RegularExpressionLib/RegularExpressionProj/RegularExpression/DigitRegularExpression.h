// NumberRegularExpression.h: interface for the CNumberRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NUMBERREGULAREXPRESSION_H__9D495928_6B03_4242_82EB_8507251E38E3__INCLUDED_)
#define AFX_NUMBERREGULAREXPRESSION_H__9D495928_6B03_4242_82EB_8507251E38E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RangeRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\StatusGraphic.h"

class CDigitRegularExpression : public CRangeRegularExpression  
{
public:
	CDigitRegularExpression();
	virtual ~CDigitRegularExpression();

// 	virtual CStatusGraphic *genStatusGraphic();
	
};

#endif // !defined(AFX_NUMBERREGULAREXPRESSION_H__9D495928_6B03_4242_82EB_8507251E38E3__INCLUDED_)
