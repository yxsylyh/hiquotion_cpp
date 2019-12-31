// GridLayout.h: interface for the CGridLayout class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDLAYOUT_H__A916431A_B24C_46ED_AE0D_FF0E8AA914E0__INCLUDED_)
#define AFX_GRIDLAYOUT_H__A916431A_B24C_46ED_AE0D_FF0E8AA914E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Layout.h"

class CGridLayout : public CLayout
{
public:
	CGridLayout();
	CGridLayout(int rowCount, int colCount);
	CGridLayout(CRect rect);
	CGridLayout(CRect rect, int rowCount, int colCount);
	CGridLayout(RECT rc);
	CGridLayout(RECT rc, int rowCount, int colCount);
	CGridLayout(int left, int top, int width, int height);
	CGridLayout(int left, int top, int width, int height, int rowCount, int colCount);
	virtual ~CGridLayout();

	void getRect(int index, CRect &rect);
	void getFullScreenRect(CRect &rect);

	int getRowCount() const { return m_rowCount; }
	void setRowCount(int val)
	{
		if(val<=0)
			return;
		
		m_rowCount = val;
	}

	int getColCount() const { return m_colCount; }
	void setColCount(int val)
	{
		if(val<=0)
			return;
		
		m_colCount = val;
	}

protected:
	void getRect(int rowIndex, int colIndex, CRect &rect);
	
protected:
	int m_rowCount;
	int m_colCount;
};

#endif // !defined(AFX_GRIDLAYOUT_H__A916431A_B24C_46ED_AE0D_FF0E8AA914E0__INCLUDED_)
