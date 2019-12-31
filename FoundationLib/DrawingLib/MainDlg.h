#if !defined(AFX_MAINDLG_H__668AAADE_8610_485F_BDE4_B6A3C1744C55__INCLUDED_)
#define AFX_MAINDLG_H__668AAADE_8610_485F_BDE4_B6A3C1744C55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Line.h"
// #include "FilledArea.h"
#include <C++\FoudationLib\cxImageLib\ximage.h>
#include "Rectangle.h"
#include "RoundRectangle.h"
#include "Elipse.h"
#include "Label.h"
#include "Picture.h"
#include "Polyline.h"
#include "Polygon.h"
#include "Bezier.h"
#include "Arc.h"
#include "Chord.h"
#include "Pie.h"

// MainDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

class CMainDlg : public CDialog
{
// Construction
public:
	CMainDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_DIALOG_MAIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButtonSetting();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CRectangle rectangle;
	CRectangle rectangle2;
	CRoundRectangle roundRect;
	CLine line;
	CElipse elipse;
	CLabel label;
// 	CFilledArea area;
	CPicture picture;
	CPolyline poly;
	CPolygon polygon;
	CBezier bezier;
	CArc arc;
	CChord chord;
	CPie pie;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__668AAADE_8610_485F_BDE4_B6A3C1744C55__INCLUDED_)
