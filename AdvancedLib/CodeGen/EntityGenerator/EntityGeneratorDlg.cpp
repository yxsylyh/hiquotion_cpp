// EntityGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EntityGenerator.h"
#include "EntityGeneratorDlg.h"
#include "EntityClassGen.h"

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
// CEntityGeneratorDlg dialog

CEntityGeneratorDlg::CEntityGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEntityGeneratorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEntityGeneratorDlg)
	m_className = _T("");
	m_classProperty = _T("");
	m_filename = _T("");
	m_include = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEntityGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntityGeneratorDlg)
	DDX_Text(pDX, IDC_EDIT_CLASS_NAME, m_className);
	DDX_Text(pDX, IDC_EDIT_CLASS_PROPERTY, m_classProperty);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_filename);
	DDX_Text(pDX, IDC_EDIT_INCLUDE, m_include);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEntityGeneratorDlg, CDialog)
	//{{AFX_MSG_MAP(CEntityGeneratorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_EN_CHANGE(IDC_EDIT_CLASS_NAME, OnChangeEditClassName)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntityGeneratorDlg message handlers

BOOL CEntityGeneratorDlg::OnInitDialog()
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
#ifdef _DEBUG
	m_className="CClassPath";
	m_filename="ClassPath";
	m_include="<string>\r\n<vector>";
	m_classProperty="className\r\nclassValue,CString\r\nfoo,float,3\r\nfee,long";
	UpdateData(FALSE);
#endif

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEntityGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEntityGeneratorDlg::OnPaint() 
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
HCURSOR CEntityGeneratorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEntityGeneratorDlg::OnOK() 
{
	// TODO: Add extra validation here
	
// 	CDialog::OnOK();
}

void CEntityGeneratorDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CEntityGeneratorDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if(m_className.GetLength()<=0)
	{
		MessageBox("请输入类名！");
		GetDlgItem(IDC_EDIT_CLASS_NAME)->SetFocus();
		return;
	}

	if(m_filename.GetLength()<=0)
	{
		m_filename=m_className;
		UpdateData(FALSE);
	}

	CEntityClassGen gen(m_className);
	int ret=0;
	ret=gen.genInclude(m_include);
	if(ret<0)
	{
		MessageBox("生成 include 列表时出错！");
		return;
	}

	ret=gen.genProperty(m_classProperty);
	if(ret<0)
	{
		MessageBox("生成类属性列表时出错！");
		return;
	}
	
	ret=gen.genFile(m_filename);
	if(ret<0)
	{
		CString msg;
		msg.Format("生成类代码时出错！错误码是 %d", ret);
		MessageBox(msg);
		return;
	}

	MessageBox("生成成功！请在 src 目录中查看。");
}

void CEntityGeneratorDlg::OnChangeEditClassName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();

	if(m_filename.Left(1)=="\\")
		m_filename=m_className.Right(m_className.GetLength()-1);
	else if(m_filename.Left(1)=="C")
		m_filename=m_className.Right(m_className.GetLength()-1);
	else
		m_filename=m_className;
	
	UpdateData(FALSE);
}

void CEntityGeneratorDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
