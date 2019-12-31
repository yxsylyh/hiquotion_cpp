
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\DataStructLib\PointerList.h>
#include "Node.h"
#include "Arc.h"

// 图，Node是节点，Arc是弧
// template <class Node, class NodeKey, class Arc, class ArcKey>
template <class NodeData, class ArcWeight>
class CDiGraphic
{
public:
	CDiGraphic()
	{
		m_isNodesDestroy=TRUE;
		m_isArcsDestroy=TRUE;
	};

	virtual ~CDiGraphic()
	{
		if(m_isNodesDestroy)
			m_nodes.destroyAll();
		if(m_isArcsDestroy)
			m_arcs.destroyAll();
	}

	CPointerList<CNode<NodeData, ArcWeight> *> *getNodes() { return &m_nodes; }
// 	void setNodes(CPointerMap<NodeKey, Node> val) { m_nodes = val; }

	CPointerList<CArc<NodeData, ArcWeight> *> *getArcs() { return &m_arcs; }
// 	void setArcs(CPointerMap<ArcKey, Arc> val) { m_arcs = val; }

	CNode<NodeData, ArcWeight> *addNode(CNode<NodeData, ArcWeight> *node)
	{
		m_nodes.push_back(node);
		return node;
	}

	BOOL addNodes(CPointerList<CNode<NodeData, ArcWeight> *> *nodes)
	{
		for(int i=0;i<nodes->size();i++)
			m_nodes.push_back(nodes->at(i));
		return TRUE;
	}

	CArc<NodeData, ArcWeight> *addArc(CArc<NodeData, ArcWeight> *arc)
	{
		m_arcs.push_back(arc);
		return arc;
	}
	
	BOOL addArcs(CPointerList<CArc<NodeData, ArcWeight> *> *arcs)
	{
		if(!arcs)
			return FALSE;

		for(int i=0;i<arcs->size();i++)
			m_arcs.push_back(arcs->at(i));
		return TRUE;
	}

	BOOL getNodesDestroy() const { return m_isNodesDestroy; }
	void setNodesDestroy(BOOL val) { m_isNodesDestroy = val; }

	BOOL getArcsDestroy() const { return m_isArcsDestroy; }
	void setArcsDestroy(BOOL val) { m_isArcsDestroy = val; }

	// 关联 arc 弧、开始结点和结束结点
	// 1、给 arc 添加开始结点和终止结点
	// 2、并把 arc 添加到开始结点的出弧列表，以及添加到结束结点的入弧列表
	void add(CArc<NodeData, ArcWeight> *arc, CNode<NodeData, ArcWeight> *nodeStart, CNode<NodeData, ArcWeight> *nodeEnd)
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

protected:
	CPointerList<CNode<NodeData, ArcWeight> *> m_nodes;
	CPointerList<CArc<NodeData, ArcWeight> *> m_arcs;

	// 类退出时，是否delete节点列表元素，默认为是
	BOOL m_isNodesDestroy;  
	// 类退出时，是否delete边列表元素，默认为是
	BOOL m_isArcsDestroy;
};