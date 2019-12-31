// DelegationCodeGenDlg.h : header file
//

#if !defined(AFX_DELEGATIONCODEGENDLG_H__08AF7546_5AD4_46DE_975F_2F80F668990F__INCLUDED_)
#define AFX_DELEGATIONCODEGENDLG_H__08AF7546_5AD4_46DE_975F_2F80F668990F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDelegationCodeGenDlg dialog

class CDelegationCodeGenDlg : public CDialog
{
// Construction
public:
	CDelegationCodeGenDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDelegationCodeGenDlg)
	enum { IDD = IDD_DELEGATIONCODEGEN_DIALOG };
	CString	m_txtAgent;
	CString	m_txtAgentMethod;
	CString	m_txtDelegator;
	CString	m_txtDelegatorMethod;
	CString	m_txtRegistAgent;
	CString	m_txtPath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDelegationCodeGenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDelegationCodeGenDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DELEGATIONCODEGENDLG_H__08AF7546_5AD4_46DE_975F_2F80F668990F__INCLUDED_)
