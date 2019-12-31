// Node.h: interface for the CNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NODE_H__052D79B5_5103_4A4A_BE37_D2FDE7970C23__INCLUDED_)
#define AFX_NODE_H__052D79B5_5103_4A4A_BE37_D2FDE7970C23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Arc.h"
#include "INodeData.h"
#include <C++\FoudationLib\DataStructLib\PointerList.h>

class CArc;

class CNode  
{
public:
	CNode();
	CNode(INodeData *nodeData);
	virtual ~CNode();

	INodeData * getNodeData() const { return m_nodeData; }
	void setNodeData(INodeData * val) { m_nodeData = val; }

	void clearArcOutList();
	void clearArcInList();
	void clearArcList();

	BOOL addArcOut(CArc *arcOut);
	BOOL addArcIn(CArc *arcIn);

	int getArcOutCount();
	int getArcInCount();

	CArc *getArcOut(int index);
	CArc *getArcIn(int index);

protected:
	INodeData *m_nodeData;

	CPointerList<CArc *> m_arcOutList;  // 出弧列表
	CPointerList<CArc *> m_arcInList;   // 入弧列表
};

#endif // !defined(AFX_NODE_H__052D79B5_5103_4A4A_BE37_D2FDE7970C23__INCLUDED_)
