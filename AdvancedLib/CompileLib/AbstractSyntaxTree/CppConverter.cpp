// CppConverter.cpp: implementation of the CCppConverter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CppConverter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCppConverter::CCppConverter()
{

}

CCppConverter::~CCppConverter()
{

}

int CCppConverter::convertST2AST( CStatuteTreeNode *statuteTreeRoot, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeRoot)
		return -1;
	
	// 由于 statuteTreeRoot 的 token 为空，所以这里直接针对孩子结点做转换
	
	int ret=convertSTNodeList2ASTNodeList(statuteTreeRoot->getChildren(), astCentences);
	if(ret<0)
		return -100+ret;
	
	return 0;
}

int CCppConverter::convertSTNodeList2ASTNodeList( CPointerList<CStatuteTreeNode *> &statuteTreeNodeList, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList )
{
	// 把规约树节点列表 statuteTreeNodeList 中的每个节点，都转换成抽象语法树的节点，并添加为参数中抽象语法树节点 abstractSyntaxTreeNode 的子节点
	for(int i=0;i<(int)statuteTreeNodeList.size();i++)
	{
		CStatuteTreeNode *node=statuteTreeNodeList.at(i);
		if(!node)
			continue;
		
		int ret=convertSTNode2ASTNodeList(node, abstractSyntaxTreeNodeList);
		if(ret<0)
			return -200+ret;
	}
	
	return 0;
}

int CCppConverter::convertSTNode2ASTNodeList( CStatuteTreeNode *statuteTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList )
{
	if(!statuteTreeNode)
		return -1;
	
	MachineToken *token=statuteTreeNode->getMachineToken();
	if(!token)
		return -2;
	
	if(token->token.size()<=0)
		return -3;
	
	int ret=0;
	if(token->token=="Lang")
	{
		if(statuteTreeNode->getChildCount()<=0)
			return -4;
		
		ret=convertSTNodeList2ASTNodeList(statuteTreeNode->getChildren(), abstractSyntaxTreeNodeList);
		if(ret<0)
			return -5;
	}
	else if(token->token=="centences")
	{
		ret=convertCentences2AstNodeList(statuteTreeNode, abstractSyntaxTreeNodeList);
		if(ret<0)
			return -6;
	}
	
	return 0;}

int CCppConverter::convertSTNode2ASTNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	MachineToken *token=statuteTreeNode->getMachineToken();
	if(!token)
		return -2;
	
	if(token->token.size()<=0)
		return -3;

	int ret=0;
	if(token->token=="Lang")
	{
		if(statuteTreeNode->getChildCount()<=0)
			return -4;

		ret=convertSTNodeList2ASTNodeList(statuteTreeNode->getChildren(), astCentences);
		if(ret<0)
			return -5;
	}
	else if(token->token=="centences")
	{
		ret=convertCentences2AstNodeList(statuteTreeNode, abstractSyntaxTreeNode->getChildren());
		if(ret<0)
			return -6;
	}
	else if(token->token=="block")
	{
		ret=convertBlock2AstNodeList(statuteTreeNode, astCentences);
		if(ret<0)
			return -7;
	}
	else if(token->token=="centence")
	{
		ret=convertCentence2AstNode(statuteTreeNode, abstractSyntaxTreeNode, astCentences);
		if(ret<0)
			return -8;
	}

	return 0;
}

// 转换 centences 到抽象语法树节点列表
int CCppConverter::convertCentences2AstNodeList( CStatuteTreeNode *statuteTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList )
{
	if(!statuteTreeNode)
		return -1;

	int childrenCount=statuteTreeNode->getChildCount();
	int ret=0;
	CStatuteTreeNode *child=NULL;
	CAbstractSyntaxTreeNode *astNode=NULL;
	switch (childrenCount)
	{
	case 1:
		// 只有一个节点（block或centence）
		child=statuteTreeNode->getChild(0);
		if(!child)
			return -2;

		astNode=new CAbstractSyntaxTreeNode();
		ret=convertSTNode2ASTNode(child, astNode, abstractSyntaxTreeNodeList);
		if(ret<0)
			return -3;

		abstractSyntaxTreeNodeList.push_back(astNode);
		break;
	case 2:
		// 有两个节点，应该是 centences centence 形式
		// 处理第一个节点
		child=statuteTreeNode->getChild(0);
		if(!child)
			return -4;
		
		ret=convertCentences2AstNodeList(child, abstractSyntaxTreeNodeList);
		if(ret<0)
			return -5;

		// 处理第二个节点
		child=statuteTreeNode->getChild(1);
		if(!child)
			return -6;
		
		CAbstractSyntaxTreeNode *astNode=new CAbstractSyntaxTreeNode();
		ret=convertSTNode2ASTNode(child, astNode, abstractSyntaxTreeNodeList);
		if(ret<0)
			return -5;

		abstractSyntaxTreeNodeList.push_back(astNode);
		break;
	}

	return 0;
}

int CCppConverter::convertBlock2AstNodeList( CStatuteTreeNode *statuteTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &abstractSyntaxTreeNodeList )
{
	if(!statuteTreeNode)
		return -1;

	if(statuteTreeNode->getChildCount()<3)
		return -2;

	CStatuteTreeNode *centences=statuteTreeNode->getChild(1);
	if(!centences)
		return -3;

	MachineToken *token=centences->getMachineToken();
	if(!token)
		return -4;
	
	if(token->token!="centences")
		return -5;
	
	return convertCentences2AstNodeList(centences, abstractSyntaxTreeNodeList);
}

int CCppConverter::convertCentence2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;

	int childCount=statuteTreeNode->getChildCount();
	if(childCount<=0)
		return -2;

	CStatuteTreeNode *child=statuteTreeNode->getChild(0);
	if(!child)
		return -3;

	MachineToken *token=child->getMachineToken();
	if(!token)
		return -4;
	
	if(token->token!="centence")
		return -5;
	
	return convertSTNode2ASTNode(child, abstractSyntaxTreeNode, astCentences);
}

int CCppConverter::convertStatement2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	int childCount=statuteTreeNode->getChildCount();
	if(childCount<=0)
		return -2;

	CStatuteTreeNode *child=statuteTreeNode->getChild(0);
	if(!child)
		return -3;

	MachineToken *token=child->getMachineToken();
	if(!token)
		return -4;

	if(token->token!="statement")
		return -5;
	
	return convertSTNode2ASTNode(child, abstractSyntaxTreeNode, astCentences);
}

int CCppConverter::convertIf2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	int childCount=statuteTreeNode->getChildCount();
	if(childCount!=5 || childCount!=7)
		return -2;

	CStatuteTreeNode *expression=statuteTreeNode->getChild(2);
	if(!expression)
		return -3;

	CStatuteTreeNode *trueBlock=statuteTreeNode->getChild(4);
	if(!trueBlock)
		return -4;

	int ret=0;
	CAbstractSyntaxTreeNode *astExpression=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNode(expression, astExpression, astCentences);
	if(ret<0)
	{
		delete astExpression;
		return -5;
	}

	CAbstractSyntaxTreeNode *astTrueBlock=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNodeList(trueBlock, astTrueBlock->getChildren());
	if(ret<0)
	{
		delete astExpression;
		delete astTrueBlock;
		return -6;
	}

	switch(childCount)
	{
	case 5:
		abstractSyntaxTreeNode->addChild(astExpression);
		abstractSyntaxTreeNode->addChild(astTrueBlock);
		break;
	case 7:
		CStatuteTreeNode *falseBlock=statuteTreeNode->getChild(6);
		if(!falseBlock)
		{
			delete astExpression;
			delete astTrueBlock;
			return -7;
		}

		CAbstractSyntaxTreeNode *astFalseBlock=new CAbstractSyntaxTreeNode();
		ret=convertSTNode2ASTNodeList(falseBlock, astFalseBlock->getChildren());
		break;
	}

	return 0;
}

int CCppConverter::convertWhile2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	int childCount=statuteTreeNode->getChildCount();
	if(childCount!=5)
		return -2;
	
	CStatuteTreeNode *expression=statuteTreeNode->getChild(2);
	if(!expression)
		return -3;
	
	CStatuteTreeNode *trueBlock=statuteTreeNode->getChild(4);
	if(!trueBlock)
		return -4;
	
	int ret=0;
	CAbstractSyntaxTreeNode *astExpression=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNode(expression, astExpression, astCentences);
	if(ret<0)
	{
		delete astExpression;
		return -5;
	}
	
	CAbstractSyntaxTreeNode *astTrueBlock=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNodeList(trueBlock, astTrueBlock->getChildren());
	if(ret<0)
	{
		delete astExpression;
		delete astTrueBlock;
		return -6;
	}
	
	abstractSyntaxTreeNode->addChild(astExpression);
	abstractSyntaxTreeNode->addChild(astTrueBlock);
	
	return 0;
}

int CCppConverter::convertDoWhile2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	int childCount=statuteTreeNode->getChildCount();
	if(childCount!=6)
		return -2;
	
	CStatuteTreeNode *centenceBlock=statuteTreeNode->getChild(1);
	if(!centenceBlock)
		return -3;
	
	CStatuteTreeNode *expression=statuteTreeNode->getChild(4);
	if(!expression)
		return -4;
	
	int ret=0;
	CAbstractSyntaxTreeNode *astCentenceBlock=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNodeList(centenceBlock, astCentenceBlock->getChildren());
	if(ret<0)
	{
		delete astCentenceBlock;
		return -5;
	}
	
	CAbstractSyntaxTreeNode *astExpression=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNode(expression, astExpression, astCentences);
	if(ret<0)
	{
		delete astCentenceBlock;
		delete astExpression;
		return -6;
	}
	
	abstractSyntaxTreeNode->addChild(astCentenceBlock);
	abstractSyntaxTreeNode->addChild(astExpression);
	
	return 0;
}

int CCppConverter::convertCentenceBlock2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	int childCount=statuteTreeNode->getChildCount();
	if(childCount!=1)
		return -2;
	
	CStatuteTreeNode *centenceBlock=statuteTreeNode->getChild(0);
	if(!centenceBlock)
		return -3;
	
	int ret=convertSTNode2ASTNode(centenceBlock, abstractSyntaxTreeNode, astCentences);
	if(ret<0)
		return -4;

	return 0;
}

int CCppConverter::convertDeclare2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	int childCount=statuteTreeNode->getChildCount();
	if(childCount!=2)
		return -2;
	
	CStatuteTreeNode *varType=statuteTreeNode->getChild(0);
	if(!varType)
		return -3;
	
	CStatuteTreeNode *var=statuteTreeNode->getChild(1);
	if(!var)
		return -4;
	
	int ret=0;
	CAbstractSyntaxTreeNode *astVarType=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNode(varType, astVarType, astCentences);
	if(ret<0)
	{
		delete astVarType;
		return -5;
	}
	
	CAbstractSyntaxTreeNode *astVar=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNode(var, astVar, astCentences);
	if(ret<0)
	{
		delete astVarType;
		delete astVar;
		return -6;
	}
	
	abstractSyntaxTreeNode->addChild(astVarType);
	abstractSyntaxTreeNode->addChild(astVar);

	return 0;
}

int CCppConverter::convertSetValue2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	int childCount=statuteTreeNode->getChildCount();
	if(childCount!=3)
		return -2;
	
	CStatuteTreeNode *var=statuteTreeNode->getChild(0);
	if(!var)
		return -3;
	
	CStatuteTreeNode *expression=statuteTreeNode->getChild(2);
	if(!expression)
		return -4;
	
	int ret=0;
	CAbstractSyntaxTreeNode *astVar=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNode(var, astVar, astCentences);
	if(ret<0)
	{
		delete astVar;
		return -5;
	}
	
	CAbstractSyntaxTreeNode *astExpression=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNode(expression, astExpression, astCentences);
	if(ret<0)
	{
		delete astVar;
		delete astExpression;
		return -6;
	}
	
	abstractSyntaxTreeNode->addChild(astVar);
	abstractSyntaxTreeNode->addChild(astExpression);

	return 0;
}

int CCppConverter::convertDeclareAndSetValue2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	int childCount=statuteTreeNode->getChildCount();
	if(childCount!=4)
		return -2;
	
	CStatuteTreeNode *varType=statuteTreeNode->getChild(0);
	if(!varType)
		return -3;
	
	CStatuteTreeNode *var=statuteTreeNode->getChild(1);
	if(!var)
		return -4;

	CStatuteTreeNode *expression=statuteTreeNode->getChild(3);
	if(!expression)
		return -5;
	
	int ret=0;
	CAbstractSyntaxTreeNode *astVarType=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNode(varType, astVarType, astCentences);
	if(ret<0)
	{
		delete astVarType;
		return -6;
	}
	
	CAbstractSyntaxTreeNode *astVar=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNode(var, astVar, astCentences);
	if(ret<0)
	{
		delete astVarType;
		delete astVar;
		return -7;
	}

	CAbstractSyntaxTreeNode *astExpression=new CAbstractSyntaxTreeNode();
	ret=convertSTNode2ASTNode(expression, astExpression, astCentences);
	if(ret<0)
	{
		delete astVarType;
		delete astVar;
		delete astExpression;
		return -8;
	}
	
	abstractSyntaxTreeNode->addChild(astVarType);
	abstractSyntaxTreeNode->addChild(astVar);
	abstractSyntaxTreeNode->addChild(astExpression);

	return 0;
}

int CCppConverter::convertVarType2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	int childCount=statuteTreeNode->getChildCount();
	if(childCount!=1)
		return -2;
	
	CStatuteTreeNode *node=statuteTreeNode->getChild(0);
	if(!node)
		return -3;

	MachineToken *token=node->getMachineToken();
	if(!token)
		return -4;

	std::string stoken=token->token;
	if(stoken.size()<=0)
		return -5;

	abstractSyntaxTreeNode->setNodeType("VarType");
	abstractSyntaxTreeNode->setNodeValue(stoken);
	abstractSyntaxTreeNode->setMachineToken(token);

	return 0;
}

int CCppConverter::convertVarName2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	int childCount=statuteTreeNode->getChildCount();
	if(childCount!=1)
		return -2;
	
	CStatuteTreeNode *node=statuteTreeNode->getChild(0);
	if(!node)
		return -3;
	
	MachineToken *token=node->getMachineToken();
	if(!token)
		return -4;
	
	std::string stoken=token->token;
	if(stoken.size()<=0)
		return -5;
	
	abstractSyntaxTreeNode->setNodeType("VarName");
	abstractSyntaxTreeNode->setNodeValue(stoken);
	abstractSyntaxTreeNode->setMachineToken(token);
	
	return 0;
}

int CCppConverter::convertExpression2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode, CPointerList<CAbstractSyntaxTreeNode *> &astCentences )
{
	if(!statuteTreeNode || !abstractSyntaxTreeNode)
		return -1;
	
	int childCount=statuteTreeNode->getChildCount();
	if(childCount!=1 && childCount!=3)
		return -2;
	
	if(childCount==1)
	{
		CStatuteTreeNode *node=statuteTreeNode->getChild(0);
		if(!node)
			return -3;
		
		MachineToken *token=statuteTreeNode->getMachineToken();
		if(!token)
			return -4;
		
		std::string stoken=token->token;
		if(stoken.size()<=0)
			return -5;
		
		abstractSyntaxTreeNode->setNodeType(stoken);
		
		token=node->getMachineToken();
		if(!token)
			return -6;
		
		stoken=token->token;
		if(stoken.size()<=0)
			return -7;
		
		abstractSyntaxTreeNode->setNodeValue(stoken);
	}
	else if(childCount==3)
	{
		CStatuteTreeNode *expr1=statuteTreeNode->getChild(0);
		if(!expr1)
			return -8;
		
		CStatuteTreeNode *opr=statuteTreeNode->getChild(1);
		if(!opr)
			return -9;

		CStatuteTreeNode *expr2=statuteTreeNode->getChild(2);
		if(!expr2)
			return -10;

		MachineToken *token=opr->getMachineToken();
		if(!token)
			return -11;
		
		std::string stoken=token->token;
		if(stoken.size()<=0)
			return -12;

		CAbstractSyntaxTreeNode *astOpr=new CAbstractSyntaxTreeNode();
		if(!astOpr)
			return -13;
		
		astOpr->setNodeType("expression");
		astOpr->setNodeValue(stoken);
		
		CAbstractSyntaxTreeNode *astExpr1=new CAbstractSyntaxTreeNode();
		if(!astExpr1)
			return -14;

		int ret=convertExpression2AstNode(expr1, astExpr1, astCentences);
		if(ret<0)
		{
			delete astExpr1;
			return -15;
		}
			
		CAbstractSyntaxTreeNode *astExpr2=new CAbstractSyntaxTreeNode();
		if(!astExpr2)
		{
			delete astExpr1;
			return -16;
		}
		
		ret=convertExpression2AstNode(expr2, astExpr2, astCentences);
		if(ret<0)
		{
			delete astExpr1;
			delete astExpr2;
			return -17;
		}
		
		abstractSyntaxTreeNode->addChild(astOpr);
		astOpr->addChild(astExpr1);
		astOpr->addChild(astExpr2);
	}
	
	return 0;
}

// int CCppConverter::convertCentence2AstNode( CStatuteTreeNode *statuteTreeNode, CAbstractSyntaxTreeNode *abstractSyntaxTreeNode )
// {
// 	if(!statuteTreeNode || !abstractSyntaxTreeNode)
// 		return -1;
// 
// 	MachineToken *token=statuteTreeNode->getMachineToken();
// 	if(!token)
// 		return -2;
// 	
// 	if(token->token.size()<=0)
// 		return -3;
// 
// 	int childCount=statuteTreeNode->getChildCount();
// 	CStatuteTreeNode *child=statuteTreeNode->getChild(0);
// 	if(!child)
// 		return -4;
// 
// 	int ret=0;
// 	switch (childCount)
// 	{
// 	case 1:
// 		if(token->token=="")
// 			
// 		break;
// 	case 2:
// 		ret=convertSTNode2ASTNode(child, abstractSyntaxTreeNode);
// 		if(ret<0)
// 			return -10;
// 		break;
// 	}
// 
// 	return 0;
// }
