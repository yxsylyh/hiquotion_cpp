// KernelLexer.h: interface for the CKernelLexer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KERNELLEXER_H__AD7D3BF3_5236_4E9F_8908_360838C08991__INCLUDED_)
#define AFX_KERNELLEXER_H__AD7D3BF3_5236_4E9F_8908_360838C08991__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Lex\Lexer\ILexer.h"
#include <string>
#include "KernelLexStatusGraphBuilder.h"
#include "..\..\Lex\Lexer\Lexer.h"
#include "..\..\Lex\LexStatusMachine\LexStatusMachine.h"

using namespace std;

class CKernelLexer : public ILexer
{
public:
	CKernelLexer();
	virtual ~CKernelLexer();

	// 返回值：
	// -1：参数为空
	// -2：状态机内部错误（当前结点为空）
	int analyze (string text, CPointerList<MachineToken *> &tokenList, CValueList<string> &errList);

private:
	// 对token列表做预处理
	// 1. 把双引号中的内容，变成一个token
	// 2. 对于 \" 的处理，如果在一对引号内，则按引号字符处理，如果是在一对引号外，则按引号token处理
	// 3. 去掉回车、空格、行注释、块注释等等的token吧
	// 4. 提取变量，即在两个%之间的是变量（在提取双引号之间的字符串之后做）
	// 参数：
	// tokenList：规约式的token列表
	int preProcessTokens (CPointerList<MachineToken *> &tokenList);

	// 根据起始和终止索引，来提取该范围的tokens为字符串token
	int preProcessExtractStringToken (CPointerList<MachineToken *> &tokenList, int startIndex, int endIndex);

private:
	CKernelLexStatusGraphBuilder m_builder;
	CLexer m_lexer;
	CLexStatusMachine m_machine;

	string m_errMsg;
};

#endif // !defined(AFX_KERNELLEXER_H__AD7D3BF3_5236_4E9F_8908_360838C08991__INCLUDED_)
