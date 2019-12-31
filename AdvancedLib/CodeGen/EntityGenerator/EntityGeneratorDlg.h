// EntityGeneratorDlg.h : header file
//

#if !defined(AFX_ENTITYGENERATORDLG_H__C0D446F9_A162_42A1_A35D_347F9F50E4F1__INCLUDED_)
#define AFX_ENTITYGENERATORDLG_H__C0D446F9_A162_42A1_A35D_347F9F50E4F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEntityGeneratorDlg dialog

class CEntityGeneratorDlg : public CDialog
{
// Construction
public:
	CEntityGeneratorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEntityGeneratorDlg)
	enum { IDD = IDD_ENTITYGENERATOR_DIALOG };
	CString	m_className;
	CString	m_classProperty;
	CString	m_filename;
	CString	m_include;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntityGeneratorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEntityGeneratorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonStart();
	afx_msg void OnChangeEditClassName();
	afx_msg void OnButtonClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTITYGENERATORDLG_H__C0D446F9_A162_42A1_A35D_347F9F50E4F1__INCLUDED_)
