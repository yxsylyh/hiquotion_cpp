#if !defined(AFX_IMAGEBUTTON_H__DCD5B90A_72C0_4309_B2A0_0F30691C8863__INCLUDED_)
#define AFX_IMAGEBUTTON_H__DCD5B90A_72C0_4309_B2A0_0F30691C8863__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageButton.h : header file
//

#include <C++\3rdParty\cxImage\include\ximage.h>

/////////////////////////////////////////////////////////////////////////////
// CImageButton window

class CImageButton : public CButton
{
// Construction
public:
	CImageButton();

	BOOL setImage(HRSRC res, UINT imageType=0);
	BOOL setImage(CString imgFile, UINT imageType=0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CImageButton)
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CxImage m_btnImage;

	BOOL m_isMouseDown;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEBUTTON_H__DCD5B90A_72C0_4309_B2A0_0F30691C8863__INCLUDED_)
