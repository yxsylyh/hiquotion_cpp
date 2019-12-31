// RangeRegularExpression.h: interface for the CRangeRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RANGEREGULAREXPRESSION_H__85B8652A_F95C_4CC8_9804_D0934AEFE4A7__INCLUDED_)
#define AFX_RANGEREGULAREXPRESSION_H__85B8652A_F95C_4CC8_9804_D0934AEFE4A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\StatusGraphic.h"

class CRangeRegularExpression : public IRegularExpression  
{
public:
	CRangeRegularExpression();
	CRangeRegularExpression(char from, char to);
	virtual ~CRangeRegularExpression();

	void setRange(char from, char to);
	void getRange(char from, char to);

// 	virtual CStatusGraphic *genStatusGraphic();
	
// 	// 需要外部释放指针
// 	virtual ICharChecker *getChecker();
	
	// 该正则表达式是否接受 ch 字符
	virtual BOOL accept(char *ch);
	
private:
	char m_charFrom;
	char m_charTo;
};

#endif // !defined(AFX_RANGEREGULAREXPRESSION_H__85B8652A_F95C_4CC8_9804_D0934AEFE4A7__INCLUDED_)
