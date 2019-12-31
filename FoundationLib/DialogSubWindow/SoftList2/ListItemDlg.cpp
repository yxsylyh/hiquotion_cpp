// ListItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoftList.h"
#include "ListItemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListItemDlg dialog


CListItemDlg::CListItemDlg(CWnd* pParent /*=NULL*/)
	: CDialogItem(CListItemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListItemDlg)
	m_name = _T("");
	m_size = _T("");
	m_description = _T("");
	//}}AFX_DATA_INIT
}


void CListItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListItemDlg)
	DDX_Text(pDX, IDC_STATIC_NAME, m_name);
	DDX_Text(pDX, IDC_STATIC_SIZE, m_size);
	DDX_Text(pDX, IDC_STATIC_DESCRIPTION, m_description);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListItemDlg, CDialog)
	//{{AFX_MSG_MAP(CListItemDlg)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CListItemDlg::setSoftware( CSoftware * val )
{
	if(!val)
		return;

	m_name=val->getName().c_str();
	m_description=val->getDescription().c_str();
	m_size=val->getSize().c_str();
	if(m_size.GetLength()<=0)
		m_size="0KB";
	UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CListItemDlg message handlers

BOOL CListItemDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//	return TRUE;

 	return CDialogItem::OnEraseBkgnd(pDC);
}

HBRUSH CListItemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	return CDialogItem::OnCtlColor(pDC, pWnd, nCtlColor);
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	// TODO: Return a different brush if the default is not desired
//	return hbr;
//	return   HBRUSH(GetStockObject(NULL_BRUSH));

}
