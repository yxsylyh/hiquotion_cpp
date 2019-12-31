// MergenceStatusGraphNode.h: interface for the CMergenceStatusGraphNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MERGENCESTATUSGRAPHNODE_H__922E4D9D_844B_42D3_AE71_A96170429DE6__INCLUDED_)
#define AFX_MERGENCESTATUSGRAPHNODE_H__922E4D9D_844B_42D3_AE71_A96170429DE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StatuteStatusGraphArc.h"
#include <string>
#include <c++\FoundationLib\DataStructLib\SelfContainer\SelfGraphNode.h>
#include "../StatuteAnalyzer/Statute.h"
#include "../StatuteAnalyzer/StatuteItemList.h"
// #include "StatuteInfoList.h"

using namespace std;

class CStatuteStatusGraphArc;

class CStatuteStatusGraphNode : public CSelfGraphNode<CStatuteStatusGraphArc *, int>
{
public:
	CStatuteStatusGraphNode();
	CStatuteStatusGraphNode(CStatuteItemList *itemList);
	CStatuteStatusGraphNode(BOOL isFinal);
	CStatuteStatusGraphNode(std::string errMsg);
	CStatuteStatusGraphNode(BOOL isFinal, std::string errMsg);
	virtual ~CStatuteStatusGraphNode();

	// 判断 token 和 弧数据arcData 是否相等
	BOOL isArcDataEquals(MachineToken *token, MachineToken *arcData);

	// 节点是否包含指定名称的出弧
	BOOL containOutArcBy(MachineToken *arcData);

	// 根据名称来获取出弧列表（为什么是列表？因为出弧中可能有名字相同的）
	void getOutArcsBy(MachineToken *arcData, CPointerList<CStatuteStatusGraphArc *> &arcs);

	// 检查是否有到 nodeTo 节点的出弧
	BOOL hasOutArcToNode(CStatuteStatusGraphNode *nodeTo);
	
	// 添加规约式条目
	void add(StatuteItem *item);
	void add(Statute *statute, int indexInStatuteList);
	void add(Statute *statute, int indexInStatuteList, int itemPosition);

	// 打印规约式条目信息
	string printStatuteItemListInfo();

	BOOL isOrigNode() const { return m_isOrigNode; }
	void setOrigNode(BOOL val) { m_isOrigNode = val; }

	BOOL isFinal() const { return m_isFinal; }
	void setFinal(BOOL val) { m_isFinal = val; }
	
// 	int getIndexInStatuteItemList() const { return m_indexInStatuteList; }
// 	void setIndexInStatuteList(int val) { m_indexInStatuteList = val; }
	
	Statute * getStatuteOfFinal() const { return m_statuteOfFinal; }
	void setStatuteOfFinal(Statute * val) { m_statuteOfFinal = val; }

	int getTokenCount() const { return m_tokenCount; }
	void setTokenCount(int val) { m_tokenCount = val; }

	BOOL isAccepted() const { return m_isAccepted; }
	void setAccepted(BOOL val) { m_isAccepted = val; }

	std::string getErrMsg() const { return m_errMsg; }
	void setErrMsg(std::string val) { m_errMsg = val; }
	
	CStatuteItemList * getStatuteItemList() const { return m_itemList; }
	void setItemList(CStatuteItemList * val) { m_itemList = val; }

private:
	BOOL m_isOrigNode;  // 用来区分初始节点和后续创建的节点，第一个后续创建的节点是接受节点，所以该变量是用来查找接受节点时区分用的
	BOOL m_isFinal;  // 是否是终节点
// 	int m_indexInStatuteList;  // 对于终节点，需要知道在规约列表中的索引
	Statute *m_statuteOfFinal;  // 对于终节点，需要知道在规约列表中的规约式
	int m_tokenCount;  // 对于终节点，需要知道token的个数，以便于上层程序知道从栈中弹出多少个节点
	BOOL m_isAccepted;  // 是否是可接受节点
	string m_errMsg;

	CStatuteItemList *m_itemList;
};

#endif // !defined(AFX_MERGENCESTATUSGRAPHNODE_H__922E4D9D_844B_42D3_AE71_A96170429DE6__INCLUDED_)
