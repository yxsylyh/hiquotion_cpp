// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Figure.h"
#include "MainDlg.h"
#include "Line.h"
// #include <C++\3rdParty\GDIPlus\Includes\GdiplusInit.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog


CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent), elipse(15, 20, 135, 624)//, label(75, 70, 40, 36, "1")
	, rectangle(450, 20, 600, 550)
	, rectangle2(20, 20, 200, 500)
	, roundRect(400, 300, 500, 400)
{
	//{{AFX_DATA_INIT(CMainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SETTING, OnButtonSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
// 	Gdiplus::GdiplusStartupInput gdiplusStartupInput; 
// 	ULONG_PTR gdiplusToken; 
// 	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL); 

	POINT p1, p2;
	p1.x=10;p1.y=10;
	p2.x=260;p2.y=270;
	line.setPoints(p1, p2);

	CRect rect;
	rect.left=15;
	rect.top=100;
	rect.right=220;
	rect.bottom=230;
	label.setRect(&rect);
	label.setCaption("看看效果如何afjak;lsdkaj;f");
	label.setFillStyle(BS_SOLID);
	arc.setRect(rect);
	arc.setPoints(p1, p2);

	picture.setRect(150, 200, 300, 350);
	picture.setPath("D:\\Sunset.jpg");

//	picture.addT(&label);
//	picture.setUseClip(TRUE);

// 	CPoint p01(255, 122);
// 	CPoint p02(143, 223);
// 	CPoint p03(243, 323);
// 	CPoint p04(543, 423);
// 	CPoint p05(651, 524);
// 	CPoint p06(336, 501);
// 	CPoint p07(601, 533);
	CPoint p01(10, 255);
	CPoint p02(10, 155);
	CPoint p03(210, 155);
	CPoint p04(210, 255);
	CPoint p05(210, 355);
	CPoint p06(410, 355);
	CPoint p07(410, 255);
	poly.addPoint(p01);
	poly.addPoint(p02);
	poly.addPoint(p03);
	poly.addPoint(p04);
	poly.addPoint(p05);
	poly.addPoint(p06);
	poly.addPoint(p07);
	poly.setLineColor(RGB(255,0,255));

// 	polygon.addPoint(p01);
// 	polygon.addPoint(p02);
// 	polygon.addPoint(p03);
// 	polygon.addPoint(p04);
// 	polygon.addPoint(p05);
// 	polygon.addPoint(p06);
// 	polygon.addPoint(p07);

	POINT ignore;
	ignore.x=0;
	ignore.y=0;
	bezier.addPoint(p01, ignore, p02);
	bezier.addPoint(p04, p03, p05);
	bezier.addPoint(p07, p06, ignore);

	chord.setRect(135, 220, 540, 421);
// 	chord.setPoints(p01, p07);
	chord.setPoints(p07, p01);

	pie.setRect(240, 300, 510, 550);
// 	pie.setPoints(p01, p07);
	pie.setPoints(p07, p01);

 	rectangle.addFigure(&label);
	rectangle.addFigure(&rectangle2);
	rectangle2.addFigure(&label);

	rectangle.setUseClip(TRUE);
	rectangle2.setUseClip(TRUE);

// 	roundRect.addFigure(&elipse);
// 	roundRect.setUseClip(TRUE);
// 
// 	elipse.addFigure(&label);
// 	elipse.setUseClip(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
// 	CRgn rgn;
// 	rgn.CreateRectRgn(10, 10, 100, 100);
// 	dc.SelectClipRgn(&rgn);

	label.draw(&dc);
	line.draw(&dc);
	elipse.draw(&dc);
	picture.draw(&dc);
// 	dc.SelectClipRgn(NULL);

	polygon.draw(&dc);
	poly.draw(&dc);
	bezier.draw(&dc);
	arc.draw(&dc);
	

	chord.draw(&dc);
	pie.draw(&dc);

	rectangle.draw(&dc);

	roundRect.draw(&dc);

// 	area.draw(&dc);
	// Do not call CDialog::OnPaint() for painting messages
}

void CMainDlg::OnButtonSetting() 
{
	// TODO: Add your control notification handler code here
	line.setLineColor(RGB(255, 128, 36));
}
