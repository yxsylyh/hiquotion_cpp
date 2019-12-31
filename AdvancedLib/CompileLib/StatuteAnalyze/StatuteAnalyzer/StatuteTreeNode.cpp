// StatuteTreeNode.cpp: implementation of the CStatuteTreeNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteTreeNode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteTreeNode::CStatuteTreeNode()
: m_machineToken(NULL)
{
	
}

CStatuteTreeNode::CStatuteTreeNode(MachineToken *machineToken)
: m_machineToken(machineToken)
{
	
}

CStatuteTreeNode::CStatuteTreeNode(CPointerStack<CStatuteTreeNode *> *reversedMachineTokenStack)
{
	if(!reversedMachineTokenStack)
		return;

	while(!reversedMachineTokenStack->empty())
		addChild(reversedMachineTokenStack->popout());
}

CStatuteTreeNode::CStatuteTreeNode(CPointerStack<CStatuteTreeNode *> *machineTokenStack, int popoutCount)
{
	if(!machineTokenStack)
		return;

	if(popoutCount>machineTokenStack->size())
		return;

	CPointerList<CStatuteTreeNode *>::iterator it=m_children.begin();
	for(int i=0;i<popoutCount;i++)
	{
		if(!machineTokenStack->empty())
		{
			it=m_children.begin();
			m_children.insert(it, machineTokenStack->popout());
		}
	}
}

CStatuteTreeNode::~CStatuteTreeNode()
{

}

void CStatuteTreeNode::genTokenPosition()
{
	if(!m_machineToken)
		return;

	if(m_children.size()<=0)
		return;

	CStatuteTreeNode *startNode=m_children.at(0);
	if(!startNode)
		return;

	MachineToken *startToken=startNode->getMachineToken();
	if(!startToken)
		return;

	CStatuteTreeNode *endNode=m_children.at(m_children.size()-1);
	if(!endNode)
		return;

	MachineToken *endToken=endNode->getMachineToken();
	if(!endNode)
		return;

	m_machineToken->startPosition=startToken->startPosition;
	m_machineToken->endPosition=endToken->endPosition;
}

// 获取树节点信息（包括子节点），用于测试
std::string CStatuteTreeNode::getTreeNodeInfo()
{
	std::string info=getTreeNodeInfoByLevel(this, 0);
	return info;
}

// 获取指定级别的树节点信息，level表示当前节点是在树的第几层，用于测试
std::string CStatuteTreeNode::getTreeNodeInfoByLevel(CStatuteTreeNode *node, unsigned int level, int space)
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
		CStatuteTreeNode *child=node->getChild(i);
		if(!child)
			continue;
		
		ss << getTreeNodeInfoByLevel(child, level+1);
	}

	return ss.str();
}

void CStatuteTreeNode::printTreeNodeInfo()
{
	printf("\nStatute tree node struct is shown below:\n\n");
	printTreeNodeInfoByLevel(this, 0);
	printf("\n");
}

void CStatuteTreeNode::printTreeNodeInfoByLevel( CStatuteTreeNode *node, unsigned int level )
{
	std::string info=getTreeNodeInfoByLevel(node, level, 4);
	printf("%s", info.c_str());
}