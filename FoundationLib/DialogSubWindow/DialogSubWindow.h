// DialogItem.h: interface for the CDialogItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOGITEM_H__31F4C6EB_F0D2_405A_9644_37E855B136B4__INCLUDED_)
#define AFX_DIALOGITEM_H__31F4C6EB_F0D2_405A_9644_37E855B136B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDialogItem dialog

class CDialogSubWindow : public CDialog
{
// Construction
public:
//	CDialogItem(CWnd* pParent = NULL);   // standard constructor
	CDialogSubWindow(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	
	COLORREF getBackColor() const { return m_backColor; }
	void setBackColor(COLORREF val);

	COLORREF getSelectedBackColor() const { return m_selectedBackColor; }
	void setSelectedBackColor(COLORREF val);

	BOOL isBgTransparent() const { return m_isBgTransparent; }
	void setBgTransparent(BOOL val) { m_isBgTransparent = val; }

	BOOL isSelected() const { return m_isSelected; }
	void setSelected(BOOL val) { m_isSelected = val; }

	COLORREF getForeColor() const { return m_foreColor; }
	void setForeColor(COLORREF val) { m_foreColor = val; }

	COLORREF getSelectedForeColor() const { return m_selectedForeColor; }
	void setSelectedForeColor(COLORREF val) { m_selectedForeColor = val; }

// Dialog Data
	//{{AFX_DATA(CDialogItem)
//	enum { IDD = 0 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogItem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogItem)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
protected:
	COLORREF m_backColor;
	COLORREF m_selectedBackColor;

	CBrush m_backColorBrush;
	CBrush m_selectedBackColorBrush;

	COLORREF m_foreColor;
	COLORREF m_selectedForeColor;
	BOOL m_isBgTransparent;
	BOOL m_isSelected;
};

#endif // !defined(AFX_DIALOGITEM_H__31F4C6EB_F0D2_405A_9644_37E855B136B4__INCLUDED_)
