// SIDCardOperation.h: interface for the CSIDCardOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIDCARDOPERATION_H__EC4FA293_47E1_487B_A835_0775F5AC6544__INCLUDED_)
#define AFX_SIDCARDOPERATION_H__EC4FA293_47E1_487B_A835_0775F5AC6544__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSIDCardOperation  
{
public:
	CSIDCardOperation();
	virtual ~CSIDCardOperation();

	int initReader();
	void closeReader();
	BOOL isCardExist();
	int read();

	CString getCardId() const { return m_cardId; }
	CString getCardPubDate() const { return m_cardPubDate; }
	CString getCardValidateTo() const { return m_cardValidateTo; }
	CString getSidNo() const { return m_sidNo; }

	CString getIdNo() const { return m_idNo; }
	CString getName() const { return m_name; }
	CString getSex() const { return m_sex; }
	CString getFolk() const { return m_folk; }
	CString getBirthPlace() const { return m_birthPlace; }
	CString getBirthday() const { return m_birthday; }

protected:
	int doSSSECmd_Hex();
	int doPublicAppCmd_Hex();
	int doSelectCardInfoFileCmd_Hex();
	int doSelectPersonInfoFileCmd_Hex();
	int doGetRecordCmd_Hex(CString flag, CString len, CString &result);
	int doGetRecordCmd(char flag, char len, CString &result);

	CString getResult(CString result);
	void initString();

private:
	HANDLE icdev;
	BOOL m_isOpen;
                               // 名称          文件 flag 长度
	CString m_cardId;      // 卡识别码          EF05  01   10
	CString m_cardPubDate; // 发卡日期          EF05  05   04
	CString m_cardValidateTo;  // 有效期        EF05  06   04
	CString m_sidNo;      // 卡号（就是社保号） EF05  07   09
	CString m_idNo;        // 身份证号          EF06  08   12
	CString m_name;        // 姓名              EF06  09   1E
	CString m_sex;         // 性别              EF06  0A   01
	CString m_folk;        // 民族              EF06  0B   01
	CString m_birthPlace;  // 出生地            Ef06  0C   03
	CString m_birthday;    // 生日              EF06  0D   04
};

#endif // !defined(AFX_SIDCARDOPERATION_H__EC4FA293_47E1_487B_A835_0775F5AC6544__INCLUDED_)
