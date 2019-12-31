// StatuteStatusGraphBuilder.h: interface for the CStatuteStatusGraphBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUTESTATUSGRAPHBUILDER_H__337B3EFD_F7BF_4D6F_BF7C_5F10D2025AE6__INCLUDED_)
#define AFX_STATUTESTATUSGRAPHBUILDER_H__337B3EFD_F7BF_4D6F_BF7C_5F10D2025AE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IStatuteStatusGraphBuilder.h"
#include "StatuteList.h"
#include <string>
#include "..\StatuteStatusGraph\StatuteStatusGraph.h"

class CStatuteStatusGraphBuilder : public IStatuteStatusGraphBuilder  
{
public:
	CStatuteStatusGraphBuilder();
	virtual ~CStatuteStatusGraphBuilder();

	int buildStatuteStatusGraph(CStatuteList *statuteList/*, CStatuteStatusGraph *graph*/);
	int buildStatuteStatusGraphFromDefText(std::string text, ILexer *lexer/*, CStatuteStatusGraph *graph*/, string statuteSymbol="=>", string lineSplitter="\r\n");
	int buildStatuteStatusGraphFromDefFile(std::string filePath, ILexer *lexer/*, CStatuteStatusGraph *graph*/, string statuteSymbol="=>", string lineSplitter="\r\n");
	int build();

	CStatuteList * getStatuteList() const { return m_statuteList; }
	void setStatuteList(CStatuteList * val) { m_statuteList = val; }

	CStatuteStatusGraph *getStatuteStatusGraph() const { return m_graph; }

	std::string getErrMsg() const { return m_errMsg; }
	
private:
	// 根据规约式列表，构造初始节点列表
	static int buildOrigNodeList(CStatuteItemList &statuteItemList, CPointerList<CStatuteStatusGraphNode *> &origNodeList);
	// 从初始节点列表，构造后续节点
	static int buildOtherNodes(CPointerList<CStatuteStatusGraphNode *> &origNodeList, CStatuteItemList &origStatuteItemList, CStatuteStatusGraph *graph);
	// 从初始节点列表中的节点，构造后续节点
	static int buildPostNodes(CStatuteStatusGraphNode *node, CPointerList<CStatuteStatusGraphNode *> &origNodeList, CStatuteItemList &origStatuteItemList, CStatuteStatusGraph *graph);
	// 将规约式列表转换成规约式条目列表
	static void statuteList2StatuteItemList(CStatuteList *statuteList, CStatuteItemList *statuteItemList);

private:
	CStatuteStatusGraph *m_graph;
	CStatuteList *m_statuteList;
	std::string m_errMsg;
};

#endif // !defined(AFX_STATUTESTATUSGRAPHBUILDER_H__337B3EFD_F7BF_4D6F_BF7C_5F10D2025AE6__INCLUDED_)
