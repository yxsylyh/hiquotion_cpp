#include "StdAfx.h"
#include "StringArrayExt.h"


CStringArrayExt::CStringArrayExt(void)
{
}


CStringArrayExt::~CStringArrayExt(void)
{
}

BOOL CStringArrayExt::intersect( CStringArray *array1, CStringArray *array2 )
{
	if(!array1 || !array2)
		return FALSE;

	if(array1->GetCount()<=0 || array2->GetCount()<=0)
		return FALSE;

	for(int i1=0;i1<array1->GetCount();i1++)
	{
		for(int i2=0;i2<array2->GetCount();i2++)
		{
			if(array1->GetAt(i1)==array2->GetAt(i2))
				return TRUE;
		}
	}

	return FALSE;
}

BOOL CStringArrayExt::isContain( CStringArray *array, CString str )
{
	if(!array)
		return FALSE;

	if(array->GetCount()<=0)
		return FALSE;

	if(str.GetLength()<=0)
		return FALSE;

	for(int i=0;i<array->GetCount();i++)
	{
		CString a1=array->GetAt(i);
		if(a1.GetLength()<=0)
			continue;

		if(a1==str)
			return TRUE;
	}

	return FALSE;
}
