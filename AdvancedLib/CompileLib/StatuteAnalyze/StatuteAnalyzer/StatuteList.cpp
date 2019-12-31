// StatuteList.cpp: implementation of the CStatuteList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StatuteList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStatuteList::CStatuteList()
{

}

CStatuteList::~CStatuteList()
{

}

BOOL CStatuteList::contain( string name )
{
	for(int i=0;i<size();i++)
	{
		Statute *statute=at(i);
		if(!statute)
			continue;
		
		if(statute->statuteName==name)
			return TRUE;
	}

	return FALSE;
}

void CStatuteList::getStatuteListbyName( string name, CStatuteList &retList )
{
	for(int i=0;i<size();i++)
	{
		Statute *statute=at(i);
		if(!statute)
			continue;

		if(statute->statuteName==name)
			retList.push_back(statute);
	}
}
