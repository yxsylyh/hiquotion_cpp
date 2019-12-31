// SymbolRegularExpression.h: interface for the CSymbolRegularExpression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYMBOLREGULAREXPRESSION_H__24952C95_F89C_44BC_A84D_7A5990417375__INCLUDED_)
#define AFX_SYMBOLREGULAREXPRESSION_H__24952C95_F89C_44BC_A84D_7A5990417375__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IRegularExpression.h"
// #include "..\..\..\DataStructLib\Graph\DiGraphProj\StatusGraphic.h"

class CSymbolRegularExpression : public IRegularExpression  
{
public:
	CSymbolRegularExpression();
	CSymbolRegularExpression(char c);
	virtual ~CSymbolRegularExpression();

	char getChar() const { return m_char; }
	void setChar(char val) { m_char = val; }

// 	virtual CStatusGraphic *genStatusGraphic();
	
	// 该正则表达式是否接受 ch 字符
	virtual BOOL accept(char *ch);
	
private:
	char m_char;
};

#endif // !defined(AFX_SYMBOLREGULAREXPRESSION_H__24952C95_F89C_44BC_A84D_7A5990417375__INCLUDED_)
