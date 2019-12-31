// StatusGraphic.h: interface for the CStatusGraphic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSGRAPHIC_H__911D3E31_8CCB_4A34_81F1_B2BDA4703492__INCLUDED_)
#define AFX_STATUSGRAPHIC_H__911D3E31_8CCB_4A34_81F1_B2BDA4703492__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DiGraphic.h"
// #include "Node.h"
// #include "Arc.h"

// template <class Node, class NodeKey, class Arc, class ArcKey>
template <class NodeData, class ArcWeight>
class CStatusGraphic : public CDiGraphic<NodeData, ArcWeight>
{
public:
	CStatusGraphic()
	{
		m_startNode=new CNode<NodeData, ArcWeight>();
// 		m_endNode=new CNode<NodeData, ArcWeight>();

		m_isStartNodeDestroy=TRUE;
// 		m_isEndNodeDestroy=TRUE;
//		m_startNode.setArcFirstOut(&m_outArcFromStartNode);

// 		m_outArcFromStartNode.setNodeStart(&m_startNode);
// 		m_outArcFromStartNode.setNodeEnd(NULL);
// 		m_outArcFromStartNode.setNextArcOutFromStart(NULL);
// 		m_outArcFromStartNode.setNextArcToEnd(NULL);
		
// 		m_inArcToStartNode.setNodeStart(NULL);
// 		m_inArcToStartNode.setNodeEnd(&m_startNode);
// 		m_inArcToStartNode.setNextArcOutFromStart(NULL);
// 		m_inArcToStartNode.setNextArcToEnd(NULL);

// 		m_endNode.setArcFirstIn(&m_inArcToEndNode);

// 		m_inArcToEndNode.setNodeEnd(&m_endNode);
// 		m_inArcToEndNode.setNodeStart(NULL);
// 		m_inArcToEndNode.setNextArcOutFromStart(NULL);
// 		m_inArcToEndNode.setNextArcToEnd(NULL);

// 		m_outArcFromEndNode.setNodeStart(&m_endNode);
// 		m_outArcFromEndNode.setNodeEnd(NULL);
// 		m_outArcFromEndNode.setNodeStart(NULL);
// 		m_outArcFromEndNode.setNodeEnd(NULL);
	};

	virtual ~CStatusGraphic()
	{
// 		m_nodes.destroyAll();
// 		m_arcs.destroyAll();

		if(m_isStartNodeDestroy)
			delete m_startNode;
// 		if(m_isEndNodeDestroy)
// 			delete m_endNode;
	};

	CNode<NodeData, ArcWeight> *getStartNode() { return m_startNode; }
	void setStartNode(CNode<NodeData, ArcWeight> *val)
	{
		if(!val)
			return;

		if(m_isStartNodeDestroy)
			delete m_startNode;
		m_startNode = val;
	}

	void getEndNodeList(CPointerList<CNode<NodeData, ArcWeight> *> *endNodeList)
	{
		return &m_endNodeList;
	}

	int getEndNodeCount()
	{
		return (int)m_endNodeList.size();
	}

	CNode<NodeData, ArcWeight> *getEndNode(int index)
	{
		if(index<0 || index>=getEndNodeCount())
			return NULL;

		return m_endNodeList.at(index);
	}

// 	CNode<NodeData, ArcWeight> *getEndNode() { return m_endNode; }
// 	void setEndNode(CNode<NodeData, ArcWeight> *val)
// 	{
// 		if(!val)
// 			return;
// 
// 		if(m_isEndNodeDestroy)
// 			delete m_endNode;
// 		m_endNode = val;
// 	}

	BOOL getStartNodeDestroy() const { return m_isStartNodeDestroy; }
	void setStartNodeDestroy(BOOL val) { m_isStartNodeDestroy = val; }

// 	BOOL getEndNodeDestroy() const { return m_isEndNodeDestroy; }
// 	void setEndNodeDestroy(BOOL val) { m_isEndNodeDestroy = val; }

	// 	CArc *getOutArcFromStartNode() { return &m_outArcFromStartNode; }
// // 	void setOutArcFromStartNode(CArc<ArcKey, CNode *, CArc *> val) { m_outArcFromStartNode = val; }
// 
// 	CArc getInArcToStartNode() const { return m_inArcToStartNode; }
// // 	void setInArcToStartNode(CArc val) { m_inArcToStartNode = val; }
// 
// 	CArc *getArcToEndNode() { return &m_inArcToEndNode; }
// // 	void setArcToEndNode(CArc<ArcKey, CNode *, CArc *> val) { m_inArcToEndNode = val; }
// 
// 	CArc getOutArcFromEndNode() const { return m_outArcFromEndNode; }
// // 	void setOutArcFromEndNode(CArc val) { m_outArcFromEndNode = val; }

protected:
	CNode<NodeData, ArcWeight> *m_startNode;//, *m_endNode;

	CPointerList<CNode<NodeData, ArcWeight> *> m_endNodeList;
// 	CArc m_outArcFromStartNode, m_inArcToStartNode;
// 	CArc m_outArcFromEndNode, m_inArcToEndNode;

	BOOL m_isStartNodeDestroy;
// 	BOOL m_isEndNodeDestroy;
};

#endif // !defined(AFX_STATUSGRAPHIC_H__911D3E31_8CCB_4A34_81F1_B2BDA4703492__INCLUDED_)
