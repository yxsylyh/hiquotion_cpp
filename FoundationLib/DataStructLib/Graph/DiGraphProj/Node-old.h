// Node.h: interface for the CNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODE_H__0D64677B_D37B_4260_9396_DFA98782BE04__INCLUDED_)
#define AFX_NODE_H__0D64677B_D37B_4260_9396_DFA98782BE04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #include "INodeData.h"
#include "Arc.h"

// 图的节点，NodeData是节点的数据，Arc是弧
template <class NodeData, class ArcWeight>
class CArc;

template <class NodeData, class ArcWeight>
class CNode  
{
public:
	CNode()
	{
		m_data=NULL;
		m_isFinal=FALSE;
		m_nodeType=0;
	};

	CNode(NodeData data)
	{
		m_data=data;
		m_isFinal=FALSE;
		m_nodeType=0;
	};

	CNode(NodeData data, BOOL isFinal)
	{
		m_data=data;
		m_isFinal=isFinal;
		m_nodeType=0;
	};
	
	CNode(NodeData data, BOOL isFinal, unsigned int nodeType)
	{
		m_data=data;
		m_isFinal=isFinal;
		m_nodeType=nodeType;
	};
	
	virtual ~CNode(){};

	NodeData getData() const { return m_data; }
	void setData(NodeData val) { m_data = val; }

	void clearArcOutList()
	{
		m_arcOutList.clear();
	}

	void clearArcInList()
	{
		m_arcInList.clear();
	}

	void clearArcList()
	{
		m_arcOutList.clear();
		m_arcInList.clear();
	}

	BOOL addArcOut(CArc<NodeData, ArcWeight> *arcOut)
	{
		if(!arcOut)
			return FALSE;

		m_arcOutList.push_back(arcOut);
		return TRUE;
	}

	BOOL addArcIn(CArc<NodeData, ArcWeight> *arcIn)
	{
		if(!arcIn)
			return FALSE;

		m_arcInList.push_back(arcIn);
		return TRUE;
	}

	int getArcOutCount()
	{
		return m_arcOutList.size();
	}

	int getArcInCount()
	{
		return m_arcInList.size();
	}

	CArc<NodeData, ArcWeight> *getArcOut(int index)
	{
		if(index<0 || index>=m_arcOutList.size())
			return NULL;

		return m_arcOutList.at(index);
	}

	CArc<NodeData, ArcWeight> *getArcIn(int index)
	{
		if(index<0 || index>=m_arcInList.size())
			return NULL;

		return m_arcInList.at(index);
	}
	
	BOOL isFinal() const { return m_isFinal; }
	void setFinal(BOOL val) { m_isFinal = val; }

	unsigned int getNodeType() const { return m_nodeType; }
	void setNodeType(unsigned int val) { m_nodeType = val; }

private:
	NodeData m_data;   // 数据
	CPointerList<CArc<NodeData, ArcWeight> *> m_arcOutList;  // 出弧列表
	CPointerList<CArc<NodeData, ArcWeight> *> m_arcInList;   // 入弧列表

	BOOL m_isFinal;
	unsigned int m_nodeType;
};

#endif // !defined(AFX_NODE_H__0D64677B_D37B_4260_9396_DFA98782BE04__INCLUDED_)
