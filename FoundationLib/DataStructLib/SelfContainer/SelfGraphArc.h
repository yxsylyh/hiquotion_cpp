// SelfGraphArc.h: interface for the CSelfGraphArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SELFGRAPHARC_H__061BDA90_8FB1_49D7_8273_2D446DD9650D__INCLUDED_)
#define AFX_SELFGRAPHARC_H__061BDA90_8FB1_49D7_8273_2D446DD9650D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\PointerList.h>

template <class Node, class ArcData>
class CSelfGraphArc  
{
public:
	CSelfGraphArc(){}
	CSelfGraphArc(Node from, Node to, ArcData data)
		: m_from(from), m_to(to), m_arcData(data)
	{
	}

	virtual ~CSelfGraphArc(){}

	Node getNodeFrom() const { return m_from; }
	void setNodeFrom(Node val) { m_from = val; }

	Node getNodeTo() const { return m_to; }
	void setNodeTo(Node val) { m_to = val; }

	ArcData getArcData() const { return m_arcData; }
	void setArcData(ArcData val) { m_arcData = val; }

protected:
	Node m_from;
	Node m_to;

	ArcData m_arcData;
};

#endif // !defined(AFX_SELFGRAPHARC_H__061BDA90_8FB1_49D7_8273_2D446DD9650D__INCLUDED_)
