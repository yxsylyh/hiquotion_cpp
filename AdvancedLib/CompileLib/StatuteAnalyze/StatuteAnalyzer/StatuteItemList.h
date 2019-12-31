// StatuteItemList.h: interface for the CStatuteItemList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUTEITEMLIST_H__CDCFBBB6_6E4F_453B_9E04_97B44CE83740__INCLUDED_)
#define AFX_STATUTEITEMLIST_H__CDCFBBB6_6E4F_453B_9E04_97B44CE83740__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\PointerList.h>
#include "Statute.h"

class CStatuteItemList : public CPointerList<StatuteItem *>  
{
public:
	CStatuteItemList();
	CStatuteItemList(CStatuteItemList *lst);
	virtual ~CStatuteItemList();

	// 检查当前规约条目列表中是否包含指定名称的规约条目
	BOOL isContainedByStatuteName(string name);
	// 检查是否存在在最终位置的条目
	BOOL isContainItemInFinalPosition();
	// 获取在最终位置的条目个数
	void getStatuteItemListInFinalPosition(CStatuteItemList *retList);
	// 根据规约名称获取规约条目列表
	void getStatuteItemListbyName(string name, CStatuteItemList *retList);
	// 根据第一个规约式的规约名称来获取规约条目列表
	int getStatuteItemListby1stStatuteName(CStatuteItemList *retList);
	// 获取条目位置不在最后的规约式条目列表
	void getStatuteItemListNotinFinalPosition(CStatuteItemList *retList);
	// 获取token名称为name的当前规约条目列表
	void getCurrentStatuteItemListbyTokenName(string name, CStatuteItemList *retList);
	// 获取当前列表中所有规约式的下一个规约条目的列表
	void genNextStatuteItemList(CStatuteItemList *retList);
	// 闭包运算，即遍历自身列表，在初始规约条目列表中查找，将当前规约条目是非终结符的规约条目添加到自身列表中
	void closure(CStatuteItemList &origStatuteItemList);

	// 生成多个规约式条目为一个字符串，就是规约式中带小点的那种字符串的组合，用来唯一标记该规约式列表所在节点
	string genStatuteKey();
	// 判断该规约式列表是否包含指定的唯一标记
	BOOL containbyKey(string key);
};

#endif // !defined(AFX_STATUTEITEMLIST_H__CDCFBBB6_6E4F_453B_9E04_97B44CE83740__INCLUDED_)
