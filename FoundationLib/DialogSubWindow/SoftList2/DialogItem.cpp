// DialogItem.cpp : implementation file
//

#include "stdafx.h"
#include "SoftList.h"
#include "DialogItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogItem dialog


//CDialogItem::CDialogItem(CWnd* pParent /*=NULL*/)
CDialogItem::CDialogItem(UINT nIDTemplate, CWnd* pParentWnd /*= NULL*/)
	: CDialog(nIDTemplate, pParentWnd),
	m_backColor(RGB(128, 128, 128)), m_selectedBackColor(RGB(0, 0, 255)),
	m_isSelected(FALSE), m_isBgTransparent(FALSE)
{
	//{{AFX_DATA_INIT(CDialogItem)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogItem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogItem)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogItem, CDialog)
	//{{AFX_MSG_MAP(CDialogItem)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogItem message handlers

HBRUSH CDialogItem::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(m_isSelected)
	{
		if( nCtlColor == CTLCOLOR_BTN || nCtlColor ==  CTLCOLOR_STATIC)
		{
			pDC->SetTextColor(m_selectedForeColor);
			pDC->SetBkMode(TRANSPARENT);
		}
		return m_selectedBackColorBrush;
	}
	else if(m_isBgTransparent)
	{
// 		if(nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_BTN || nCtlColor ==  CTLCOLOR_STATIC)
// 			pDC->SetBkMode(TRANSPARENT);
		return   HBRUSH(GetStockObject(NULL_BRUSH));
	}

	pDC->SetTextColor(m_foreColor);
	return m_backColorBrush;

	// TODO: Return a different brush if the default is not desired
//	return hbr;
}

BOOL CDialogItem::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_isSelected)
		pDC->SetBkColor(m_selectedBackColor);
	else if(m_isBgTransparent)
		return TRUE;
	
	return CDialog::OnEraseBkgnd(pDC);
}

void CDialogItem::setBackColor( COLORREF val )
{
	m_backColor=val;
	m_backColorBrush.CreateSolidBrush(m_backColor);
}

void CDialogItem::setSelectedBackColor( COLORREF val )
{
	m_selectedBackColor = val;
	m_selectedBackColorBrush.CreateSolidBrush(m_selectedBackColor);
}
