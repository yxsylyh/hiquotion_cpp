// SortableStringArray.cpp: implementation of the CSortableStringArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "zzspbc.h"
#include "SortableStringArray.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSortableStringArray::CSortableStringArray()
{

}

CSortableStringArray::~CSortableStringArray()
{

}

void CSortableStringArray::Sort()
{
	BOOL bNotDone = TRUE;
	while (bNotDone)
	{
		bNotDone = FALSE;
		for(int pos = 0;pos < GetUpperBound();pos++)
			bNotDone |= CompareAndSwap(pos);
	}
}
BOOL CSortableStringArray::CompareAndSwap(int pos)
{
	CString temp;
	int posFirst = pos;
	int posNext = pos + 1;
	if (GetAt(posFirst).CompareNoCase(GetAt(posNext)) > 0)
	{
		temp = GetAt(posFirst);
		SetAt(posFirst, GetAt(posNext));
		SetAt(posNext, temp);
		return TRUE;
	}
	return FALSE;
}
