// OrRegularExpression.h: interface for the COrRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORREGULAREXPRESSION_H__AAFA5F18_A9CC_4A67_9A6A_30FD1D0D7EE2__INCLUDED_)
#define AFX_ORREGULAREXPRESSION_H__AAFA5F18_A9CC_4A67_9A6A_30FD1D0D7EE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IRegularExpression.h"

class COrRegularExpression : public IRegularExpression  
{
public:
	COrRegularExpression();
	COrRegularExpression(IRegularExpression *regularExpression1, IRegularExpression *regularExpression2);
	virtual ~COrRegularExpression();

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

#endif // !defined(AFX_ORREGULAREXPRESSION_H__AAFA5F18_A9CC_4A67_9A6A_30FD1D0D7EE2__INCLUDED_)
