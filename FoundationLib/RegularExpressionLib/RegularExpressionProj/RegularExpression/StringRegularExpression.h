// StringRegularExpression.h: interface for the CStringRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGREGULAREXPRESSION_H__A24EEE14_8090_4C4D_B922_E345FAA84BF2__INCLUDED_)
#define AFX_STRINGREGULAREXPRESSION_H__A24EEE14_8090_4C4D_B922_E345FAA84BF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IRegularExpression.h"
#include <string>

class CStringRegularExpression : public IRegularExpression  
{
public:
	CStringRegularExpression();
	CStringRegularExpression(std::string expr);
	virtual ~CStringRegularExpression();

	// 该正则表达式是否接受 ch 字符
	virtual BOOL accept(char *ch);

private:
	std::string m_expr;

};

#endif // !defined(AFX_STRINGREGULAREXPRESSION_H__A24EEE14_8090_4C4D_B922_E345FAA84BF2__INCLUDED_)
