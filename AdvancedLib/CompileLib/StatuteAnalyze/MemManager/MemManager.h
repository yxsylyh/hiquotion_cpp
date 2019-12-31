// MemManager.h: interface for the CMemManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMMANAGER_H__B2A363F0_1F8C_41AA_9406_A0653139FE87__INCLUDED_)
#define AFX_MEMMANAGER_H__B2A363F0_1F8C_41AA_9406_A0653139FE87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <C++\FoundationLib\DataStructLib\PointerList.h>
#include "../StatuteAnalyzer/StatuteList.h"

class CMemManager  
{
public:
	CMemManager();
	virtual ~CMemManager();

	static void addStatuteItem(StatuteItem *item);
	static void removeStatuteItem(StatuteItem *item);
	static void removeStatuteItemList(CPointerList<StatuteItem *> *lst);
	static void destroyAllStatuteItems();
	static int getStatuteItemCount();

};

#endif // !defined(AFX_MEMMANAGER_H__B2A363F0_1F8C_41AA_9406_A0653139FE87__INCLUDED_)
