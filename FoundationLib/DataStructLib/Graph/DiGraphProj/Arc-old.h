// Arc.h: interface for the CArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARC_H__C6A64DC4_B1B0_4834_9FFC_5BB92500170C__INCLUDED_)
#define AFX_ARC_H__C6A64DC4_B1B0_4834_9FFC_5BB92500170C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Node.h"

// 图节点之间的弧，也叫做边，Weight是弧的权重，Node是节点，Arc是弧
template <class NodeData, class ArcWeight>
class CNode;

template <class NodeData, class ArcWeight>
class CArc  
{
public:
	CArc()
	{
		m_weight=NULL;
		m_isWeightDestroy=FALSE;
		m_nodeStart=NULL;
		m_nodeToEnd=NULL;
	};

	CArc(CNode<NodeData, ArcWeight> *nodeStart, CNode<NodeData, ArcWeight> *nodeEnd)
	{
		m_weight=NULL;
		m_isWeightDestroy=FALSE;
		m_nodeStart=nodeStart;
		m_nodeToEnd=nodeEnd;
	};

	CArc(ArcWeight data, CNode<NodeData, ArcWeight> *nodeStart, CNode<NodeData, ArcWeight> *nodeEnd)
	{
		m_weight=data;
		m_isWeightDestroy=FALSE;
		m_nodeStart=nodeStart;
		m_nodeToEnd=nodeEnd;
	};

	CArc(ArcWeight data, BOOL isWeightDestroy, CNode<NodeData, ArcWeight> *nodeStart, CNode<NodeData, ArcWeight> *nodeEnd)
	{
		m_weight=data;
		m_isWeightDestroy=isWeightDestroy;
		m_nodeStart=nodeStart;
		m_nodeToEnd=nodeEnd;
	};
	
	virtual ~CArc()
	{
		if(m_isWeightDestroy)
			delete m_weight;
	};

	ArcWeight getWeight() const { return m_weight; }
	void setWeight(ArcWeight val) { m_weight = val; }
	
	CNode<NodeData, ArcWeight> *getNodeStart() const { return m_nodeStart; }
	void setNodeStart(CNode<NodeData, ArcWeight> *val) { m_nodeStart = val; }
	
	CNode<NodeData, ArcWeight> *getNodeEnd() const { return m_nodeToEnd; }
	void setNodeEnd(CNode<NodeData, ArcWeight> *val) { m_nodeToEnd = val; }
	
	BOOL isNoWeight()
	{
		if(!m_weight)
			return TRUE;

		return FALSE;
	}
	
	BOOL isWeightDestroy() const { return m_isWeightDestroy; }
	void isWeightDestroy(BOOL val) { m_isWeightDestroy = val; }

protected:
	ArcWeight m_weight;     // 弧的权重
	BOOL m_isWeightDestroy; // 权重是否需要delete，默认是不需要
	CNode<NodeData, ArcWeight> *m_nodeStart;     // 起始节点
	CNode<NodeData, ArcWeight> *m_nodeToEnd;     // 终止节点
};

#endif // !defined(AFX_ARC_H__C6A64DC4_B1B0_4834_9FFC_5BB92500170C__INCLUDED_)
