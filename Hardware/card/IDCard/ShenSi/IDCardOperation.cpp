// GCardReaderCtl.cpp : Implementation of the CIDCardOperation ActiveX Control class.

#include "stdafx.h"
#include "IDCardOperation.h"
#include "UCmd.h"
#include <C++\FoudationLib\social.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nOpen=1;
bool	bConnect;
int		nCom;
BYTE buff[2048];
int nReset=0;
BOOL bRun;

CIDCardOperation::CIDCardOperation()
{
	
}

CIDCardOperation::~CIDCardOperation()
{
	
}

int CIDCardOperation::initReader()
{
	if(!LoadDll())
		return -2;

	int para0,para1,para2;
	BYTE CMD=0x41;       //初始化端口
	para0=0;
	para1=8811;
	para2=9986;
	int nRet;
	nRet=mycmd(&CMD,&para0,&para1,&para2);
	if((nRet!=62171)||(nRet==-5)||(nRet==-7))
		//if(nRet!=62171)
	{
		bConnect=FALSE;
		//ShowMessage("神思SS628--第二代居民身份证验证终端连接失败！"+0x0a+0x0d+"请检查原因后手动连接！");
// 		ss.Format("连接失败");
// 		m_ctMsg.SetWindowText(ss);
		return -1;
	}
	else
	{
		//
		bConnect=TRUE;
// 		SetTimer(1,300,NULL);
// 		pBtn->SetWindowText("停止读卡");
// 		m_ctMsg.SetWindowText("连接成功，开始读卡");
		return 0;
	}

}

// 返回值：
// 0，成功读卡
// 2，未找到卡
// 1，读卡失败
// <0，
int CIDCardOperation::read()
{
	BYTE CMD;
	int para0,para1,para2;
	int nRet,nRet1;

		bRun=TRUE;
// 	m_ctMsg.SetWindowText("寻找卡..");
	//------------------------------------------------------------
	CMD=0x43;       //验证卡
	//para0=1001;
	para1=8811;
	para2=9986;
	nRet=mycmd(&CMD,&para0,&para1,&para2);
	if(nRet==62171)
	{
		//m_strMsg="正在读卡...";
// 		m_ctMsg.SetWindowText("正在读卡...");
		//--------------------------------------------------------

		CMD=0x44;       //读基本信息
		//para0=0;
		para1=8811;
		para2=9986;
		int nRet;
		nRet=mycmd(&CMD,&para0,&para1,&para2);
		if ((nRet==62171) || (nRet==62172))
		{
			m_strNewAddr="";
			
			CMD=0x45;       //读最新住址信息
			//para0=0;
			para1=8811;
			para2=9986;
			nRet1=mycmd(&CMD,&para0,&para1,&para2);
			if(nRet1==62171)
			{
				CFile f_name;
				
				char byNewAddr[72];
				if(f_name.Open("NewAdd.txt",CFile::modeRead))
				{
					f_name.SeekToBegin();
					f_name.Read(&byNewAddr,70);			
					byNewAddr[70]=0x0;byNewAddr[71]=0x0;
					m_strNewAddr=byNewAddr;

					f_name.Close();
				}
			}
			else
			{
				m_strNewAddr="";
			}

			if ((nRet==62171) || (nRet==62172))
			{
// 				SendMessage(CARD_READ_MSG, 0, 0);  !!!!!!!!!!!!!!!!!!!! 读卡成功 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// 				Beep(1500,300);
				return 0;

			}
			else
				return nRet;
// 				else if (nRet==0)
// 				{
// 					::MessageBox(NULL,"调用sdtapi.dll错误",MB_OK,0);
// 				}else if( nRet==-1)
// 				{
// 					::MessageBox(NULL,"相片解码错误",MB_OK,0);
// 				}
// 				else if (nRet==-2)
// 				{
// 					::MessageBox(NULL,"wlt文件后缀错误",MB_OK,0);
// 				}
// 				else if (nRet==-3)
// 				{
// 					::MessageBox(NULL,"wlt文件打开错误",MB_OK,0);
// 				}
// 				else if (nRet==-4)
// 				{
// 					::MessageBox(NULL,"wlt文件格式错误",MB_OK,0);
// 				}
// 				else if (nRet==-5)
// 				{
// 					::MessageBox(NULL,"软件未授权",MB_OK,0);
// 				}
// 				else if (nRet==-6)
// 				{
// 					::MessageBox(NULL,"设备连接错误",MB_OK,0);
// 				}


		}
		else
		{
			//读基本信息错误

// 			m_ctMsg.SetWindowText("读卡失败!");
//			::MessageBox(NULL,"读卡失败！可能浏览器需要以管理员身份运行。",MB_OK,0);
			return 1;
		}
		//--------------------------------------------------------
	}
	else
	{
		//寻卡/证错误    选卡/证错误
		//m_ctMsg.SetWindowText("选卡错误...");
// 		m_ctMsg.SetWindowText("寻找卡...");
		return 2;
	}
}

CString CIDCardOperation::GetName() 
{
	memset(buff, 0x00, 2048);
	myGetName(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetSex() 
{
	memset(buff, 0x00, 2048);
	myGetSex(buff);
	CString strResult(buff);
	strResult.TrimRight();
	if(strResult=="1")
		strResult="男";
	else
		strResult="女";
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetFolk() 
{
	memset(buff, 0x00, 2048);
	myGetFolk(buff);
	CString strResult(buff);
	strResult.TrimRight();
	strResult=FOLK[atoi((LPTSTR)(LPCSTR)strResult)].c_str();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetBirth() 
{
	memset(buff, 0x00, 2048);
	myGetBirth(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetAddr() 
{
	memset(buff, 0x00, 2048);
	myGetAddr(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetIDNum() 
{
	memset(buff, 0x00, 2048);
	myGetIDNum(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetDepartment() 
{
	memset(buff, 0x00, 2048);
	myGetDep(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetValidDateFrom() 
{
	memset(buff, 0x00, 2048);
	myGetBegin(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetValidDateTo() 
{
	memset(buff, 0x00, 2048);
	myGetEnd(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

CString CIDCardOperation::GetPicPath() 
{
	memset(buff, 0x00, 2048);
	myGetPicPath(buff);
	CString strResult(buff);
	strResult.TrimRight();
	// TODO: Add your dispatch handler code here

	return strResult;
// 	return strResult.AllocSysString();
}

