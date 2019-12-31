// DelegationCodeGenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DelegationCodeGen.h"
#include "DelegationCodeGenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelegationCodeGenDlg dialog

CDelegationCodeGenDlg::CDelegationCodeGenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDelegationCodeGenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDelegationCodeGenDlg)
	m_txtAgent = _T("");
	m_txtAgentMethod = _T("");
	m_txtDelegator = _T("");
	m_txtDelegatorMethod = _T("");
	m_txtRegistAgent = _T("");
	m_txtPath = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDelegationCodeGenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDelegationCodeGenDlg)
	DDX_Text(pDX, IDC_EDIT_AGENT, m_txtAgent);
	DDX_Text(pDX, IDC_EDIT_AGENT_METHOD, m_txtAgentMethod);
	DDX_Text(pDX, IDC_EDIT_DELEGATOR, m_txtDelegator);
	DDX_Text(pDX, IDC_EDIT_DELEGATOR_METHOD, m_txtDelegatorMethod);
	DDX_Text(pDX, IDC_EDIT_Regist_AGENT, m_txtRegistAgent);
	DDX_Text(pDX, IDC_EDIT_PATH, m_txtPath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDelegationCodeGenDlg, CDialog)
	//{{AFX_MSG_MAP(CDelegationCodeGenDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelegationCodeGenDlg message handlers

BOOL CDelegationCodeGenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_txtDelegator="Delegator";
	m_txtRegistAgent="regist";
	m_txtDelegatorMethod="delegate";
	m_txtAgent="Agent";
	m_txtAgentMethod="agent";
	m_txtPath="C:\\Delegation";
	UpdateData(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDelegationCodeGenDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDelegationCodeGenDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDelegationCodeGenDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDelegationCodeGenDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

// 	m_txtDelegator="Delegator";
// 	m_txtRegistAgent="regist";
// 	m_txtDelegatorMethod="delegate";
// 	m_txtAgent="Agent";
// 	m_txtAgentMethod="agent";
// 	m_txtPath="C:\\Delegation";
	if(m_txtDelegator=="" || m_txtRegistAgent=="" || m_txtDelegatorMethod==""
		|| m_txtAgent=="" || m_txtAgentMethod=="" || m_txtPath=="")
	{
		MessageBox("参数有空值！请检查并重新录入。");
		return;
	}

	// 请保证 m_txtPath 事先存在！！！！！！！
	//if(CFolderOperation::)


	
// 	CDialog::OnOK();
}
