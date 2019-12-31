// TransEdit.cpp : implementation file
//

#include "stdafx.h"
#include "FVerifyShell.h"
#include "TransEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransEdit

CTransEdit::CTransEdit()
{
	m_backColor=RGB(255,255,255);
	m_fontColor=RGB(0,0,0);
	m_isTransparent=FALSE;
}

CTransEdit::~CTransEdit()
{
}


BEGIN_MESSAGE_MAP(CTransEdit, CEdit)
	//{{AFX_MSG_MAP(CTransEdit)
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnKillfocus)
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
	ON_WM_FONTCHANGE()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_CHAR()
	ON_WM_DEADCHAR()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransEdit message handlers

HBRUSH CTransEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	pDC->SetTextColor(m_fontColor);

	if(!m_isTransparent)
	{
		m_brush.DeleteObject();
		m_brush.CreateSolidBrush(m_backColor);
		return HBRUSH(&m_backColor);
	}

	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)GetStockObject(NULL_BRUSH);  

	// TODO: Return a non-NULL brush if the parent's handler should not be called
// 	return NULL;
}

void CTransEdit::update()
{
	CRect rc;
	GetWindowRect(rc);
	
	GetParent()->ScreenToClient(rc);
	GetParent()->RedrawWindow(rc);
}

void CTransEdit::ReconstructFont()
{
	m_font.DeleteObject();
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf);
	
	ASSERT(bCreated);
}

void CTransEdit::OnChange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	update();
}

void CTransEdit::OnKillfocus() 
{
	// TODO: Add your control notification handler code here
	update();
}

void CTransEdit::OnUpdate() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
	update();
}

void CTransEdit::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	update();

	CEdit::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

BOOL CTransEdit::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	update();

	return CEdit::OnEraseBkgnd(pDC);
}

void CTransEdit::OnFontChange() 
{
	CEdit::OnFontChange();
	
	// TODO: Add your message handler code here
	update();
}

void CTransEdit::OnSize(UINT nType, int cx, int cy) 
{
	CEdit::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	update();
}

void CTransEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(nFlags==MK_LBUTTON)
		update();

	CEdit::OnMouseMove(nFlags, point);
}

void CTransEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	update();

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CTransEdit::OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	update();

	CEdit::OnDeadChar(nChar, nRepCnt, nFlags);
}

void CTransEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	update();
}

void CTransEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	update();

	CEdit::OnLButtonUp(nFlags, point);
}

void CTransEdit::setText(CString strText)
{
	if(IsWindow(this->GetSafeHwnd())) 
	{
		SetWindowText(strText);
		update();
	}
}

void CTransEdit::setFontBold(BOOL bBold)
{
	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	ReconstructFont();
	update();

}

void CTransEdit::setFontName(CString strFont, BYTE byCharSet)
{
	m_lf.lfCharSet = byCharSet;
	
	_tcscpy(m_lf.lfFaceName,strFont);
	ReconstructFont();
	update();
}

void CTransEdit::setFontUnderline(BOOL bSet)
{
	m_lf.lfUnderline = bSet;
	ReconstructFont();
	update();
}

void CTransEdit::setFontItalic(BOOL bSet)
{
	m_lf.lfItalic = bSet;
	ReconstructFont();
	update();
}

void CTransEdit::setFontSize(int nSize)
{
	CFont cf;
	LOGFONT lf;
	
	cf.CreatePointFont(nSize * 10, m_lf.lfFaceName);
	cf.GetLogFont(&lf);
	
	m_lf.lfHeight = lf.lfHeight;
	m_lf.lfWidth  = lf.lfWidth;

	update();
}
