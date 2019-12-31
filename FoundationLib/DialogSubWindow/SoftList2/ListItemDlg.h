#if !defined(AFX_LISTITEMDLG_H__C0184697_9CB5_4F9C_8157_094B9B7DDB47__INCLUDED_)
#define AFX_LISTITEMDLG_H__C0184697_9CB5_4F9C_8157_094B9B7DDB47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DialogItem.h"
#include "..\..\sai_cmd\SAICmd\Software.h"
// ListItemDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListItemDlg dialog

class CListItemDlg : public CDialogItem
{
// Construction
public:
	CListItemDlg(CWnd* pParent = NULL);   // standard constructor

	CSoftware * getSoftware() const { return m_software; }
	void setSoftware(CSoftware * val);

	COLORREF getBackColor() const { return m_backColor; }
	void setBackColor(COLORREF val) { m_backColor = val; }

// Dialog Data
	//{{AFX_DATA(CListItemDlg)
	enum { IDD = IDD_DIALOG_LIST_ITEM };
	CString	m_name;
	CString	m_size;
	CString	m_description;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListItemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListItemDlg)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CSoftware *m_software;

	COLORREF m_backColor;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_LISTITEMDLG_H__C0184697_9CB5_4F9C_8157_094B9B7DDB47__INCLUDED_)
