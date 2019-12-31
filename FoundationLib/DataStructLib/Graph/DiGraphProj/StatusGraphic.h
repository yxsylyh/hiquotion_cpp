// StatusGraphic.h: interface for the CStatusGraphic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSGRAPHIC_H__A9FE39F1_A65A_4A1E_8943_B046CB96CBDA__INCLUDED_)
#define AFX_STATUSGRAPHIC_H__A9FE39F1_A65A_4A1E_8943_B046CB96CBDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DiGraphic.h"
#include "Node.h"
#include <C++\FoudationLib\DataStructLib\PointerList.h>

class CStatusGraphic : public CDiGraphic  
{
public:
	CStatusGraphic();
	virtual ~CStatusGraphic();

	CNode *getStartNode() { return m_startNode; }
	void setStartNode(CNode *val);

	int getEndNodeCount();
	CNode *getEndNode(int index);

	BOOL isStartNodeDestroy() const { return m_destroyStartNode; }
	void setStartNodeDestroy(BOOL val) { m_destroyStartNode = val; }
	
protected:
	CNode *m_startNode;
	CPointerList<CNode *> m_endNodeList;

	BOOL m_destroyStartNode;

};

#endif // !defined(AFX_STATUSGRAPHIC_H__A9FE39F1_A65A_4A1E_8943_B046CB96CBDA__INCLUDED_)
