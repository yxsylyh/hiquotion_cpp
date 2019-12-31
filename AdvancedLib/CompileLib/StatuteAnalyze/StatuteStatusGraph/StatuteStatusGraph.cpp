// MergeStatusGraph.cpp: implementation of the CMergeStatusGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteStatusGraph.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteStatusGraph::CStatuteStatusGraph()
: m_currentNode(NULL)
{

}

CStatuteStatusGraph::~CStatuteStatusGraph()
{

}

// 打印状态图信息
void CStatuteStatusGraph::printGraphInfo()
{
	// show total info
	printf("Node count is %d\n", (int)m_nodeList.size());
	printf("Arc count is %d\n", (int)m_arcList.size());
	printf("\n\n");
	
	// show node info
	for(int i=0;i<m_nodeList.size();i++)
	{
		CStatuteStatusGraphNode *node=m_nodeList.at(i);
		if(!node)
		{
			printf("Node %d is null pointer!\n");
			continue;
		}
		
		int j=0;
		
		printf("Node %d:\n", i);
		printf("StatuteItem info: %s\n", node->printStatuteItemListInfo().c_str());
		printf("Can be accepted? %d\n", node->isAccepted());
		printf("Is final? %d\n", node->isFinal());
		printf("----------------\n", i);
		printf("Arc-in count is %d\n", node->getInArcCount());
		if(node->getInArcCount()>0)
		{
			for(j=0;j<node->getInArcCount();j++)
			{
				CStatuteStatusGraphArc *arc=node->getInArc(j);
				if(!arc)
				{
					printf("%dth Arc-in is null pointer!\n", j+1);
					continue;
				}
				
				int indx=getArcIndex(arc);
				std::string data="";
				MachineToken *token=arc->getArcData();
				if(!token)
				{
					printf("arc data is NULL!\n");
					continue;
				}

				data=token->token;
				if(data.length()<=0)
					data=" ";
				printf("%dth Arc-in %d: %s\n", j+1, indx, data.c_str());
			}
		}
		printf("----------------\n", i);
		printf("Arc-out count is %d\n", node->getOutArcCount());
		if(node->getOutArcCount()>0)
		{
			for(j=0;j<node->getOutArcCount();j++)
			{
				CStatuteStatusGraphArc *arc=node->getOutArc(j);
				if(!arc)
				{
					printf("%dth Arc-out is null pointer!\n", j+1);
					continue;
				}

				int indx=getArcIndex(arc);
				std::string data="";
				MachineToken *token=arc->getArcData();
				if(!token)
				{
					printf("arc data is NULL!\n");
					continue;
				}

				data=token->token;
				if(data.length()<=0)
					data=" ";
				printf("%dth Arc-out %d: %s\n", j+1, indx, data.c_str());
			}
		}
		
		printf("\n");
	}
}

// 判断是否包含唯一标记的节点
BOOL CStatuteStatusGraph::containNodeby(string statuteKey)
{
	for(int i=0;i<m_nodeList.size();i++)
	{
		CStatuteStatusGraphNode *node=m_nodeList.at(i);
		if(!node)
			continue;

		CStatuteItemList *lst=node->getStatuteItemList();
		if(!lst)
			continue;

		if(lst->genStatuteKey()==statuteKey)
			return TRUE;
	}

	return FALSE;
}

// 取指定唯一标记的节点
CStatuteStatusGraphNode * CStatuteStatusGraph::getNodeby(string statuteKey)
{
	for(int i=0;i<m_nodeList.size();i++)
	{
		CStatuteStatusGraphNode *node=m_nodeList.at(i);
		if(!node)
			continue;
		
		CStatuteItemList *lst=node->getStatuteItemList();
		if(!lst)
			continue;
		
		if(lst->genStatuteKey()==statuteKey)
			return node;
	}
	
	return NULL;
}

// 将第一个非初始节点设置为接受节点
BOOL CStatuteStatusGraph::setAcceptNode()
{
	for(int i=0;i<getNodeCount();i++)
	{
		CStatuteStatusGraphNode *node=getNode(i);
		if(!node)
			continue;

		if(!node->isOrigNode())
		{
			node->setAccepted(TRUE);
			return TRUE;
		}
	}

	return FALSE;
}

// 初始化当前节点
BOOL CStatuteStatusGraph::initCurrentNode()
{
	if(m_nodeList.size()<=0)
		return FALSE;
	
	m_currentNode=m_nodeList.at(0);

	return TRUE;
}

// 从当前节点走指定名称的出弧
// 返回值：
// 1，成功
// 0，当前节点不存在名称为 arcName 的出弧
// -1，弧名称为空
// -2，当前节点为空
// -3，当前节点的名称为 arcName 的出弧不唯一
// -4，指定名称 arcName 的出弧存在，但是为空
// -5，指定名称 arcName 的出弧的to节点为空
int CStatuteStatusGraph::walkThroughArc(MachineToken *arcData)
{
	if(!arcData)
		return -1;
	
	if(!m_currentNode)
		if(!initCurrentNode())
			return -2;

	CPointerList<CStatuteStatusGraphArc *> arcList;
	m_currentNode->getOutArcsBy(arcData, arcList);
	if(arcList.size()<=0)
		return 0;

	if(arcList.size()>1)
		return -3;

	CStatuteStatusGraphArc *arc=arcList.at(0);
	if(!arc)
		return -4;

	CStatuteStatusGraphNode *nodeTo=arc->getNodeTo();
	if(!nodeTo)
		return -5;

	m_currentNode=nodeTo;

	return 1;
}

// 当前节点是否是可接受的
BOOL CStatuteStatusGraph::isCurrentNodeAccepted()
{
	if(!m_currentNode)
		return FALSE;

	return m_currentNode->isAccepted();
}

// 当前节点是否是终节点
BOOL CStatuteStatusGraph::isCurrentNodeFinal()
{
	if(!m_currentNode)
		return FALSE;
	
	return m_currentNode->isFinal();	
}

// 获取唯一规约式在规约条目列表中的索引
// int CStatuteStatusGraph::getIndexInStatuteItemList()
// {
// 	if(!m_currentNode)
// 		return -11;
// 
// 	if(!m_currentNode->isFinal())
// 		return -12;
// 
// 	return m_currentNode->getIndexInStatuteItemList();
// }

// 获取终节点唯一规约式
Statute * CStatuteStatusGraph::getStatuteOfFinal()
{
	if(!m_currentNode)
		return NULL;
	
	if(!m_currentNode->isFinal())
		return NULL;
	
	return m_currentNode->getStatuteOfFinal();
}

// 获取唯一规约式中token的个数
int CStatuteStatusGraph::getTokenCount()
{
	if(!m_currentNode)
		return -11;
	
	if(!m_currentNode->isFinal())
		return -12;
	
	return m_currentNode->getTokenCount();	
}

// 获取终节点唯一规约式中规约的名称
std::string CStatuteStatusGraph::getStatuteName()
{
	if(!m_currentNode)
		return "";

	CStatuteItemList *lst=m_currentNode->getStatuteItemList();
	if(!lst)
		return "";

	StatuteItem *item=lst->at(0);
	if(!item)
		return "";

	Statute *statute=item->statute;
	if(!statute)
		return "";

	return statute->statuteName;
}
