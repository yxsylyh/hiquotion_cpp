// StatusGraphic.cpp: implementation of the CStatusGraphic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiGraphProj.h"
#include "StatusGraphic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatusGraphic::CStatusGraphic()
: m_destroyStartNode(TRUE)
{
	m_startNode=new CNode();

}

CStatusGraphic::~CStatusGraphic()
{
	if(m_destroyStartNode)
		delete m_startNode;
}

void CStatusGraphic::setStartNode(CNode *val)
{
	if(!val)
		return;
	
	if(m_destroyStartNode)
		delete m_startNode;
	m_startNode = val;
}

int CStatusGraphic::getEndNodeCount()
{
	return (int)m_endNodeList.size();
}

CNode *CStatusGraphic::getEndNode(int index)
{
	if(index<0 || index>=getEndNodeCount())
		return NULL;
	
	return m_endNodeList.at(index);
}
