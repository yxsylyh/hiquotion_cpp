#if !defined(AFX_TESTDLG_H__F354F38D_5759_4C44_B880_19AD681C1169__INCLUDED_)
#define AFX_TESTDLG_H__F354F38D_5759_4C44_B880_19AD681C1169__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IUIHandler.h"
#include "..\DrawingLib\Container.h"
#include "..\DrawingLib\RoundRectangle.h"
#include "..\DrawingLib\Elipse.h"

// TestDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_DIALOG_TEST };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	virtual void OnDoubleBufferedDraw(CDC *pDC);

private:
	CRectangle m_rectangle;
	IUIHandler m_designer;
	CRoundRectangle m_roundRectangle;
	IUIHandler m_obj;
	CElipse m_elipse;
	IUIHandler m_subObj;
	CContainer m_rect;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__F354F38D_5759_4C44_B880_19AD681C1169__INCLUDED_)
