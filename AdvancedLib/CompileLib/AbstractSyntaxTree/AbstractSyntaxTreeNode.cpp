// AbstractSyntaxTreeNode.cpp: implementation of the CAbstractSyntaxTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AbstractSyntaxTreeNode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAbstractSyntaxTreeNode::CAbstractSyntaxTreeNode()
: m_machineToken(NULL)
{

}

CAbstractSyntaxTreeNode::~CAbstractSyntaxTreeNode()
{

}

std::string CAbstractSyntaxTreeNode::getTreeNodeInfo()
{
	std::string info=getTreeNodeInfoByLevel(this, 0);
	return info;
}

std::string CAbstractSyntaxTreeNode::getTreeNodeInfoByLevel( CAbstractSyntaxTreeNode *node, unsigned int level, int space/*=4*/ )
{
	stringstream ss;
	MachineToken *token=node->getMachineToken();
	if(token)
	{
		if(level>0)
		{
			for(int s=0;s<(level-1)*space;s++)
			{
				ss << " ";
			}
			for(int l=0;l<space;l++)
			{
				if(l % space ==0)
					ss << "|";
				else
					ss << "-";
			}
		}
		
		if(token->token=="")
			ss << "-[TokenIsNull]\n";
		else
			ss << "-" << node->getMachineToken()->token.c_str() << "\n";
	}
	else
		ss << "-[NoToken]\n";
	
	if(node->getChildCount()<=0)
		return ss.str();
	
	for(int i=0;i<node->getChildCount();i++)
	{
		CAbstractSyntaxTreeNode *child=node->getChild(i);
		if(!child)
			continue;
		
		ss << getTreeNodeInfoByLevel(child, level+1);
	}
	
	return ss.str();
}
