// CppConverter.h: interface for the CCppConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CPPCONVERTER_H__8DE020C4_A0E3_4EA1_B95E_C151F45E64BB__INCLUDED_)
#define AFX_CPPCONVERTER_H__8DE020C4_A0E3_4EA1_B95E_C151F45E64BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IST2ASTConverter.h"

class CCppConverter : public IST2ASTConverter  
{
public:
	CCppConverter();
	virtual ~CCppConverter();

	// 规约树到抽象语法树的转换
	int convertST2AST(CStatuteTreeNode *statuteTreeRoot, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

protected:
	// 转换规约树的所有孩子节点到抽象语法树节点
	int convertSTNodeList2ASTNodeList(CPointerList<CStatuteTreeNode *> &statuteTreeNodeList, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList);
	// 转换规约树节点到抽象语法树节点列表
	// 即从树型变成列表型，比如把根据语法规则生成的递归句子的规约树变成抽象语法树的句子列表
	int convertSTNode2ASTNodeList(CStatuteTreeNode *statuteTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList);
	// 转换规约树节点到抽象语法树节点
	int convertSTNode2ASTNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

	// 转换 centences 到抽象语法树节点列表
	int convertCentences2AstNodeList(CStatuteTreeNode *statuteTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList);
	int convertBlock2AstNodeList(CStatuteTreeNode *statuteTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList);
	int convertCentence2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

	int convertStatement2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertIf2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertWhile2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertDoWhile2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertCentenceBlock2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

	int convertDeclare2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertSetValue2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertDeclareAndSetValue2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

	int convertVarType2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);
	int convertVarName2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

	int convertExpression2AstNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences);

};

#endif // !defined(AFX_CPPCONVERTER_H__8DE020C4_A0E3_4EA1_B95E_C151F45E64BB__INCLUDED_)
