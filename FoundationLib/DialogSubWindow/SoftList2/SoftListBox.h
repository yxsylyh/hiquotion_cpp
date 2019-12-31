#if !defined(AFX_SOFTLISTBOX_H__D66CAF8C_D46B_4E88_93D6_E9A77D10C439__INCLUDED_)
#define AFX_SOFTLISTBOX_H__D66CAF8C_D46B_4E88_93D6_E9A77D10C439__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SoftListBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSoftListBox window

#include "..\..\sai_cmd\SAICmd\Software.h"
#include "ListItemDlg.h"

#define LIST_ITEM_HIGHT 64

class CSoftListBox : public CCheckListBox
{
// Construction
public:
	CSoftListBox();

	//BOOL createDialogItems()

	void setSoftwareList(vector<CSoftware *> softwares);
	void clearItems();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoftListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSoftListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSoftListBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	vector<CListItemDlg *> m_items;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOFTLISTBOX_H__D66CAF8C_D46B_4E88_93D6_E9A77D10C439__INCLUDED_)
