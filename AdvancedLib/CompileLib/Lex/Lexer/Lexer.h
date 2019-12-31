// Lexer.h: interface for the CLexer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEXER_H__90CF4CB1_5165_4EF3_996B_E45B1D5EDEAB__INCLUDED_)
#define AFX_LEXER_H__90CF4CB1_5165_4EF3_996B_E45B1D5EDEAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "C++\ADVANCEDLIB\COMPILELIB\LEX\LEXER\ILexer.h"
#include "..\LexStatusMachine\LexStatusMachine.h"

class CLexer : public ILexer  
{
public:
	CLexer();
	virtual ~CLexer();

	// 返回值：
	// -1：参数为空
	// -2：状态机内部错误（当前结点为空）
	int analyze(string text, CPointerList<MachineToken *> &tokenList, CValueList<string> &errList);
	void setLexStatusGraph(CLexStatusGraph *graph);

private:
	CLexStatusMachine m_machine;

};

#endif // !defined(AFX_LEXER_H__90CF4CB1_5165_4EF3_996B_E45B1D5EDEAB__INCLUDED_)
