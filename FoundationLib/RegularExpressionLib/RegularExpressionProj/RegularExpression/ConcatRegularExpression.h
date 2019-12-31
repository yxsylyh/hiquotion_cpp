// ConcatRegularExpression.h: interface for the CConcatRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONCATREGULAREXPRESSION_H__1413F153_FA78_45A7_BC77_DCCE2686B459__INCLUDED_)
#define AFX_CONCATREGULAREXPRESSION_H__1413F153_FA78_45A7_BC77_DCCE2686B459__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\StatusGraphic.h"

class CConcatRegularExpression : public IRegularExpression  
{
public:
	CConcatRegularExpression();
	CConcatRegularExpression(IRegularExpression *regularExpression1, IRegularExpression *regularExpression2);
	virtual ~CConcatRegularExpression();

	IRegularExpression * getRegularExpression1() const { return m_regularExpression1; }
	void setRegularExpression1(IRegularExpression * val) { m_regularExpression1 = val; }
	
	IRegularExpression * getRegularExpression2() const { return m_regularExpression2; }
	void setRegularExpression2(IRegularExpression * val) { m_regularExpression2 = val; }

	void setRegularExpression(IRegularExpression *regularExpression1, IRegularExpression *regularExpression2);

// 	virtual CStatusGraphic *genStatusGraphic();

// 	// 需要外部释放指针
// 	virtual ICharChecker *getChecker();

	// 该正则表达式是否接受 ch 字符
	virtual BOOL accept(char *ch);

private:
	IRegularExpression *m_regularExpression1;
	IRegularExpression *m_regularExpression2;
};

#endif // !defined(AFX_CONCATREGULAREXPRESSION_H__1413F153_FA78_45A7_BC77_DCCE2686B459__INCLUDED_)
