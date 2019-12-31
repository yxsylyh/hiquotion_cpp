// TransLabel.cpp : implementation file
//

#include "stdafx.h"
#include "FVerifyShell.h"
#include "TransLabel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransLabel

CTransLabel::CTransLabel()
{
	m_backColor=RGB(155, 255, 255);
	m_Brush.CreateSolidBrush(m_backColor);
	m_textColor=RGB(255, 0, 0);
	m_isBgTransparent=FALSE;
	m_text="";
}

CTransLabel::~CTransLabel()
{
}

BEGIN_MESSAGE_MAP(CTransLabel, CStatic)
	//{{AFX_MSG_MAP(CTransLabel)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransLabel message handlers

void CTransLabel::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.SetTextColor(m_textColor);

	if(m_isBgTransparent)
	{
		dc.SetBkMode(TRANSPARENT);
	}
	else
	{
		dc.SetBkColor(m_backColor);
		CBrush *oldBrush=dc.SelectObject(&m_Brush);
		CWnd *parent=GetParent();
		if(parent)
		{
			RECT rect;
			GetWindowRect(&rect);
			parent->ScreenToClient(&rect);
// 			dc.FillRect(&rect, &m_Brush);
			dc.Rectangle(&rect);
		}
	}

	// Do not call CStatic::OnPaint() for painting messages
}

HBRUSH CTransLabel::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	pDC->SetTextColor(m_textColor);

	if(m_isBgTransparent)
	{
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)GetStockObject(NULL_BRUSH); 
	}

	m_Brush.DeleteObject();
	m_Brush.CreateSolidBrush(m_backColor);
	pDC->SetBkColor(m_backColor);
	return (HBRUSH)m_Brush;

	// TODO: Return a non-NULL brush if the parent's handler should not be called
// 	return NULL;
}

void CTransLabel::setText(CString text)
{
	if(m_isBgTransparent)
	{
		CWnd *parent=GetParent();
		if(parent)
		{
			RECT rect;
			GetWindowRect(&rect);
			parent->ScreenToClient(&rect);
			parent->RedrawWindow(&rect);
		}
	}

	m_text=text;
	SetWindowText(m_text);
}
