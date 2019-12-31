// RfOperation.cpp: implementation of the CRfOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RfOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRfOperation::CRfOperation()
: m_icdev(NULL), m_isConnected(FALSE)
{

}

CRfOperation::~CRfOperation()
{
	disconnect();
}

// 返回值：
// 0：成功
// -1：设备初始化失败
// -2：取设备版本失败
// -3：取0扇区密码失败
int CRfOperation::connect()
{
// 	CString str;
// 	int port,baud;
	unsigned char ver[32];
	
// 	GetDlgItemText(IDC_COMBO_PORT,str);
// 	port=atoi(str.Mid(4,1));
// 	baud=GetDlgItemInt(IDC_COMBO_BAUD);
	m_icdev=rf_init(0, 9600);
	if (m_icdev<=0)
		return -1;
	
	ZeroMemory(ver,32);
	int st=rf_get_status(m_icdev,ver);
	if (st!=0)
		return -2;
	
	char* key="ffffffffffff";
	unsigned char sector=0;
// 	for(unsigned char sector=0;sector<16;sector++)
// 	{
		st=rf_load_key_hex(m_icdev,0,sector,key);
		if(st!=0)
		{
			return -3;
// 			CString str;
// 			str.Format("%d sector load key error!",sector);
// 			m_list.AddString(str);
// 		}
	}
	
// 	rf_beep(m_icdev,30);

	m_isConnected=TRUE;
	return 0;
}

void CRfOperation::disconnect()
{
	if(m_isConnected)
	{
		rf_exit(m_icdev);
		m_icdev=NULL;
		m_isConnected=FALSE;
	}
}

BOOL CRfOperation::isDeviceExist()
{
	if(!m_isConnected)
		connect();

	if(m_isConnected)
		return TRUE;
	else
		return FALSE;
}

BOOL CRfOperation::findCard(std::string &cardSn)
{
	unsigned long snr=0;
	unsigned char mode=0; //GetDlgItemInt(IDC_COMBO_MODE);
	int st=rf_card(m_icdev,mode,&snr);
	if (st!=0)
		return FALSE;

	char CardNumber[10];
	ZeroMemory(CardNumber,10);
	hex_a((unsigned char*)&snr,CardNumber,sizeof(snr));
	cardSn=CardNumber;

	st=rf_halt(m_icdev);
	rf_beep(m_icdev,30);

	return TRUE;
}

int CRfOperation::readCard(std::string &content)
{
	unsigned char sector=0;
	int st=rf_authentication(m_icdev,0,sector);
	if(st!=0)
		return -1;

	char rdata[17];
	ZeroMemory(rdata,17);

	st=rf_read(m_icdev,sector*4+1,(unsigned char *)rdata);
	if(st!=0)
		return -2;

//  	rf_beep(m_icdev,30);
	st=rf_halt(m_icdev);

	if(rdata[0]=='\0')
		content="";
	else
		content=rdata;
	
	return 0;
}

int CRfOperation::writeCard(std::string content)
{
	unsigned char sector=0;
	int st=rf_authentication(m_icdev,0,sector);
	if(st!=0)
		return -1;
	
	char* wdata=(char *)content.c_str();
	st=rf_write(m_icdev,sector*4+1,(unsigned char*)wdata);
	if(st!=0)
		return -2;

	return 0;
}
