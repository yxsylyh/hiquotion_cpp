#if !defined(AFX_TRANSLABEL_H__38E8B532_78C5_45F3_81A7_B874ECC2A45B__INCLUDED_)
#define AFX_TRANSLABEL_H__38E8B532_78C5_45F3_81A7_B874ECC2A45B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransLabel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransLabel window

// 这个类没在项目中使用，不知道是否好用

class CTransLabel : public CStatic
{
// Construction
public:
	CTransLabel();

// Attributes
public:

// Operations
public:
	void setText(CString text);

	COLORREF getTextColor() const { return m_textColor; }
	void setTextColor(COLORREF val) { m_textColor = val; }

	COLORREF getBackColor() const { return m_backColor; }
	void setBackColor(COLORREF val) { m_backColor = val; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransLabel)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTransLabel();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTransLabel)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
    COLORREF m_textColor;
    COLORREF m_backColor;

	BOOL m_isBgTransparent;

    CBrush   m_Brush;

	CString m_text;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSLABEL_H__38E8B532_78C5_45F3_81A7_B874ECC2A45B__INCLUDED_)
