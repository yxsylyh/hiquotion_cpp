// StatuteStatusMachine.cpp: implementation of the CStatuteStatusMachine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteStatusMachine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteStatusMachine::CStatuteStatusMachine()
: m_statuteStatusGraph(NULL)
{

}

CStatuteStatusMachine::CStatuteStatusMachine( CStatuteStatusGraph *statuteStatusGraph )
: m_statuteStatusGraph(statuteStatusGraph)
{

}

CStatuteStatusMachine::~CStatuteStatusMachine()
{

}

BOOL CStatuteStatusMachine::initCurrentNode()
{
	if(!m_statuteStatusGraph)
		return FALSE;

	return m_statuteStatusGraph->initCurrentNode();
}

void CStatuteStatusMachine::setCurrentNode(CStatuteStatusGraphNode *node)
{
	if(!m_statuteStatusGraph)
		return;

	m_statuteStatusGraph->setCurrentNode(node);
}

CStatuteStatusGraphNode *CStatuteStatusMachine::getCurrentNode()
{
	if(!m_statuteStatusGraph)
		return NULL;

	return m_statuteStatusGraph->getCurrentNode();
}

// 从当前节点走指定名称的出弧
// 返回值：
// 1，成功
// 0，当前节点不存在名称为 arcName 的出弧
// -1，弧数据指针为空
// -2，规约状态树指针为空
// -3，当前节点为空，并且重新初始化失败
// -4，当前节点为空，并且重新初始化后仍然为空
// -5，当前节点的名称为 arcName 的出弧不唯一
// -6，指定名称 arcName 的出弧存在，但是为空
// -7，指定名称 arcName 的出弧的to节点为空
//int CStatuteStatusMachine::goThrough(string arcName)
int CStatuteStatusMachine::goThrough(MachineToken *arcData)
{
	if(!arcData)
		return -1;

	if(!m_statuteStatusGraph)
		return -2;
	
	CStatuteStatusGraphNode *currentNode=m_statuteStatusGraph->getCurrentNode();
	if(!currentNode)
	{
		if(!m_statuteStatusGraph->initCurrentNode())
			return -3;

		currentNode=m_statuteStatusGraph->getCurrentNode();
		if(!currentNode)
			return -4;
	}
		
	CPointerList<CStatuteStatusGraphArc *> arcList;
	currentNode->getOutArcsBy(arcData, arcList);
	if(arcList.size()<=0)
		return 0;
	
	if(arcList.size()>1)
		return -5;
	
	CStatuteStatusGraphArc *arc=arcList.at(0);
	if(!arc)
		return -6;
	
	CStatuteStatusGraphNode *nodeTo=arc->getNodeTo();
	if(!nodeTo)
		return -7;
	
	m_statuteStatusGraph->setCurrentNode(nodeTo);
		
	return 1;
}

BOOL CStatuteStatusMachine::isCurrentNodeAccepted()
{
	if(!m_statuteStatusGraph)
		return FALSE;

	return m_statuteStatusGraph->isCurrentNodeAccepted();
}

BOOL CStatuteStatusMachine::isCurrentNodeFinal()
{
	if(!m_statuteStatusGraph)
		return FALSE;
	
	return m_statuteStatusGraph->isCurrentNodeFinal();	
}

int CStatuteStatusMachine::getNodeCount()
{
	if(!m_statuteStatusGraph)
		return -1;

	return m_statuteStatusGraph->getNodeCount();
}