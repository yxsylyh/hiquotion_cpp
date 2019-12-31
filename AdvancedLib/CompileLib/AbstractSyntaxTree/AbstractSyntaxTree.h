// AbstractSyntaxTree.h: interface for the CAbstractSyntaxTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABSTRACTSYNTAXTREE_H__130AEDD6_4310_49D3_9AC5_6CB3EB79729B__INCLUDED_)
#define AFX_ABSTRACTSYNTAXTREE_H__130AEDD6_4310_49D3_9AC5_6CB3EB79729B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\AdvancedLib\CompileLib\StatuteAnalyze\StatuteAnalyzer\StatuteTreeNode.h>
#include "AbstractSyntaxTreeNode.h"
#include <C++\FoundationLib\DataStructLib\PointerList.h>

// 抽象语法树类
// 负责将规约树转换成抽象语法树
class CAbstractSyntaxTree  
{
public:
	CAbstractSyntaxTree();
	virtual ~CAbstractSyntaxTree();

	// 规约树到抽象语法树的转换
	static int convertST2AST(CStatuteTreeNode *statuteTreeRoot, CAbstractSyntaxTreeNode *abstractSyntaxTreeRoot);

protected:
	// 转换规约树的所有孩子节点到抽象语法树节点
	static int convertSTNodeList2ASTNode(CPointerList<CStatuteTreeNode *> &statuteTreeNodeList, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode);
	// 转换规约树节点到抽象语法树节点列表
	// 即从树型变成列表型，比如把根据语法规则生成的递归句子的规约树变成抽象语法树的句子列表
	static int convertSTNode2ASTNodeList(CStatuteTreeNode *statuteTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList);
	// 转换规约树节点到抽象语法树节点
	static int convertSTNode2ASTNode(CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode);
	// 根据指定的名称，具体转换规约树节点到抽象语法树节点
	static int convertSTNode2ASTNode(std::string statuteTreeNodeName, CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode);
};

#endif // !defined(AFX_ABSTRACTSYNTAXTREE_H__130AEDD6_4310_49D3_9AC5_6CB3EB79729B__INCLUDED_)
