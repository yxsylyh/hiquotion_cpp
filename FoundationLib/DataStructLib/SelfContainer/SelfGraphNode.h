// SelfGraphNode.h: interface for the CSelfGraphNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELFGRAPHNODE_H__ED133AD5_4019_4ABF_884A_7199007D2E03__INCLUDED_)
#define AFX_SELFGRAPHNODE_H__ED133AD5_4019_4ABF_884A_7199007D2E03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\PointerList.h>

template <class Arc, class NodeData>
class CSelfGraphNode  
{
public:
	CSelfGraphNode(){};
	CSelfGraphNode(NodeData data)
	{
		m_data=data;
	};

	virtual ~CSelfGraphNode(){};

	void addOutArc(Arc arc)
	{
		m_outArcList.push_back(arc);
	}

	void addInArc(Arc arc)
	{
		m_inArcList.push_back(arc);
	}

	Arc getOutArc(int index)
	{
		if(index>=0 && index<m_outArcList.size())
			return m_outArcList.at(index);

		return NULL;
	}

	Arc getInArc(int index)
	{
		if(index>=0 && index<m_inArcList.size())
			return m_inArcList.at(index);

		return NULL;
	}

	int getOutArcCount()
	{
		return m_outArcList.size();
	}

	int getInArcCount()
	{
		return m_inArcList.size();
	}

	Arc removeOutArc(int index)
	{
		return m_outArcList.remove(index);
	}

	Arc removeOutArc(Arc arc)
	{
		return m_outArcList.remove(arc);
	}

	Arc removeInArc(int index)
	{
		return m_inArcList.remove(index);
	}

	Arc removeInArc(Arc arc)
	{
		return m_inArcList.remove(arc);
	}

	void clearOutArcList(BOOL isDestroy=FALSE)
	{
		if(isDestroy)
			m_outArcList.destroyAll();

		m_outArcList.clear();
	}
	void clearInArcList(BOOL isDestroy=FALSE)
	{
		if(isDestroy)
			m_inArcList.destroyAll();

		m_inArcList.clear();
	}

protected:
	CPointerList<Arc> m_outArcList;
	CPointerList<Arc> m_inArcList;

	NodeData m_data;
};

#endif // !defined(AFX_SELFGRAPHNODE_H__ED133AD5_4019_4ABF_884A_7199007D2E03__INCLUDED_)
