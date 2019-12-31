// EmptyRegularExpression.h: interface for the CEmptyRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMPTYREGULAREXPRESSION_H__90011DA7_59E4_4858_9DAE_AFC3C8283C06__INCLUDED_)
#define AFX_EMPTYREGULAREXPRESSION_H__90011DA7_59E4_4858_9DAE_AFC3C8283C06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\StatusGraphic.h"

class CEmptyRegularExpression : public IRegularExpression  
{
public:
	CEmptyRegularExpression();
	virtual ~CEmptyRegularExpression();

// 	virtual CStatusGraphic *genStatusGraphic();
	
	// ch 字符是否符合该正则表达式
	// 这里规定，空正则表达式接受所有字符
	virtual BOOL accept(char *ch){ return TRUE;};
};

#endif // !defined(AFX_EMPTYREGULAREXPRESSION_H__90011DA7_59E4_4858_9DAE_AFC3C8283C06__INCLUDED_)
