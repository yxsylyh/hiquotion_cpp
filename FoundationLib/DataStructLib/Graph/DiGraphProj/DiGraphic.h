// DiGraphic.h: interface for the CDiGraphic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIGRAPHIC_H__1478DA1A_75C2_4925_B1BB_685BAF7D9EAC__INCLUDED_)
#define AFX_DIGRAPHIC_H__1478DA1A_75C2_4925_B1BB_685BAF7D9EAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Node.h"
#include "Arc.h"

class CNode;
class CArc;

class CDiGraphic  
{
public:
	CDiGraphic();
	virtual ~CDiGraphic();

	CNode *addNode(CNode *node);
	
	BOOL addNodes(CPointerList<CNode *> *nodes);
	
	CArc *addArc(CArc *arc);
	
	BOOL addArcs(CPointerList<CArc *> *arcs);
	
	// 关联 arc 弧、开始结点和结束结点
	// 1、给 arc 添加开始结点和终止结点
	// 2、并把 arc 添加到开始结点的出弧列表，以及添加到结束结点的入弧列表
	void add(CArc *arc, CNode *nodeStart, CNode *nodeEnd);

	BOOL getNodesDestroy() const { return m_isNodesDestroy; }
	void setNodesDestroy(BOOL val) { m_isNodesDestroy = val; }
	
	BOOL getArcsDestroy() const { return m_isArcsDestroy; }
	void setArcsDestroy(BOOL val) { m_isArcsDestroy = val; }
	
protected:
	CPointerList<CNode *> m_nodes;
	CPointerList<CArc *> m_arcs;
	
	// 类退出时，是否delete节点列表元素，默认为是
	BOOL m_isNodesDestroy;  
	// 类退出时，是否delete边列表元素，默认为是
	BOOL m_isArcsDestroy;
};

#endif // !defined(AFX_DIGRAPHIC_H__1478DA1A_75C2_4925_B1BB_685BAF7D9EAC__INCLUDED_)
