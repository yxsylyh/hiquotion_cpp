// Node.cpp: implementation of the CNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiGraphProj.h"
#include "Node.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNode::CNode()
: m_nodeData(NULL)
{

}

CNode::CNode(INodeData *nodeData)
: m_nodeData(nodeData)
{

}

CNode::~CNode()
{

}

void CNode::clearArcOutList()
{
	m_arcOutList.clear();
}

void CNode::clearArcInList()
{
	m_arcInList.clear();
}

void CNode::clearArcList()
{
	m_arcOutList.clear();
	m_arcInList.clear();
}

BOOL CNode::addArcOut(CArc *arcOut)
{
	if(!arcOut)
		return FALSE;
	
	m_arcOutList.push_back(arcOut);
	return TRUE;
}

BOOL CNode::addArcIn(CArc *arcIn)
{
	if(!arcIn)
		return FALSE;
	
	m_arcInList.push_back(arcIn);
	return TRUE;
}

int CNode::getArcOutCount()
{
	return m_arcOutList.size();
}

int CNode::getArcInCount()
{
	return m_arcInList.size();
}

CArc *CNode::getArcOut(int index)
{
	if(index<0 || index>=m_arcOutList.size())
		return NULL;
	
	return m_arcOutList.at(index);
}

CArc *CNode::getArcIn(int index)
{
	if(index<0 || index>=m_arcInList.size())
		return NULL;
	
	return m_arcInList.at(index);
}
