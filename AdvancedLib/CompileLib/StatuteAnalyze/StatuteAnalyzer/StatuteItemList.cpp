// StatuteItemList.cpp: implementation of the CStatuteItemList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteItemList.h"
#include "../MemManager/MemManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteItemList::CStatuteItemList()
{

}

CStatuteItemList::CStatuteItemList(CStatuteItemList *lst)
{
	if(!lst)
		return;

	for(int i=0;i<lst->size();i++)
	{
		StatuteItem *statuteItem=lst->at(i);
		if(!statuteItem)
			continue;

		push_back(statuteItem);
	}
}

CStatuteItemList::~CStatuteItemList()
{

}

// 检查当前规约条目列表中是否包含指定名称的规约条目
BOOL CStatuteItemList::isContainedByStatuteName( string name )
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;
		
		Statute *statute=statuteItem->statute;
		if(!statute)
			continue;
		
		if(statute->statuteName==name)
			return TRUE;
	}
	
	return FALSE;
}

// 检查是否存在在最终位置的条目
BOOL CStatuteItemList::isContainItemInFinalPosition()
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;
		
		if(statuteItem->isFinalItemPosition())
			return TRUE;
	}
	
	return FALSE;
}

void CStatuteItemList::getStatuteItemListInFinalPosition(CStatuteItemList *retList)
{
	if(!retList)
		return;

	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;
		
		if(statuteItem->isFinalItemPosition())
			retList->push_back(statuteItem);
	}
}

// 根据规约名称获取规约条目列表
void CStatuteItemList::getStatuteItemListbyName( string name, CStatuteItemList *retList )
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;

		Statute *statute=statuteItem->statute;
		if(!statute)
			continue;
		
		if(statute->statuteName==name)
		{
//			if(!((CValueList<StatuteItem *> *)retList)->contain(statuteItem))
			if(!retList->contain(statuteItem))
				retList->push_back(statuteItem);
		}
	}
}

// 根据第一个规约式的规约名称来获取规约条目列表
// 返回值：
// 0，成功
// -1，规约式条目列表中的第一个规约式为空指针
// -2，第一个规约式条目中的规约式指针为空
// -3，第一个规约式的规约名称为空
int CStatuteItemList::getStatuteItemListby1stStatuteName( CStatuteItemList *retList )
{
	StatuteItem *statuteItem=at(0);
	if(!statuteItem)
		return -1;
	
	Statute *statute=statuteItem->statute;
	if(!statute)
		return -2;
	
	string name=statute->statuteName;
	if(name=="")
		return -3;
	
	getStatuteItemListbyName(name, retList);
	if(retList->size()<=0)
		return -4;  // 至少包含一个，所以这个判断恐怕没什么用

	return 0;
}

// 获取条目位置不在最后的规约式条目列表
void CStatuteItemList::getStatuteItemListNotinFinalPosition(CStatuteItemList *retList)
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;

		if(!statuteItem->isFinalItemPosition())
			retList->push_back(statuteItem);
	}
}

// 获取token名称为name的当前规约条目列表
void CStatuteItemList::getCurrentStatuteItemListbyTokenName(string name, CStatuteItemList *retList)
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;
		
		if(statuteItem->isFinalItemPosition())
			continue;
		
		Statute *statute=statuteItem->statute;
		if(!statute)
			continue;
		
		MachineToken *token=statute->tokenList.at(statuteItem->itemPosition);
		if(!token)
			continue;
		
		if(token->token==name)
			retList->push_back(statuteItem);
	}
}

// 获取当前列表中所有规约式的下一个规约条目的列表
void CStatuteItemList::genNextStatuteItemList(CStatuteItemList *retList)
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;

		StatuteItem *item=statuteItem->genNextStatuteItem();
		if(item)
		{
			CMemManager::addStatuteItem(item);
			retList->push_back(item);
		}
	}
}

// 闭包运算，即遍历自身列表，在初始规约条目列表中查找，将当前规约条目是非终结符的规约条目添加到自身列表中
void CStatuteItemList::closure( CStatuteItemList &origStatuteItemList )
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;
		
		if(statuteItem->isFinalItemPosition())
			continue;
		
		Statute *statute=statuteItem->statute;
		if(!statute)
			continue;
		
		MachineToken *token=statute->tokenList.at(statuteItem->itemPosition);
		if(!token)
			continue;

		if(token->token=="")
			continue;
		
		if(origStatuteItemList.isContainedByStatuteName(token->token))
		{
			CStatuteItemList lst;
			origStatuteItemList.getStatuteItemListbyName(token->token, &lst);

			for(int i=0;i<lst.size();i++)
			{
				StatuteItem *item=lst.at(i);
				if(!item)
					continue;

				Statute *statute=item->statute;
				if(!statute)
					continue;

				if(!containbyKey(item->printStatute()))
					push_back(item);
			}
		}
	}
}

std::string CStatuteItemList::genStatuteKey()
{
	string key="{";
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;

		key+=statuteItem->printStatute();
		if(i!=size()-1)
			key+="}|{";
		else
			key+="}";
	}

	return key;
}

BOOL CStatuteItemList::containbyKey(string key)
{
	for(int i=0;i<size();i++)
	{
		StatuteItem *statuteItem=at(i);
		if(!statuteItem)
			continue;
		
		if(statuteItem->printStatute()==key)
			return TRUE;
	}

	return FALSE;
}


