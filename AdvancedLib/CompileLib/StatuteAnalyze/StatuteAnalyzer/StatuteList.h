// StatuteList.h: interface for the CStatuteList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUTELIST_H__00B80F17_F483_48CD_A8C4_4E3C885F6EC6__INCLUDED_)
#define AFX_STATUTELIST_H__00B80F17_F483_48CD_A8C4_4E3C885F6EC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoundationLib\DataStructLib\PointerList.h>
#include "../StatuteAnalyzer/Statute.h"
#include <string>

using namespace std;

class CStatuteList : public CPointerList<Statute *>  
{
public:
	CStatuteList();
	virtual ~CStatuteList();

	BOOL contain(string name);
	void getStatuteListbyName(string name, CStatuteList &retList);

};

#endif // !defined(AFX_STATUTELIST_H__00B80F17_F483_48CD_A8C4_4E3C885F6EC6__INCLUDED_)
