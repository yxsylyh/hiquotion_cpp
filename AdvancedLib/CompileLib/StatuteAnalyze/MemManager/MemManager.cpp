// MemManager.cpp: implementation of the CMemManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemManager.h"
#include <C++\FoundationLib\DataStructLib\PointerList.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static CPointerList<StatuteItem *> m_statuteItemList;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemManager::CMemManager()
{

}

CMemManager::~CMemManager()
{

}

void CMemManager::addStatuteItem(StatuteItem *item)
{
	if(!item)
		return;
	
	if(!m_statuteItemList.contain(item))
		m_statuteItemList.push_back(item);
}

void CMemManager::removeStatuteItem(StatuteItem *item)
{
	if(!item)
		return;

	m_statuteItemList.remove(item);
}

void CMemManager::removeStatuteItemList(CPointerList<StatuteItem *> *lst)
{
	if(!lst)
		return;

	for(int i=0;i<lst->size();i++)
	{
		m_statuteItemList.remove(lst->at(i));
	}
}

void CMemManager::destroyAllStatuteItems()
{
	m_statuteItemList.destroyAll();
	m_statuteItemList.clear();
}

int CMemManager::getStatuteItemCount()
{
	return m_statuteItemList.size();
}
