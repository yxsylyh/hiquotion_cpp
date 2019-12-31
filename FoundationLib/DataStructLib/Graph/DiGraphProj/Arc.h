// Arc.h: interface for the CArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARC_H__477187B1_99D9_4B3A_AA02_25AEF35D6E5A__INCLUDED_)
#define AFX_ARC_H__477187B1_99D9_4B3A_AA02_25AEF35D6E5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Node.h"
#include "IArcWeight.h"

class CNode;

class CArc  
{
public:
	CArc();
	CArc(IArcWeight *arcWeight);
	CArc(CNode *nodeStart, CNode *nodeEnd);
	CArc(IArcWeight *arcWeight, CNode *nodeStart, CNode *nodeEnd);
	CArc(IArcWeight *arcWeight, BOOL isWeightDestroy, CNode *nodeStart, CNode *nodeEnd);
	virtual ~CArc();

	IArcWeight * getArcWeight() const { return m_arcWeight; }
	void setArcWeight(IArcWeight * val) { m_arcWeight = val; }

	CNode *getNodeStart() const { return m_nodeStart; }
	void setNodeStart(CNode *val) { m_nodeStart = val; }
	
	CNode *getNodeEnd() const { return m_nodeToEnd; }
	void setNodeEnd(CNode *val) { m_nodeToEnd = val; }

	BOOL isWeightDestroy() const { return m_isWeightDestroy; }
	void setWeightDestroy(BOOL val) { m_isWeightDestroy = val; }

protected:
	IArcWeight *m_arcWeight;     // 弧的权重

	BOOL m_isWeightDestroy; // 权重是否需要delete，默认是不需要
	CNode *m_nodeStart;     // 起始节点
	CNode *m_nodeToEnd;     // 终止节点
};

#endif // !defined(AFX_ARC_H__477187B1_99D9_4B3A_AA02_25AEF35D6E5A__INCLUDED_)
