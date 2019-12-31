// SoftListDlg.h : header file
//

#if !defined(AFX_SOFTLISTDLG_H__C1F69208_5EBC_4692_9BA0_06A263D40A64__INCLUDED_)
#define AFX_SOFTLISTDLG_H__C1F69208_5EBC_4692_9BA0_06A263D40A64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSoftListDlg dialog

#include "SoftListBox.h"
#include "..\..\sai_cmd\SAICmd\SAIConfig.h"

class CSoftListDlg : public CDialog
{
// Construction
public:
	CSoftListDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSoftListDlg)
	enum { IDD = IDD_SOFTLIST_DIALOG };
	CSoftListBox	m_softListBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoftListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSoftListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CSAIConfig config;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOFTLISTDLG_H__C1F69208_5EBC_4692_9BA0_06A263D40A64__INCLUDED_)
