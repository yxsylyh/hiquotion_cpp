// MergenceAnalyzer.h: interface for the CMergenceAnalyzer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MERGENCEANALYZER_H__4BDDD584_9C5A_4C68_B62C_F97FE5F02BBE__INCLUDED_)
#define AFX_MERGENCEANALYZER_H__4BDDD584_9C5A_4C68_B62C_F97FE5F02BBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <c++\FoundationLib\DataStructLib\PointerList.h>
#include "StatuteTreeNode.h"
#include <C++\FoundationLib\DataStructLib\PointerStack.h>
#include "..\StatuteStatusGraph\StatuteStatusGraphNode.h"
#include "StatuteList.h"
#include "..\StatuteStatusMachine\StatuteStatusMachine.h"

using namespace std;

// 规约定义分析器
// 根据（从规约定义文件中读取出来的）规约定义字符串，生成语法分析器所需的规约状态图
// 并且能够根据源码的token列表和规约状态图，生成规约树，返回规约树的根节点
class CStatuteAnalyzer  
{
public:
	CStatuteAnalyzer();
	virtual ~CStatuteAnalyzer();

	// 生成规约状态图
	// 参数：1-规约式文本（即语言规则定义），2-规约标识符（默认是 =>），3-换行符（默认是 \r\n)
// 	int genStatuteStatusGraph(string text, CStatuteList &statuteList, string statuteSymbol="=>", string lineSplitter="\r\n");

// 	// 分析源码文本
// 	int analyzeFromSrcText(std::string text, ILexer *lexer, CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList);
// 	// 分析源码文件
// 	int analyzeFromSrcFile(std::string filePath, ILexer *lexer, CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList);

	// 生成规约树
	// 参数：
	// tokenList：源码的token列表
	// root：返回的规约树根节点
	// 返回值：0-成功，其他-失败
	int analyze(CPointerList<MachineToken *> &tokenList, CStatuteTreeNode *root, CPointerList<MachineToken *> &errorTokenList);
	
	CStatuteStatusGraph * getStatuteStatusGraph() const { return m_machine.getStatuteStatusGraph(); }
	void setStatuteStatusGraph(CStatuteStatusGraph * val) { m_machine.setStatuteStatusGraph(val); }
	
	string getErrMsg() const { return m_errMsg; }

protected:
	int statute(CStatuteStatusGraph *graph, /*CStatuteList &origStatuteList,*/ CPointerStack<CStatuteStatusGraphNode *> &statuteStatusGraphNodeStack, CPointerStack<CStatuteTreeNode *> &statuteTreeNodeStack);

private:
	CStatuteStatusMachine m_machine;
	string m_errMsg;
};

#endif // !defined(AFX_MERGENCEANALYZER_H__4BDDD584_9C5A_4C68_B62C_F97FE5F02BBE__INCLUDED_)
