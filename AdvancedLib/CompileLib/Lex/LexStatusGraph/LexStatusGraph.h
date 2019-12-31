// StatusGraph.h: interface for the CStatusGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSGRAPH_H__EDBAEACB_C869_49A7_8743_C6BC21AEEFE8__INCLUDED_)
#define AFX_STATUSGRAPH_H__EDBAEACB_C869_49A7_8743_C6BC21AEEFE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <c++\FoundationLib\DataStructLib\SelfContainer\Graph.h>
#include "StatusGraphNode.h"
#include "StatusGraphArc.h"

// 词法分析状态图类
// 包含静态的结点和边
// 是结点和边的存储类，同时便于销毁处理
// 该类不包含对状态图的操作，操作状态图请用状态机类
class CLexStatusGraph : public CGraph<CStatusGraphNode *, CStatusGraphArc *>
{
public:
	CLexStatusGraph();
	virtual ~CLexStatusGraph();

	// 关联弧和 from 结点以及 to 结点
	void genRelationship(CStatusGraphArc *arc, CStatusGraphNode *from=NULL, CStatusGraphNode *to=NULL);
	
	// 从当前结点延接受 ch 字符的边移动，并返回下一节点
// 	CNode *move(CNode *currentNode, char ch);
};

#endif // !defined(AFX_STATUSGRAPH_H__EDBAEACB_C869_49A7_8743_C6BC21AEEFE8__INCLUDED_)
