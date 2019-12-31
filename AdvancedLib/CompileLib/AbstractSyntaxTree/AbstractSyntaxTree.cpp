// AbstractSyntaxTree.cpp: implementation of the CAbstractSyntaxTree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AbstractSyntaxTree.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAbstractSyntaxTree::CAbstractSyntaxTree()
{

}

CAbstractSyntaxTree::~CAbstractSyntaxTree()
{

}

int CAbstractSyntaxTree::convertST2AST( CStatuteTreeNode *statuteTreeRoot, CAbstractSyntaxTreeNode *abstractSyntaxTreeRoot )
{
	if(!statuteTreeRoot || !abstractSyntaxTreeRoot)
		return -1;
	
	// 由于 statuteTreeRoot 的 token 为空，所以这里直接针对孩子结点做转换
	
	int ret=convertSTNodeList2ASTNode(statuteTreeRoot->getChildren(), abstractSyntaxTreeRoot);
	if(ret<0)
		return -100+ret;

	return 0;
}

int CAbstractSyntaxTree::convertSTNodeList2ASTNode( CPointerList<CStatuteTreeNode *> &statuteTreeNodeList, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode )
{
	if(!abstractSyntaxTreeNode)
		return -1;
	
	for(int i=0;i<(int)statuteTreeNodeList.size();i++)
	{
		CStatuteTreeNode *node=statuteTreeNodeList.at(i);
		if(!node)
			continue;
		
		int ret=convertSTNode2ASTNodeList(node, abstractSyntaxTreeNode->getChildren());
		if(ret<0)
			return -200+ret;
	}
	
	return 0;
}

int CAbstractSyntaxTree::convertSTNode2ASTNodeList( CStatuteTreeNode *statuteTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList )
{
	
	return 0;
}

int CAbstractSyntaxTree::convertSTNode2ASTNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	MachineToken *token=statuteTreeNode->getMachineToken();
	if(!token)
		return -2;
	
	if(token->token.size()<=0)
		return -3;
	
	int ret=convertSTNode2ASTNode(token->token, statuteTreeNode, abstractSyntaxTreeNode);
	if(ret<0)
		return -99;
	
	return 0;
}

int CAbstractSyntaxTree::convertSTNode2ASTNode( std::string statuteTreeNodeName, CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode )
{
	if(statuteTreeNodeName.size()<=0 || !statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	if(statuteTreeNodeName=="CppLike")
	{
		return convertSTNodeList2ASTNode(statuteTreeNode->getChildren(), abstractSyntaxTreeNode);
	}
	
	return 0;
}
