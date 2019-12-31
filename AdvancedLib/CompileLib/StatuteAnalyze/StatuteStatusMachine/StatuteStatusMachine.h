// StatuteStatusMachine.h: interface for the CStatuteStatusMachine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUTESTATUSMACHINE_H__9316458F_4E25_4EF3_B90F_1773D44E7458__INCLUDED_)
#define AFX_STATUTESTATUSMACHINE_H__9316458F_4E25_4EF3_B90F_1773D44E7458__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "..\StatuteStatusGraph\StatuteStatusGraph.h"
#include "..\..\LEX\LEXER\ILexer.h"

class CStatuteStatusMachine  
{
public:
	CStatuteStatusMachine();
	CStatuteStatusMachine(CStatuteStatusGraph *statuteStatusGraph);
	virtual ~CStatuteStatusMachine();

	// 初始化当前节点
	BOOL initCurrentNode();

	void setCurrentNode(CStatuteStatusGraphNode *node);
	CStatuteStatusGraphNode *getCurrentNode();

	// 从当前节点走指定名称的出弧
	int goThrough(MachineToken *arcData);

	BOOL isCurrentNodeAccepted();
	BOOL isCurrentNodeFinal();

	int getNodeCount();

	CStatuteStatusGraph * getStatuteStatusGraph() const { return m_statuteStatusGraph; }
	void setStatuteStatusGraph(CStatuteStatusGraph * val) { m_statuteStatusGraph = val; }
private:
	CStatuteStatusGraph *m_statuteStatusGraph;

};

#endif // !defined(AFX_STATUTESTATUSMACHINE_H__9316458F_4E25_4EF3_B90F_1773D44E7458__INCLUDED_)
