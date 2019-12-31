#if !defined(AFX_TRANSEDIT_H__03E3A0F2_FF15_46ED_8AF8_F71AE12815EC__INCLUDED_)
#define AFX_TRANSEDIT_H__03E3A0F2_FF15_46ED_8AF8_F71AE12815EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransEdit window

class CTransEdit : public CEdit
{
// Construction
public:
	CTransEdit();

// Attributes
public:

// Operations
public:
	COLORREF getBackColor() const { return m_backColor; }
	void setBackColor(COLORREF val) { m_backColor = val; }

	BOOL getTransparent() const { return m_isTransparent; }
	void setTransparent(BOOL val) { m_isTransparent = val; }

	void setText(CString strText);
	void setFontBold(BOOL bBold);
	void setFontName(CString strFont, BYTE byCharSet = ANSI_CHARSET);
	void setFontUnderline(BOOL bSet);
	void setFontItalic(BOOL bSet);
	void setFontSize(int nSize);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTransEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTransEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnChange();
	afx_msg void OnKillfocus();
	afx_msg void OnUpdate();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnFontChange();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void update();
	void ReconstructFont();

private:
	BOOL m_isTransparent;
	COLORREF m_backColor;
	COLORREF m_fontColor;
	CBrush m_brush;
	CFont m_font;
	LOGFONT m_lf;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSEDIT_H__03E3A0F2_FF15_46ED_8AF8_F71AE12815EC__INCLUDED_)
