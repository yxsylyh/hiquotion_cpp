// MergeStatusGraph.h: interface for the CMergeStatusGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MERGESTATUSGRAPH_H__37F4D06F_354A_433B_AB6B_23F96193DE5B__INCLUDED_)
#define AFX_MERGESTATUSGRAPH_H__37F4D06F_354A_433B_AB6B_23F96193DE5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\SelfContainer\Graph.h>
#include "StatuteStatusGraphNode.h"
#include "StatuteStatusGraphArc.h"
#include "..\..\LEX\LEXER\ILexer.h"

class CStatuteStatusGraph : public CGraph<CStatuteStatusGraphNode *, CStatuteStatusGraphArc *>
{
public:
	CStatuteStatusGraph();
	virtual ~CStatuteStatusGraph();

	// 判断是否包含唯一标记的节点
	BOOL containNodeby(string statuteKey);
	// 取指定唯一标记的节点
	CStatuteStatusGraphNode *getNodeby(string statuteKey);

	// 将第一个非初始节点设置为接受节点
	BOOL setAcceptNode();

	// 打印状态图信息
	void printGraphInfo();

	// 初始化当前节点
	BOOL initCurrentNode();

	// 从当前节点走指定名称的出弧
	int walkThroughArc(MachineToken *arcData);

	// 当前节点是否是可接受的
	BOOL isCurrentNodeAccepted();
	// 当前节点是否是终节点
	BOOL isCurrentNodeFinal();
	// 获取终节点唯一规约式在规约条目列表中的索引
// 	int getIndexInStatuteItemList();
	// 获取终节点唯一规约式
	Statute *getStatuteOfFinal();
	// 获取终节点唯一规约式中token的个数
	int getTokenCount();
	// 获取终节点唯一规约式中规约的名称
	std::string getStatuteName();

	CStatuteStatusGraphNode * getCurrentNode() const { return m_currentNode; }
	void setCurrentNode(CStatuteStatusGraphNode * val) { m_currentNode = val; }

private:
	CStatuteStatusGraphNode *m_currentNode;
};

#endif // !defined(AFX_MERGESTATUSGRAPH_H__37F4D06F_354A_433B_AB6B_23F96193DE5B__INCLUDED_)
