// GridCtrlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GridCtrlDemo.h"
#include "GridCtrlDemoDlg.h"

#include "NewCellTypes/GridURLCell.h"
#include "NewCellTypes/GridCellCombo.h"
#include "NewCellTypes/GridCellCheck.h"
#include "NewCellTypes/GridCellNumeric.h"
#include "NewCellTypes/GridCellDateTime.h"
#include "NewCellTypes/GridCellButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if defined(_WIN32_WCE) && (_WIN32_WCE <= 0x200)
#define MF_DISABLED 0
#define DT_END_ELLIPSIS 0
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg() : CDialog(IDD_ABOUTBOX) {}
};

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDemoDlg dialog

CGridCtrlDemoDlg::CGridCtrlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGridCtrlDemoDlg::IDD, pParent)
{
	m_OldSize = CSize(-1,-1);

	//{{AFX_DATA_INIT(CGridCtrlDemoDlg)
	m_nFixCols = 1;
	m_nFixRows = 1;
	m_nCols = 8;
	m_nRows = 20;
	m_bEditable = FALSE;
	m_bHorzLines = FALSE;
	m_bVertLines = FALSE;
	m_bListMode = TRUE;
	m_bHeaderSort = FALSE;
	m_bSingleSelMode = TRUE;
    m_bSingleColSelMode = TRUE;
	m_bSelectable = FALSE;
	m_bAllowColumnResize = FALSE;
	m_bAllowRowResize = FALSE;
	m_bItalics = FALSE;
	m_btitleTips = FALSE;
	m_bTrackFocus = FALSE;
	m_bFrameFocus = FALSE;
	m_bVirtualMode = TRUE;
	m_bCallback = TRUE;
    m_bVertical = TRUE;
    m_bExpandUseFixed = FALSE;
    m_bRejectEditAttempts = TRUE;
    m_bRejectEditChanges = TRUE;
	m_bRow2Col2Hidden = FALSE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGridCtrlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGridCtrlDemoDlg)
	DDX_Control(pDX, IDC_TRACE, m_TraceWnd);
	DDX_Control(pDX, IDC_SPIN_ROW, m_RowSpin);
	DDX_Control(pDX, IDC_SPIN_FIXROW, m_FixRowSpin);
	DDX_Control(pDX, IDC_SPIN_FIXCOL, m_FixColSpin);
	DDX_Control(pDX, IDC_SPIN_COL, m_ColSpin);
	DDX_Text(pDX, IDC_EDIT_FIXCOLS, m_nFixCols);
	DDX_Text(pDX, IDC_EDIT_FIXROWS, m_nFixRows);
	DDX_Text(pDX, IDC_EDIT_COLS, m_nCols);
	DDX_Text(pDX, IDC_EDIT_ROWS, m_nRows);
	DDX_Control(pDX, IDC_GRID, m_Grid);             // associate the grid window with a C++ object
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGridCtrlDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CGridCtrlDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_EN_UPDATE(IDC_EDIT_COLS, OnUpdateEditCols)
	ON_EN_UPDATE(IDC_EDIT_FIXCOLS, OnUpdateEditFixcols)
	ON_EN_UPDATE(IDC_EDIT_FIXROWS, OnUpdateEditFixrows)
	ON_EN_UPDATE(IDC_EDIT_ROWS, OnUpdateEditRows)
	ON_COMMAND(IDC_HORZ_LINES, OnHorzGridLines)
	ON_COMMAND(IDC_VERT_LINES, OnVertGridLines)
	ON_COMMAND(IDC_LISTMODE, OnListmode)
	ON_COMMAND(IDC_EDITABLE, OnEditable)
	ON_COMMAND(IDC_PRINT_BUTTON, OnPrintButton)
	ON_COMMAND(IDC_ALLOW_SELECTION, OnAllowSelection)
	ON_COMMAND(IDC_ROW_RESIZE, OnRowResize)
	ON_COMMAND(IDC_COL_RESIZE, OnColResize)
	ON_COMMAND(IDC_FONT_BUTTON, OnFontButton)
	ON_WM_SIZE()
	ON_COMMAND(IDC_HEADERSORT, OnHeaderSort)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(IDC_ITALICS, OnItalics)
	ON_COMMAND(IDC_TITLETIPS, OnTitletips)
	ON_COMMAND(IDC_INSERT_ROW, OnInsertRow)
	ON_COMMAND(IDC_DELETE_ROW, OnDeleteRow)
	ON_COMMAND(IDC_SINGLESELMODE, OnSingleselmode)
    ON_COMMAND(IDC_SINGLECOLSELMODE, OnSingleColMode)
	ON_COMMAND(IDC_EXPAND_TO_FIT, OnExpandToFit)
	ON_COMMAND(IDC_AUTO_SIZE, OnAutoSize)
	ON_COMMAND(IDC_FILL, OnFill)
	ON_BN_CLICKED(IDC_CELL_URL, OnCellUrl)
	ON_BN_CLICKED(IDC_CELL_NORMAL, OnCellNormal)
	ON_BN_CLICKED(IDC_CELL_COMBO, OnCellCombo)
	ON_BN_CLICKED(IDC_CELL_NUMERIC, OnCellNumeric)
	ON_BN_CLICKED(IDC_CELL_READONLY, OnCellReadonly)
	ON_BN_CLICKED(IDC_CELL_CHECK, OnCellCheckbox)
	ON_BN_CLICKED(IDC_CELL_DATETIME, OnCellDateTime)
	ON_COMMAND(IDC_TRACKFOCUS, OnTrackfocus)
	ON_COMMAND(IDC_FRAMEFOCUS, OnFramefocus)
	ON_COMMAND(IDC_EXPAND_LAST, OnExpandLast)
	ON_COMMAND(IDC_SET_FOCUS, OnSetFocus11)
	ON_COMMAND(IDC_VIRTUAL_MODE, OnVirtualMode)
	ON_COMMAND(IDC_CALLBACK_FUNCTION, OnCallbackFunction)
	ON_COMMAND(IDC_FIXEDROW_SELECTION, OnFixedRowSelection)
	ON_COMMAND(IDC_FIXEDCOL_SELECTION, OnFixedColSelection)
    ON_COMMAND(IDC_VERTICAL_TEXT, OnVertical)
    ON_COMMAND(IDC_EXPAND_USE_FIXED, OnExpandUseFixed)
    ON_COMMAND(IDC_EDITING_REJECT_ATTEMPT, OnRejectEditAttempts)
    ON_COMMAND(IDC_EDITING_REJECT_CHANGE, OnRejectEditChanges)
	ON_BN_CLICKED(IDC_CLEARTRACE, OnCleartrace)
	ON_COMMAND(ID_HIDE2NDROWCOLUMN, OnHide2ndrowcolumn)
	ON_BN_CLICKED(IDC_RADIO_BUTTON, OnRadioButton)
	//}}AFX_MSG_MAP
#ifndef _WIN32_WCE
	ON_WM_CONTEXTMENU()
#endif
    ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
    ON_NOTIFY(NM_CLICK, IDC_GRID, OnGridClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnGridRClick)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_NOTIFY(GVN_SELCHANGING, IDC_GRID, OnGridStartSelChange)
	ON_NOTIFY(GVN_SELCHANGED, IDC_GRID, OnGridEndSelChange)
	ON_NOTIFY(GVN_BEGINDRAG, IDC_GRID, OnGridBeginDrag)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnGridRClick)
	
#ifndef GRIDCONTROL_NO_CLIPBOARD
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopyOrCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopyOrCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridCtrlDemoDlg message handlers

BOOL CGridCtrlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

#ifndef _WIN32_WCE
	CMenu* pSysMenu = GetSystemMenu(FALSE);

    if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
#else - pulled this since it was causing some probs in CE 3.0 (Bjoern Ruff)
//    CSize ScreenSize;
//    ::SetWindowPos(m_hWnd, HWND_TOP,0,0, 
//                 GetSystemMetrics(SM_CXSCREEN), 
//                 GetSystemMetrics(SM_CYSCREEN) - 32, // 32 = kludge value
//                 SWP_SHOWWINDOW);
#endif

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect rect;
	GetClientRect(rect);
	m_OldSize = CSize(rect.Width(), rect.Height());

	// init spin controls
	m_RowSpin.SetRange(0,999);
	m_FixRowSpin.SetRange(0,999);
	m_FixColSpin.SetRange(0,999);
	m_ColSpin.SetRange(0,999);


	/////////////////////////////////////////////////////////////////////////
	// initialise grid properties
	/////////////////////////////////////////////////////////////////////////

	m_ImageList.Create(MAKEINTRESOURCE(IDB_IMAGES), 16, 1, RGB(255,255,255));
	m_Grid.SetImageList(&m_ImageList);

	m_Grid.EnableDragAndDrop(TRUE);
	m_Grid.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));

    OnEditable();
    OnVirtualMode();    // Sets the grid mode, fills the grid
	OnListmode();
    OnCellReadonly();
    OnItalics();
    OnTitletips();
    OnTrackfocus();
    OnFramefocus();
    OnRowResize();
    OnColResize();
    OnSingleselmode();
    OnSingleColMode();
    OnVertGridLines();
    OnHorzGridLines();
    OnAllowSelection();
    OnCallbackFunction();
    OnVertical();
    OnHeaderSort();
    OnExpandUseFixed();
	OnRejectEditAttempts();
	OnRejectEditChanges();

    m_Grid.SetFixedColumnSelection(TRUE);
    m_Grid.SetFixedRowSelection(TRUE);
	m_Grid.EnableColumnHide();

    UpdateMenuUI();

    m_Grid.AutoSize();

	m_Grid.SetCompareFunction(CGridCtrl::pfnCellNumericCompare);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGridCtrlDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

HCURSOR CGridCtrlDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGridCtrlDemoDlg::OnUpdateEditCols() 
{
	if (!::IsWindow(m_Grid.m_hWnd)) return;
	UpdateData();

    int nOldNumCols = m_Grid.GetColumnCount();

	TRY { 
        m_Grid.SetColumnCount(m_nCols); 
    }
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
    END_CATCH

	m_nCols = m_Grid.GetColumnCount();
	m_nFixCols = m_Grid.GetFixedColumnCount();
	UpdateData(FALSE);

    CString str;
    for (int i = nOldNumCols; i < m_nCols; i++)
    {
        str.Format(_T("Column %d"), i);
        m_Grid.SetItemText(0,i,str);
    }
}

void CGridCtrlDemoDlg::OnUpdateEditFixcols() 
{
	if (!::IsWindow(m_Grid.m_hWnd)) return;
	UpdateData();

	TRY {
        m_Grid.SetFixedColumnCount(m_nFixCols); 
    }
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
    END_CATCH

	m_nCols = m_Grid.GetColumnCount();
	m_nFixCols = m_Grid.GetFixedColumnCount();
	UpdateData(FALSE);
}

void CGridCtrlDemoDlg::OnUpdateEditFixrows() 
{
	if (!::IsWindow(m_Grid.m_hWnd)) return;
	UpdateData();

	TRY {
        m_Grid.SetFixedRowCount(m_nFixRows); 
    }
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
    END_CATCH

	m_nRows = m_Grid.GetRowCount();
	m_nFixRows = m_Grid.GetFixedRowCount();
	UpdateData(FALSE);
}

void CGridCtrlDemoDlg::OnUpdateEditRows() 
{	
	if (!::IsWindow(m_Grid.m_hWnd)) return;
	UpdateData();

    int nOldNumRows = m_Grid.GetRowCount();

	TRY {
        m_Grid.SetRowCount(m_nRows); 
    }
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
    END_CATCH

	m_nRows = m_Grid.GetRowCount();
	m_nFixRows = m_Grid.GetFixedRowCount();
	UpdateData(FALSE);

    CString str;
    for (int i = nOldNumRows; i < m_nRows; i++)
    {
        str.Format(_T("Row %d"), i);
        m_Grid.SetItemText(i,0,str);
    }

	//m_Grid.EnsureVisible(m_nRows-1,0);
}

void CGridCtrlDemoDlg::OnGridLines() 
{
	if (!m_bHorzLines && !m_bVertLines)
		m_Grid.SetGridLines(GVL_NONE);
	else if (m_bHorzLines && !m_bVertLines)
		m_Grid.SetGridLines(GVL_HORZ);
	else if (!m_bHorzLines && m_bVertLines)
		m_Grid.SetGridLines(GVL_VERT);
	else 
		m_Grid.SetGridLines(GVL_BOTH);

    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnVertGridLines() 
{
    m_bVertLines = !m_bVertLines;
    OnGridLines();
}

void CGridCtrlDemoDlg::OnHorzGridLines() 
{
    m_bHorzLines = !m_bHorzLines;
    OnGridLines();
}

void CGridCtrlDemoDlg::OnListmode() 
{
    m_bListMode = !m_bListMode;
	m_Grid.SetListMode(m_bListMode);
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnHeaderSort() 
{
	m_bHeaderSort = !m_bHeaderSort;
	m_Grid.SetHeaderSort(m_bHeaderSort);
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnSingleselmode() 
{
	m_bSingleSelMode = !m_bSingleSelMode;
	m_Grid.SetSingleRowSelection(m_bSingleSelMode);
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnSingleColMode() 
{
	m_bSingleColSelMode = !m_bSingleColSelMode;
	m_Grid.SetSingleColSelection(m_bSingleColSelMode);
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnEditable() 
{
	m_bEditable = !m_bEditable;
	m_Grid.SetEditable(m_bEditable);
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnAllowSelection() 
{
	m_bSelectable = !m_bSelectable;
	m_Grid.EnableSelection(m_bSelectable);
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnRowResize() 
{
	m_bAllowRowResize = !m_bAllowRowResize;
	m_Grid.SetRowResize(m_bAllowRowResize);
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnColResize() 
{
	m_bAllowColumnResize = !m_bAllowColumnResize;
	m_Grid.SetColumnResize(m_bAllowColumnResize);
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnPrintButton() 
{
#if !defined(WCE_NO_PRINTING) && !defined(GRIDCONTROL_NO_PRINTING)
	m_Grid.Print();
#endif
}

void CGridCtrlDemoDlg::OnFontButton() 
{
#ifndef _WIN32_WCE
	LOGFONT lf;
	m_Grid.GetFont()->GetLogFont(&lf);

	CFontDialog dlg(&lf);
	if (dlg.DoModal() == IDOK) {
		dlg.GetCurrentFont(&lf);

		CFont Font;
		Font.CreateFontIndirect(&lf);
		m_Grid.SetFont(&Font);
        OnItalics();	
		m_Grid.AutoSize();
		Font.DeleteObject();	
	}
#endif
}

BOOL CALLBACK EnumProc(HWND hwnd, LPARAM lParam)
{
	CWnd* pWnd = CWnd::FromHandle(hwnd);
	CSize* pTranslate = (CSize*) lParam;

	CGridCtrlDemoDlg* pDlg = (CGridCtrlDemoDlg*) pWnd->GetParent();
	if (!pDlg) return FALSE;

	CRect rect;
	pWnd->GetWindowRect(rect);
	//if (hwnd == pDlg->m_Grid.GetSafeHwnd())
	//	TRACE(_T("Wnd rect: %d,%d - %d,%d\n"),rect.left,rect.top, rect.right, rect.bottom);

	pDlg->ScreenToClient(rect);
	//if (hwnd == pDlg->m_Grid.GetSafeHwnd())
	//	TRACE(_T("Scr rect: %d,%d - %d,%d\n"),rect.left,rect.top, rect.right, rect.bottom);

	if (hwnd == pDlg->m_Grid.GetSafeHwnd())
	{
		if (  ((rect.top >= 7 && pTranslate->cy > 0) || rect.Height() > 20) &&
			  ((rect.left >= 7 && pTranslate->cx > 0) || rect.Width() > 20)   )
			pWnd->MoveWindow(rect.left, rect.top, 
							 rect.Width()+pTranslate->cx, 
							 rect.Height()+pTranslate->cy, FALSE);
		else
			pWnd->MoveWindow(rect.left+pTranslate->cx, rect.top+pTranslate->cy, 
							 rect.Width(), rect.Height(), FALSE);
	}
	else if (hwnd == pDlg->m_TraceWnd.GetSafeHwnd())
	{
		if (  ((rect.top >= 7 && pTranslate->cy > 0) || rect.Height() > 20) &&
			  ((rect.left >= 7 && pTranslate->cx > 0) || rect.Width() > 20)   )
			pWnd->MoveWindow(rect.left, rect.top+pTranslate->cy, 
							 rect.Width()+pTranslate->cx, 
							 rect.Height(), FALSE);
		else
			pWnd->MoveWindow(rect.left+pTranslate->cx, rect.top+pTranslate->cy, 
							 rect.Width(), rect.Height(), FALSE);
	}
	else 
	{
        if (pWnd->GetDlgCtrlID() == IDC_SIZEBOX)
       		pWnd->MoveWindow(rect.left+pTranslate->cx, rect.top+pTranslate->cy, 
           					 rect.Width(), rect.Height(), FALSE);
        else
   		    pWnd->MoveWindow(rect.left+pTranslate->cx, rect.top, rect.Width(), rect.Height(), FALSE);
	}
	pDlg->Invalidate();

	return TRUE;
}

void CGridCtrlDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (cx <= 1 || cy <= 1 ) 
        return;

#ifdef _WIN32_WCE
    m_Grid.MoveWindow(0,0, cx,cy, FALSE);
#else
	CSize Translate(cx - m_OldSize.cx, cy - m_OldSize.cy);
	::EnumChildWindows(GetSafeHwnd(), EnumProc, (LPARAM)&Translate);
	m_OldSize = CSize(cx,cy);
#endif

	CWnd *pWnd = GetDlgItem(IDC_SIZEBOX);
	if (pWnd)
		pWnd->ShowWindow( (nType == SIZE_MAXIMIZED)? SW_HIDE : SW_SHOW);
}

#ifndef GRIDCONTROL_NO_CLIPBOARD
void CGridCtrlDemoDlg::OnEditCopy() 
{
	m_Grid.OnEditCopy();	
}

void CGridCtrlDemoDlg::OnEditCut() 
{
	m_Grid.OnEditCut();	
}

void CGridCtrlDemoDlg::OnEditPaste() 
{
	m_Grid.OnEditPaste();	
}

void CGridCtrlDemoDlg::OnUpdateEditCopyOrCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Grid.GetSelectedCount() > 0);
}

void CGridCtrlDemoDlg::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
    // Attach a COleDataObject to the clipboard see if there is any data
    COleDataObject obj;
    pCmdUI->Enable(obj.AttachClipboard() && obj.IsDataAvailable(CF_TEXT)); 
}
#endif

void CGridCtrlDemoDlg::OnEditSelectall() 
{
	m_Grid.OnEditSelectAll();
}

void CGridCtrlDemoDlg::OnAppAbout() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CGridCtrlDemoDlg::OnItalics() 
{
    m_bItalics = !m_bItalics;

    CFont *pFont = m_Grid.GetFont();
	if (!pFont) 
        return;

	LOGFONT lf;
    pFont->GetLogFont(&lf);
	lf.lfItalic = (BYTE) m_bItalics;

    m_Grid.GetDefaultCell(TRUE, FALSE)->SetFont(&lf);
    m_Grid.GetDefaultCell(FALSE, TRUE)->SetFont(&lf);
    m_Grid.GetDefaultCell(TRUE, TRUE)->SetFont(&lf);

	m_Grid.Invalidate();
    m_Grid.AutoSizeColumns(GVS_HEADER);

    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnTitletips() 
{
    m_btitleTips = !m_btitleTips;
    m_Grid.EnableTitleTips(m_btitleTips);
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnInsertRow() 
{
	int nRow = m_Grid.GetFocusCell().row;
    if (nRow >= 0)
    {
	    m_Grid.InsertRow(_T("Newest Row"), nRow);	
	    m_Grid.Invalidate();
    }
}

void CGridCtrlDemoDlg::OnDeleteRow() 
{
	int nRow = m_Grid.GetFocusCell().row;
    if (nRow >= 0)
    {
	    m_Grid.DeleteRow(nRow);	
	    m_Grid.Invalidate();
    }
}

// (Thanks to Koay Kah Hoe for this)
BOOL CGridCtrlDemoDlg::PreTranslateMessage(MSG* pMsg) 
{
    if( pMsg->message == WM_KEYDOWN )
    {
        if(pMsg->wParam == VK_RETURN
            || pMsg->wParam == VK_ESCAPE )
        {
            ::TranslateMessage(pMsg);
            ::DispatchMessage(pMsg);
            return TRUE;                    // DO NOT process further
        }
    }
    return CDialog::PreTranslateMessage(pMsg);
}	

// NM_RCLICK
void CGridCtrlDemoDlg::OnGridRClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Right button click on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}

// GVN_BEGINLABELEDIT
void CGridCtrlDemoDlg::OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Start Edit on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	*pResult = (m_bRejectEditAttempts)? -1 : 0;
}

// GVN_ENDLABELEDIT
void CGridCtrlDemoDlg::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("End Edit on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	*pResult = (m_bRejectEditChanges)? -1 : 0;
}

// GVN_SELCHANGING
void CGridCtrlDemoDlg::OnGridStartSelChange(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Start Selection Change on row %d, col %d (%d Selected)\n"), 
		pItem->iRow, pItem->iColumn, m_Grid.GetSelectedCount());
}

// GVN_SELCHANGED
void CGridCtrlDemoDlg::OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("End Selection Change on row %d, col %d (%d Selected)\n"), 
		pItem->iRow, pItem->iColumn, m_Grid.GetSelectedCount());
}

// GVN_BEGINDRAG
void CGridCtrlDemoDlg::OnGridBeginDrag(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Begin Drag row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}

void CGridCtrlDemoDlg::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}

void CGridCtrlDemoDlg::OnGridClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}

void CGridCtrlDemoDlg::OnExpandToFit() 
{
    m_Grid.ExpandToFit(m_bExpandUseFixed);
}

void CGridCtrlDemoDlg::OnAutoSize() 
{
    m_Grid.AutoSize();
}

void CGridCtrlDemoDlg::OnFill() 
{
    m_Grid.DeleteAllItems();
    m_Grid.AutoFill();
}

void CGridCtrlDemoDlg::OnCellNormal() 
{
    m_Grid.SetCellType(1,1, RUNTIME_CLASS(CGridCell));
    m_Grid.SetItemText(1,1, _T("1"));
    m_Grid.SetItemState(1,1, m_Grid.GetItemState(1,1) & ~GVIS_READONLY);
    m_Grid.Invalidate();
}

void CGridCtrlDemoDlg::OnCellReadonly() 
{
    OnCellNormal();

    m_Grid.SetItemState(1,1, m_Grid.GetItemState(1,1) | GVIS_READONLY);
}

void CGridCtrlDemoDlg::OnCellCheckbox()
{
    OnCellNormal();

	m_Grid.SetCellType(1,1, RUNTIME_CLASS(CGridCellCheck));
}

void CGridCtrlDemoDlg::OnCellDateTime()
{
    OnCellNormal();

	m_Grid.SetCellType(1,1, RUNTIME_CLASS(CGridCellDateTime));

	CGridCellDateTime* pCell = (CGridCellDateTime*) m_Grid.GetCell(1,1);
	pCell->SetTime(CTime::GetCurrentTime());
	m_Grid.RedrawCell(1,1);

	m_Grid.SetColumnWidth(1,100);
}

void CGridCtrlDemoDlg::OnCellUrl() 
{
    OnCellNormal();

    if (!m_Grid.SetCellType(1,1, RUNTIME_CLASS(CGridURLCell)))
        return;
    m_Grid.SetItemText(1,1, _T("www.codeproject.com"));
}

void CGridCtrlDemoDlg::OnCellCombo() 
{
    OnCellNormal();

    if (!m_Grid.SetCellType(1,1, RUNTIME_CLASS(CGridCellCombo)))
        return;

    m_Grid.SetItemText(1,1, _T("Option 1"));

    CStringArray options;
    options.Add(_T("Option 1"));
    options.Add(_T("Option 2"));
    options.Add(_T("Option 3"));

    CGridCellCombo *pCell = (CGridCellCombo*) m_Grid.GetCell(1,1);
    pCell->SetOptions(options);
    pCell->SetStyle(CBS_DROPDOWN); //CBS_DROPDOWN, CBS_DROPDOWNLIST, CBS_SIMPLE
}

void CGridCtrlDemoDlg::OnCellNumeric() 
{
    OnCellNormal();

    if (!m_Grid.SetCellType(1,1, RUNTIME_CLASS(CGridCellNumeric)))
        return;

    m_Grid.SetItemText(1,1, _T("12345"));
}


void CGridCtrlDemoDlg::OnTrackfocus() 
{
    m_bTrackFocus = !m_bTrackFocus;
    m_Grid.SetTrackFocusCell(m_bTrackFocus);
    m_Grid.Invalidate();
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnFramefocus() 
{
    m_bFrameFocus = !m_bFrameFocus;
    m_Grid.SetFrameFocusCell(m_bFrameFocus);
    m_Grid.Invalidate();
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnRejectEditAttempts() 
{
    m_bRejectEditAttempts = !m_bRejectEditAttempts;
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnRejectEditChanges() 
{
    m_bRejectEditChanges = !m_bRejectEditChanges;
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnExpandLast() 
{
    m_Grid.ExpandLastColumn();	
}

void CGridCtrlDemoDlg::OnSetFocus11() 
{
    CCellID cell(1,1);

    m_Grid.SetFocusCell(cell);

    if (m_Grid.GetListMode())
        m_Grid.SetSelectedRange(1, m_Grid.GetFixedColumnCount(), 1, m_Grid.GetColumnCount()-1, TRUE);
    else
        m_Grid.SetSelectedRange(1,1,1,1, TRUE);
}

void CGridCtrlDemoDlg::OnCallbackFunction() 
{
    m_bCallback = !m_bCallback;
    m_Grid.SetCallbackFunc(m_bCallback? GridCallback : NULL, 0);
	m_Grid.AllowReorderColumn(m_bCallback!=0); // implemented now only if m_bCallback
	m_Grid.EnableDragRowMode(m_bCallback!=0);
    m_Grid.Refresh();
    UpdateMenuUI();
}

bool CGridCtrlDemoDlg::VirtualCompare(int c1, int c2)
{
	//CGridCtrl *pThis = CGridCtrl::m_This; // Mmm, in big virtual mode you must well optimize this function
	//int col = pThis->m_CurCol;            // a first version with CStrings was catastrophic....
	return (c1<c2); // strange order, whatever the column number...
}

void CGridCtrlDemoDlg::OnVirtualMode() 
{
    UpdateData();

    m_bVirtualMode = !m_bVirtualMode;
	m_Grid.SetVirtualMode(m_bVirtualMode);
    m_Grid.SetEditable(m_bEditable);

    m_bHeaderSort = m_Grid.GetHeaderSort();

    if (m_bVirtualMode)
    {
        m_bEditable = m_Grid.IsEditable();
        m_Grid.SetCallbackFunc(m_bCallback? GridCallback : NULL, 0);

        m_nFixCols = 1;
	    m_nFixRows = 1;
	    m_nCols = 100;
	    m_nRows = 100000;

	    TRY {
		    m_Grid.SetRowCount(m_nRows);
		    m_Grid.SetColumnCount(m_nCols);
		    m_Grid.SetFixedRowCount(m_nFixRows);
		    m_Grid.SetFixedColumnCount(m_nFixCols);
			m_Grid.AllowReorderColumn(m_bCallback!=0); // implemented now only if m_bCallback
			m_Grid.EnableDragRowMode(m_bCallback!=0);
			m_Grid.SetVirtualCompare(VirtualCompare);
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH
    }
    else
    {
        m_nFixCols = 1;
	    m_nFixRows = 1;
	    m_nCols = 6;
	    m_nRows = 16;

        m_Grid.SetAutoSizeStyle();

	    TRY {
		    m_Grid.SetRowCount(m_nRows);
		    m_Grid.SetColumnCount(m_nCols);
		    m_Grid.SetFixedRowCount(m_nFixRows);
		    m_Grid.SetFixedColumnCount(m_nFixCols);
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

	    // fill rows/cols with text
	    for (int row = 0; row < m_Grid.GetRowCount(); row++)
        {
	    	for (int col = 0; col < m_Grid.GetColumnCount(); col++)
		    { 
                CString str;

			    GV_ITEM Item;

    			Item.mask = GVIF_TEXT;
	    		Item.row = row;
		    	Item.col = col;

			    if (row < m_nFixRows)
                    str.Format(_T("Column %d"),col);
                else if (col < m_nFixCols) 
                    str.Format(_T("Row %d"), row);
                else 
				    str.Format(_T("%d"),row*col);
                Item.strText = str;

    			if (rand() % 10 == 1)
	    		{
                    COLORREF clr = RGB(rand()%128 + 128, rand()%128 + 128, rand()%128 + 128);
                    Item.crBkClr = clr;             // or - m_Grid.SetItemBkColour(row, col, clr);
                    Item.crFgClr = RGB(255,0,0);    // or - m_Grid.SetItemFgColour(row, col, RGB(255,0,0));				    
                    Item.mask    |= (GVIF_BKCLR|GVIF_FGCLR);
    			}

    			if (col < m_Grid.GetFixedColumnCount())
                {
                    Item.iImage = rand()%m_ImageList.GetImageCount();
                    Item.mask  |= (GVIF_IMAGE);
                }

        		m_Grid.SetItem(&Item);
	    	}
        }
    }

    //m_Grid.GetDefaultCell(FALSE,FALSE)->SetFormat(DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX|DT_END_ELLIPSIS);
    //m_Grid.GetDefaultCell(TRUE, FALSE)->SetFormat(DT_RIGHT|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX|DT_END_ELLIPSIS);

    // Having weird Autosize problems with CE 2.11 - possibly just an emulation problem
#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
	m_Grid.AutoSize();
#endif

    UpdateMenuUI();

    UpdateData(FALSE);
}

BOOL CGridCtrlDemoDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
    if (wParam == (WPARAM)m_Grid.GetDlgCtrlID())
    {
        *pResult = 1;
        GV_DISPINFO *pDispInfo = (GV_DISPINFO*)lParam;
        if (GVN_GETDISPINFO == pDispInfo->hdr.code)
        {
            //TRACE2("Getting Display info for cell %d,%d\n", pDispInfo->item.row, pDispInfo->item.col);
            pDispInfo->item.strText.Format(_T("Message %d,%d"),pDispInfo->item.row, pDispInfo->item.col);
            return TRUE;
        }
        else if (GVN_ODCACHEHINT == pDispInfo->hdr.code)
        {
            GV_CACHEHINT *pCacheHint = (GV_CACHEHINT*)pDispInfo;
            Trace(_T("Cache hint received for cell range %d,%d - %d,%d\n"),
                  pCacheHint->range.GetMinRow(), pCacheHint->range.GetMinCol(),
                  pCacheHint->range.GetMaxRow(), pCacheHint->range.GetMaxCol());
        }
    }
    
	return CDialog::OnNotify(wParam, lParam, pResult);
}

BOOL CALLBACK CGridCtrlDemoDlg::GridCallback(GV_DISPINFO *pDispInfo, LPARAM /*lParam*/) 
{
    pDispInfo->item.strText.Format(_T("Callback %d,%d"),pDispInfo->item.row, pDispInfo->item.col);
    return TRUE;
}

void CGridCtrlDemoDlg::UpdateMenuUI()
{
#ifndef _WIN32_WCE
    BOOL bHorzLines = m_Grid.GetGridLines() & GVL_HORZ;
    BOOL bVertLines = m_Grid.GetGridLines() & GVL_VERT;
    GetMenu()->CheckMenuItem(IDC_HORZ_LINES, MF_BYCOMMAND | (bHorzLines)? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_LISTMODE, MF_BYCOMMAND | (m_Grid.GetListMode())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_VERT_LINES, MF_BYCOMMAND | (bVertLines)? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->EnableMenuItem(IDC_SINGLESELMODE, MF_BYCOMMAND | (m_Grid.GetListMode())? MF_ENABLED: MF_DISABLED|MF_GRAYED);
    GetMenu()->CheckMenuItem(IDC_HEADERSORT, MF_BYCOMMAND | (m_Grid.GetHeaderSort())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_SINGLESELMODE, MF_BYCOMMAND | (m_Grid.GetSingleRowSelection())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_SINGLECOLSELMODE, MF_BYCOMMAND | (m_Grid.GetSingleColSelection())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_EDITABLE, MF_BYCOMMAND | (m_Grid.IsEditable())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_ALLOW_SELECTION, MF_BYCOMMAND | (m_Grid.IsSelectable())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_ROW_RESIZE, MF_BYCOMMAND | (m_Grid.GetRowResize())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_COL_RESIZE, MF_BYCOMMAND | (m_Grid.GetColumnResize())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_ITALICS, MF_BYCOMMAND | (m_bItalics)? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_TITLETIPS, MF_BYCOMMAND | (m_Grid.GetTitleTips())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_TRACKFOCUS, MF_BYCOMMAND | (m_Grid.GetTrackFocusCell())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_FRAMEFOCUS, MF_BYCOMMAND | (m_Grid.GetFrameFocusCell())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_CALLBACK_FUNCTION, MF_BYCOMMAND | (m_Grid.GetCallbackFunc()!=NULL)? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_VIRTUAL_MODE, MF_BYCOMMAND | (m_Grid.GetVirtualMode())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->EnableMenuItem(IDC_CALLBACK_FUNCTION, MF_BYCOMMAND | (m_Grid.GetVirtualMode())? MF_ENABLED: MF_DISABLED|MF_GRAYED);
    GetMenu()->CheckMenuItem(IDC_FIXEDROW_SELECTION, MF_BYCOMMAND | (m_Grid.GetFixedRowSelection())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_FIXEDCOL_SELECTION, MF_BYCOMMAND | (m_Grid.GetFixedColumnSelection())? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_VERTICAL_TEXT, MF_BYCOMMAND | (m_bVertical)? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_EXPAND_USE_FIXED, MF_BYCOMMAND | (m_bExpandUseFixed)? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_EDITING_REJECT_ATTEMPT, MF_BYCOMMAND | (m_bRejectEditAttempts)? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(IDC_EDITING_REJECT_CHANGE, MF_BYCOMMAND | (m_bRejectEditChanges)? MF_CHECKED: MF_UNCHECKED);
    GetMenu()->CheckMenuItem(ID_HIDE2NDROWCOLUMN, MF_BYCOMMAND | (m_bRow2Col2Hidden)? MF_CHECKED: MF_UNCHECKED);
#endif
}

void CGridCtrlDemoDlg::OnFixedRowSelection() 
{
    m_Grid.SetFixedRowSelection(!m_Grid.GetFixedRowSelection());
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnFixedColSelection() 
{
    m_Grid.SetFixedColumnSelection(!m_Grid.GetFixedColumnSelection());
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnExpandUseFixed() 
{
    m_bExpandUseFixed = !m_bExpandUseFixed;
    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnVertical() 
{
    m_bVertical = !m_bVertical;

    // Set reasonable format
    //m_Grid.GetDefaultCell(TRUE, FALSE)->SetFormat(DT_SINGLELINE|DT_NOPREFIX|DT_END_ELLIPSIS|DT_LEFT|DT_BOTTOM);
    //m_Grid.GetDefaultCell(TRUE, TRUE)->SetFormat(DT_SINGLELINE|DT_NOPREFIX|DT_END_ELLIPSIS|DT_LEFT|DT_BOTTOM);

    // Get the font
    CFont* pFont = m_Grid.GetFont();
	LOGFONT lf;
    pFont->GetLogFont(&lf);
    
    // Make it true-type
    memcpy(lf.lfFaceName, _T("Arial"), 6);

    // Vertical or horizontal
    if (m_bVertical)
    {
        lf.lfEscapement = 900;
        lf.lfOrientation = 900;
    }
    else
    {
        lf.lfEscapement = 0;
        lf.lfOrientation = 0;
    }

    // Set the fixed row defaults as this new font
    m_Grid.GetDefaultCell(TRUE, FALSE)->SetFont(&lf);

    // Set cell 1,1 as the more normal font so URL cells look OK
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    m_Grid.SetItemFont(0,1, &lf);


    m_Grid.AutoSize(GVS_HEADER);
    if (m_btitleTips)
    {
        m_btitleTips = !m_bVertical;
        m_Grid.EnableTitleTips(!m_bVertical);
    }

    UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (pWnd->GetSafeHwnd() == m_Grid.GetSafeHwnd())
	{
		m_Grid.ScreenToClient(&point);
		CCellID cell = m_Grid.GetCellFromPt(point);
		Trace(_T("Context menu called on row %d, col %d\n"), cell.row, cell.col);
	}
}

void CGridCtrlDemoDlg::Trace(LPCTSTR szFmt, ...)
{    
	CString str;

	// Format the message text
    va_list argptr;
    va_start(argptr, szFmt);
    str.FormatV(szFmt, argptr);
    va_end(argptr);

	str.Replace(_T("\n"), _T("\r\n"));

	CString strWndText;
	m_TraceWnd.GetWindowText(strWndText);
	strWndText += str;
	m_TraceWnd.SetWindowText(strWndText);

//	m_TraceWnd.SetSel(str.GetLength()-1, str.GetLength()-2, FALSE);
	m_TraceWnd.LineScroll(-m_TraceWnd.GetLineCount());
	m_TraceWnd.LineScroll(m_TraceWnd.GetLineCount()-4);
}

void CGridCtrlDemoDlg::OnCleartrace() 
{
	m_TraceWnd.SetWindowText(_T(""));
}

void CGridCtrlDemoDlg::OnHide2ndrowcolumn()
{
	m_bRow2Col2Hidden = !m_bRow2Col2Hidden;

	if (m_bRow2Col2Hidden)
	{
		m_Grid.SetColumnWidth(2,0);
		m_Grid.SetRowHeight(2,0);
	}
	else
	{
		m_Grid.SetColumnWidth(2,1);
		m_Grid.AutoSizeColumn(2);
		m_Grid.SetRowHeight(2,1);
		m_Grid.AutoSizeRow(2);
	}
	m_Grid.Refresh();
	UpdateMenuUI();
}

void CGridCtrlDemoDlg::OnRadioButton() 
{
	// TODO: Add your control notification handler code here
    OnCellNormal();
	
	m_Grid.SetCellType(1,1, RUNTIME_CLASS(CGridCellButton));
}
