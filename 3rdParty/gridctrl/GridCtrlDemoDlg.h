// GridCtrlDemoDlg.h : header file
//

#if !defined(AFX_GRIDCTRLDEMODLG_H__34B6D7A6_9CDC_11D1_9C11_00A0243D1382__INCLUDED_)
#define AFX_GRIDCTRLDEMODLG_H__34B6D7A6_9CDC_11D1_9C11_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDemoDlg dialog

#include "GridCtrl_src/GridCtrl.h"

class CGridCtrlDemoDlg : public CDialog
{
// Construction
public:
	CGridCtrlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGridCtrlDemoDlg)
	enum { IDD = IDD_GRIDCTRLDEMO_DIALOG };
	CEdit	m_TraceWnd;
	CButton	m_CallbackButton;
	CSpinButtonCtrl	m_RowSpin;
	CSpinButtonCtrl	m_FixRowSpin;
	CSpinButtonCtrl	m_FixColSpin;
	CSpinButtonCtrl	m_ColSpin;
	CStatic	m_GridRect;
	int		m_nFixCols;
	int		m_nFixRows;
	int		m_nCols;
	int		m_nRows;
	BOOL	m_bEditable;
	BOOL	m_bHorzLines;
	BOOL	m_bListMode;
	BOOL	m_bVertLines;
	BOOL	m_bSelectable;
	BOOL	m_bAllowColumnResize;
	BOOL	m_bAllowRowResize;
	BOOL	m_bHeaderSort;
	BOOL	m_bItalics;
	BOOL	m_btitleTips;
	BOOL	m_bSingleSelMode;
    BOOL    m_bSingleColSelMode;
	BOOL	m_bTrackFocus;
	BOOL	m_bFrameFocus;
	BOOL	m_bVirtualMode;
	BOOL	m_bCallback;
    BOOL    m_bVertical;
    BOOL    m_bExpandUseFixed;
    BOOL    m_bRejectEditAttempts;
    BOOL    m_bRejectEditChanges;
	BOOL    m_bRow2Col2Hidden;
	//}}AFX_DATA
	CGridCtrl m_Grid;
	CSize m_OldSize;
	static bool VirtualCompare(int c1, int c2);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridCtrlDemoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

    static BOOL CALLBACK GridCallback(GV_DISPINFO *pDispInfo, LPARAM lParam);
	void OnGridLines();
    void UpdateMenuUI();
	void Trace(LPCTSTR szFmt, ...);

// Implementation
protected:
	HICON m_hIcon;
	CImageList m_ImageList;

	// Generated message map functions
	//{{AFX_MSG(CGridCtrlDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnUpdateEditCols();
	afx_msg void OnUpdateEditFixcols();
	afx_msg void OnUpdateEditFixrows();
	afx_msg void OnUpdateEditRows();
	afx_msg void OnHorzGridLines();
	afx_msg void OnVertGridLines();
	afx_msg void OnListmode();
	afx_msg void OnEditable();
	afx_msg void OnPrintButton();
	afx_msg void OnAllowSelection();
	afx_msg void OnRowResize();
	afx_msg void OnColResize();
	afx_msg void OnFontButton();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHeaderSort();
	afx_msg void OnEditSelectall();
	afx_msg void OnAppAbout();
	afx_msg void OnItalics();
	afx_msg void OnTitletips();
	afx_msg void OnInsertRow();
	afx_msg void OnDeleteRow();
	afx_msg void OnSingleselmode();
	afx_msg void OnSingleColMode();
	afx_msg void OnExpandToFit();
	afx_msg void OnAutoSize();
	afx_msg void OnFill();
	afx_msg void OnCellUrl();
	afx_msg void OnCellNormal();
	afx_msg void OnCellCombo();
	afx_msg void OnCellNumeric();
	afx_msg void OnCellReadonly();
	afx_msg void OnCellCheckbox();
	afx_msg void OnCellDateTime();
	afx_msg void OnTrackfocus();
	afx_msg void OnFramefocus();
	afx_msg void OnExpandLast();
	afx_msg void OnSetFocus11();
	afx_msg void OnVirtualMode();
	afx_msg void OnCallbackFunction();
	afx_msg void OnFixedRowSelection();
	afx_msg void OnFixedColSelection();
    afx_msg void OnVertical();
    afx_msg void OnExpandUseFixed();
	afx_msg void OnRejectEditAttempts();
	afx_msg void OnRejectEditChanges();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnCleartrace();
	afx_msg void OnRadioButton();
	//}}AFX_MSG
    afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridRClick(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridStartSelChange(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridBeginDrag(NMHDR *pNotifyStruct, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
#ifndef GRIDCONTROL_NO_CLIPBOARD
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCopyOrCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
#endif
public:
	afx_msg void OnHide2ndrowcolumn();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDCTRLDEMODLG_H__34B6D7A6_9CDC_11D1_9C11_00A0243D1382__INCLUDED_)
