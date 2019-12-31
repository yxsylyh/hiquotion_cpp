// Graph.h: interface for the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH_H__60BF83A9_FFAC_46CF_BB4C_E298E5A9EF29__INCLUDED_)
#define AFX_GRAPH_H__60BF83A9_FFAC_46CF_BB4C_E298E5A9EF29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\PointerList.h>

template <class Node, class Arc>
class CGraph  
{
public:
	CGraph()
	: m_startNode(NULL)
	{
		m_nodeList.setSelfDestroy(TRUE);
		m_arcList.setSelfDestroy(TRUE);
	};

	virtual ~CGraph()
	{
	};

	void addNode(Node node)
	{
		m_nodeList.push_back(node);
	}

	void addArc(Arc arc)
	{
		m_arcList.push_back(arc);
	}

	int getNodeCount()
	{
		return m_nodeList.size();
	}

	Node getNode(int index)
	{
		if(index>=0 && index<m_nodeList.size())
			return m_nodeList.at(index);

		return NULL;
	}

	int getNodeIndex(Node node)
	{
		return m_nodeList.getIndexOf(node);
	}

	int getArcCount()
	{
		return m_arcList.size();
	}

	Arc getArc(int index)
	{
		if(index>=0 && index<m_arcList.size())
			return m_arcList.at(index);

		return NULL;
	}

	int getArcIndex(Arc arc)
	{
		return m_arcList.getIndexOf(arc);
	}

	virtual Node removeNode(int index)
	{
		return m_nodeList.removeByIndex(index);
	}

	virtual Node removeNode(Node node)
	{
		return m_nodeList.remove(node);
	}

	void removeAllNodes()
	{
		m_nodeList.destroyAll();
	}
	
	virtual Arc removeArc(int index)
	{
		return m_arcList.removeByIndex(index);
	}

	virtual Arc removeArc(Arc arc)
	{
		return m_arcList.remove(arc);
	}

	void removeAllArcs()
	{
		m_arcList.destroyAll();
	}

	Node getStartNode() const { return m_startNode; }
	void setStartNode(Node val) { m_startNode = val; }

	BOOL isSelfDestroyNodes() const { return m_nodeList.isSelfDestroy(); }
	void setSelfDestroyNodes(BOOL val) { m_nodeList.setSelfDestroy(val); }

	BOOL isSelfDestroyArcs() const { return m_arcList.isSelfDestroy(); }
	void setSelfDestroyArcs(BOOL val) { m_arcList.setSelfDestroy(val); }

protected:
	CPointerList<Node> m_nodeList;
	CPointerList<Arc> m_arcList;
	Node m_startNode;
};

#endif // !defined(AFX_GRAPH_H__60BF83A9_FFAC_46CF_BB4C_E298E5A9EF29__INCLUDED_)
