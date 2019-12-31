
// MonitorSystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MonitorSystem.h"
#include "MonitorSystemDlg.h"
#include <FileSysLib\FolderOperation.h>
#include "monitorlib\monitorbuilder.h"
#include <sstream>
#include <FileSysLib\FileOperation.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMonitorSystemDlg 对话框




CMonitorSystemDlg::CMonitorSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMonitorSystemDlg::IDD, pParent)
	, m_monitorDetails(_T(""))
// 	, m_eventLogString(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMonitorSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MONITOR_INFO, m_monitorList);
	DDX_Text(pDX, IDC_EDIT_MONITOR_INFO, m_monitorDetails);
	// 	DDX_Text(pDX, IDC_EDIT_EVENT_LOG, m_eventLogString);
	DDX_Control(pDX, IDC_EDIT_EVENT_LOG, m_txtLog);
}

BEGIN_MESSAGE_MAP(CMonitorSystemDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_START_ALL, &CMonitorSystemDlg::OnBnClickedButtonStartAll)
	ON_BN_CLICKED(IDC_BUTTON_STOP_ALL, &CMonitorSystemDlg::OnBnClickedButtonStopAll)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMonitorSystemDlg::OnBnClickedButtonClose)
	ON_WM_CLOSE()
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MONITOR_INFO, &CMonitorSystemDlg::OnLvnItemchangedListMonitorInfo)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MONITOR_INFO, &CMonitorSystemDlg::OnNMClickListMonitorInfo)
	ON_BN_CLICKED(IDC_BUTTON1, &CMonitorSystemDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMonitorSystemDlg 消息处理程序

BOOL CMonitorSystemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_appPath=CFolderOperation::addGang(CFolderOperation::GetModulePath());

	// 创建日志目录
	CString eventFolder=m_appPath + "EventLogs";
	if(!CFolderOperation::isFolderExist(eventFolder))
	{
		if(!CFolderOperation::createDir(eventFolder))
			MessageBox("日志目录 EventLogs 创建失败！\n\n请先关闭程序，在程序目录中手动创建日志目录后再次运行。");
	}

	CString file=m_appPath+"config.xml";
	if(!CFileOperation::isFileExist(file))
	{
		MessageBox("config.xml 文件不存在！");

		((CButton *)GetDlgItem(IDC_BUTTON_START_ALL))->EnableWindow(FALSE);
	}
	else
	{
		CMonitorBuilder monitorBuilder((LPTSTR)(LPCSTR)file, &m_monitorManager);
		int ret=monitorBuilder.build();

		if(ret==0)
			m_monitorManager.setEventLogPath(eventFolder+"\\");
		else
		{
			switch(ret)
			{
			case -1:
				MessageBox("config 文件路径为空！");
				break;
			case -2:
				MessageBox("config 文件不存在！");
				break;
			case -3:
				MessageBox("pugixml 加载 config.xml 文件失败！");
				break;
			}

			((CButton *)GetDlgItem(IDC_BUTTON_START_ALL))->EnableWindow(FALSE);
		}

	}

	initListCtrl();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMonitorSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMonitorSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMonitorSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMonitorSystemDlg::OnBnClickedButtonStartAll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_monitorManager.startAll();

	int nCount = m_monitorList.GetItemCount();//获取当前已插入的行数
	for(int i=0;i<nCount;i++)
		m_monitorList.SetItemText(i, 1, "已启动");
}

void CMonitorSystemDlg::OnBnClickedButtonStopAll()
{
	// TODO: 在此添加控件通知处理程序代码
	m_monitorManager.stopAll();

	int nCount = m_monitorList.GetItemCount();//获取当前已插入的行数
	for(int i=0;i<nCount;i++)
		m_monitorList.SetItemText(i, 1, "已停止");
}

void CMonitorSystemDlg::initListCtrl()
{
	////初始化界面
	LONG lStyle;
	lStyle = GetWindowLong(m_monitorList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_monitorList.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD styles=m_monitorList.GetExtendedStyle();  
	m_monitorList.SetExtendedStyle(styles|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	//添加列
	m_monitorList.InsertColumn(0, _T("监控器编号"),LVCFMT_CENTER, 80);//插入列
	m_monitorList.InsertColumn(1,_T("监控器状态"),LVCFMT_CENTER,90);        
	m_monitorList.InsertColumn(2,_T("轮询间隔(秒)"),LVCFMT_CENTER,90);        
	m_monitorList.InsertColumn(3,_T("几次后报警"),LVCFMT_CENTER,90);    
	m_monitorList.InsertColumn(4,_T("监控对象类型"),LVCFMT_CENTER, 90);
	m_monitorList.InsertColumn(5,_T("监控对象状态"),LVCFMT_CENTER, 90);

	for(int i=0;i<(int)m_monitorManager.size();i++)
	{
		CMonitor *monitor=m_monitorManager.at(i);
		if(!monitor)
			continue;

		stringstream ss;
		int nCount = m_monitorList.GetItemCount();//获取当前已插入的行数
		ss << i;
		m_monitorList.InsertItem(nCount, _T(""));//插入一行
		m_monitorList.SetItemText(nCount, 0, ss.str().c_str());//第一列
		ss.clear();
		ss.str("");
		m_monitorList.SetItemText(nCount, 1, "未启动");//第二列
		ss << monitor->Interval;
		m_monitorList.SetItemText(nCount, 2, ss.str().c_str());//第三列
		ss.clear();
		ss.str("");
		ss << monitor->Times;
		m_monitorList.SetItemText(nCount, 3, ss.str().c_str());//第四列
		ss.clear();
		ss.str("");
		m_monitorList.SetItemText(nCount, 4, monitor->MonitedObject->Type.c_str());//第四列
		m_monitorList.SetItemText(nCount, 5, monitor->MonitedObject->Status.c_str());//第四列

	}
}

void CMonitorSystemDlg::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE);
}

void CMonitorSystemDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int ret=MessageBox("确实要退出吗？", "询问", MB_OKCANCEL);
	if(ret==1)
		CDialog::OnClose();
}

void CMonitorSystemDlg::OnNMClickListMonitorInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nIndex=m_monitorList.GetSelectionMark();//获取选中的行
	if(nIndex>=0 && nIndex<(int)m_monitorManager.size())
	{
		CMonitor *monitor=m_monitorManager.at(nIndex);
		if(monitor)
		{
			m_monitorDetails=monitor->toString().c_str();

			CString log="";
			CStdioFile file;
			if(file.Open(monitor->getEventLogFile().c_str(), CFile::modeRead | CFile::shareDenyNone))
			{
				CString tmp="";
				while(file.ReadString(tmp)!=NULL)
				{
					log+=tmp+"\r\n";
				}
			}
			m_txtLog.SetWindowText(log);
			m_txtLog.SetSel(log.GetLength(),log.GetLength());

			file.Close();

			UpdateData(FALSE);
		}
	}

	*pResult = 0;
}

void CMonitorSystemDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}
