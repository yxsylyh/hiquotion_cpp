#if !defined(AFX_IDCARDOPERATION_H__DD8B4DB1_00D7_4678_984B_D97BBF74FC6C__INCLUDED_)
#define AFX_IDCARDOPERATION_H__DD8B4DB1_00D7_4678_984B_D97BBF74FC6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// IDCardOperation.h : Declaration of the CIDCardOperation class.

#define CARD_READ_MSG WM_USER+100

/////////////////////////////////////////////////////////////////////////////
// CIDCardOperation : See GCardReaderCtl.cpp for implementation.

class CIDCardOperation
{
// Constructor
public:
	CIDCardOperation();
	~CIDCardOperation();

	int initReader();
	int read();
	CString GetName();
	CString GetSex();
	CString GetFolk();
	CString GetBirth();
	CString GetAddr();
	CString getNewAddr() const { return m_strNewAddr; }
	CString GetIDNum();
	CString GetDepartment();
	CString GetValidDateFrom();
	CString GetValidDateTo();
	CString GetPicPath();
// Dispatch maps
// 	//{{AFX_DISPATCH(CIDCardOperation)
// 	afx_msg short setCardInfo(LPCTSTR cardType, LPCTSTR manufacture);
// 	afx_msg long ReadCard();
// 	afx_msg void StopRead();
// 	afx_msg BSTR GetName();
// 	afx_msg BSTR GetSex();
// 	afx_msg BSTR GetFolk();  // 民族
// 	afx_msg BSTR GetBirth();
// 	afx_msg BSTR GetAddr();
// 	afx_msg BSTR GetIDNum();  // 身份证号
// 	afx_msg BSTR GetDepartment();  // 签发机关
// 	afx_msg BSTR GetValidDateFrom();  // 证件有效日期（从）
// 	afx_msg BSTR GetValidDateTo();    // 证件有效日期（到）
// 	afx_msg BSTR GetPicPath();
// 	//}}AFX_DISPATCH
// 	DECLARE_DISPATCH_MAP()

private:
	CString m_strNewAddr;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDCARDOPERATION_H__DD8B4DB1_00D7_4678_984B_D97BBF74FC6C__INCLUDED_)
