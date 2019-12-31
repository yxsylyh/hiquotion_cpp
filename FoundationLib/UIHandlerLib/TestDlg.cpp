// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UIHandlerLib.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog


CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

void CTestDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_designer.leftButtonDoubleClick(nFlags, point);

	CDialog::OnLButtonDblClk(nFlags, point);
}

void CTestDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_designer.leftButtonDown(nFlags, point);

	CDialog::OnLButtonDown(nFlags, point);
}

void CTestDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_designer.leftButtonUp(nFlags, point);

	CDialog::OnLButtonUp(nFlags, point);
}

void CTestDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_designer.mouseMove(nFlags, point);
// 	Invalidate();

	CDialog::OnMouseMove(nFlags, point);
}

BOOL CTestDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	m_designer.mouseWheel(nFlags, zDelta, pt);

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CTestDlg::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_designer.rightButtonDblClick(nFlags, point);

	CDialog::OnRButtonDblClk(nFlags, point);
}

void CTestDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_designer.rightButtonDown(nFlags, point);

	CDialog::OnRButtonDown(nFlags, point);
}

void CTestDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_designer.rightButtonUp(nFlags, point);

	CDialog::OnRButtonUp(nFlags, point);
}

BOOL CTestDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rect;
	GetClientRect(&rect);
	m_rectangle.setRect(0, 0, rect.right, rect.bottom);
	m_rectangle.setBackColor(RGB(70, 63, 252));
	m_rectangle.setUseClip(TRUE);  // 这句现在不好使
	m_designer.setShape(&m_rectangle);
// 	m_designer.setRect(0, 0, 500, 500);
	m_roundRectangle.setRect(-10, 10, 120, 200);
	m_obj.setShape(&m_roundRectangle);
	m_elipse.setRect(5, 15, 260, 30);
	m_subObj.setShape(&m_elipse);
// 	m_rect.setRect(10, 30, 70, 30);
	m_designer.addUIHandler(&m_obj);
// 	m_designer.addFigure(&m_rect);
// 	m_designer.setWndForRefresh(this);
//	m_designer.setEffectedOnChild(TRUE);
//	m_designer.setUseClip(TRUE);
	m_obj.addUIHandler(&m_subObj);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CTestDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE; 
}

void CTestDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	CDC dcMem;
	dcMem.CreateCompatibleDC (&dc);
	
	CRect rect;
	GetClientRect(&rect);
	
	CBitmap MemBitmap;
	MemBitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
// 	dcMem.BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&dc,0,0,SRCCOPY);

	CBrush brush, *oldBrush=NULL;
	brush.CreateSolidBrush(RGB(255,255,255));
	oldBrush=dcMem.SelectObject(&brush);
	
// 	dcMem.
	dcMem.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255,255,255));
	
	CBitmap *OldBitmap = dcMem.SelectObject(&MemBitmap);

	m_designer.draw(&dcMem);

// 	dc.FillRect(&rect, NULL);
	dc.BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);
	
	
	
	dcMem.SelectObject(OldBitmap);
	

	// Do not call CDialog::OnPaint() for painting messages
}

void CTestDlg::OnDoubleBufferedDraw(CDC *pDC)
{
	m_designer.draw(pDC);
}
