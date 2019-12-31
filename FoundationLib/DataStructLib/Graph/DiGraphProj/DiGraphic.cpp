// DiGraphic.cpp: implementation of the CDiGraphic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiGraphProj.h"
#include "DiGraphic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiGraphic::CDiGraphic()
: m_isNodesDestroy(TRUE), m_isArcsDestroy(TRUE)
{

}

CDiGraphic::~CDiGraphic()
{
	if(m_isNodesDestroy)
		m_nodes.destroyAll();
	if(m_isArcsDestroy)
		m_arcs.destroyAll();
}

CNode *CDiGraphic::addNode(CNode *node)
{
	m_nodes.push_back(node);
	return node;
}

BOOL CDiGraphic::addNodes(CPointerList<CNode *> *nodes)
{
	for(int i=0;i<nodes->size();i++)
		m_nodes.push_back(nodes->at(i));
	return TRUE;
}

CArc *CDiGraphic::addArc(CArc *arc)
{
	m_arcs.push_back(arc);
	return arc;
}

BOOL CDiGraphic::addArcs(CPointerList<CArc *> *arcs)
{
	if(!arcs)
		return FALSE;
	
	for(int i=0;i<arcs->size();i++)
		m_arcs.push_back(arcs->at(i));
	return TRUE;
}

// 关联 arc 弧、开始结点和结束结点
// 1、给 arc 添加开始结点和终止结点
// 2、并把 arc 添加到开始结点的出弧列表，以及添加到结束结点的入弧列表
void CDiGraphic::add(CArc *arc, CNode *nodeStart, CNode *nodeEnd)
{
	if(!arc)
		return;
	
	if(!nodeStart)
		return;
	
	if(!nodeEnd)
		return;
	
	arc->setNodeStart(nodeStart);
	arc->setNodeEnd(nodeEnd);
	
	nodeStart->addArcOut(arc);
	nodeEnd->addArcIn(arc);
}
