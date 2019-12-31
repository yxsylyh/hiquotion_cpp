// MonitorSystemDlg.h : 头文件
//

#pragma once

#include "monitorlib\monitormanager.h"
#include "afxcmn.h"
#include "afxwin.h"

// CMonitorSystemDlg 对话框
class CMonitorSystemDlg : public CDialog
{
// 构造
public:
	CMonitorSystemDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MONITORSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void initListCtrl();

private:
	CMonitorManager m_monitorManager;
	CString m_appPath;
public:
	afx_msg void OnBnClickedButtonStartAll();
	afx_msg void OnBnClickedButtonStopAll();
	CListCtrl m_monitorList;
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnClose();
//	afx_msg void OnLvnItemchangedListMonitorInfo(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_monitorDetails;
	afx_msg void OnNMClickListMonitorInfo(NMHDR *pNMHDR, LRESULT *pResult);
// 	CString m_eventLogString;
	CEdit m_txtLog;
	afx_msg void OnBnClickedButton1();
};
