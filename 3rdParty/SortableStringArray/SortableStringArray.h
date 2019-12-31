// SortableStringArray.h: interface for the CSortableStringArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SORTABLESTRINGARRAY_H__0973C972_E101_4164_ADA0_BEF5191500BD__INCLUDED_)
#define AFX_SORTABLESTRINGARRAY_H__0973C972_E101_4164_ADA0_BEF5191500BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSortableStringArray : public CStringArray  
{
public:
	CSortableStringArray();
	virtual ~CSortableStringArray();

public:
   void Sort();

private:
	BOOL CompareAndSwap(int pos);
	
};

#endif // !defined(AFX_SORTABLESTRINGARRAY_H__0973C972_E101_4164_ADA0_BEF5191500BD__INCLUDED_)
