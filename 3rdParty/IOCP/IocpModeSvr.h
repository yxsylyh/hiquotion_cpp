// IocpModeSvr.h: interface for the CIocpModeSvr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOCPMODESVR_H__46FFF420_23C3_4356_A88D_AEBDA61EA186__INCLUDED_)
#define AFX_IOCPMODESVR_H__46FFF420_23C3_4356_A88D_AEBDA61EA186__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>
#include <afxtempl.h>

#include <winsock2.h>
#pragma  comment(lib,"ws2_32.lib")

/***************************************************************************************
文件名:IocpModeSvr.h
类名:CIocpModeSvr
类说明:本类是一个完成端口模型的网络服务器引擎
运行平台:WinNT3.5以上版本、Windows2000
输入接口说明:本类接收一个回调函数地址，该函数具有如下原型
             void _stdcall ProcessRecvData(unsigned long sIP,
			                               SOCKET sClient,
										   char * pData,
										   unsigned long DataLength);
		 此回调函数用来接收从客户端发来的数据或者某客户端断开连接的通知(有始有终)
		 unsigned long sIP : 表示数据通知的客户端IP地址
		 SOCKET sClient :服务器用于和客户端通迅的套接字，
		                 如果不是断开连接消息，
						 则您可使用此参数调用SendMsg向客户端发送数据
		 char * pData : 本次操作的数据
		 unsigned long DataLength :本次操作数据的数据长度
		 提示：如果pData==NULL 并且DataLength 则表示那是客户端断开连接的消息，
		       请针对业务做处理吧。
输出接口说明:
		 引擎初始化函数，第一参为回调地址(必须正确填写)，第二参为服务端口号
		 初始化成功返回真，否则返回假
         bool Init(ProcessRecvData* pProcessRecvData,unsigned long iSvrPort=SVRPORT);

		 引擎反初始化函数，请在程序退出时调用，或者在程序需要重新启动服务时调用
		 void UnInit();

         以下在关于发送消息函数组的接口说明

         1、向目标IP客户端发送数据，
		    第一参为目标客户端IP,
			第二参为数据区地址，
			第三参为数据区长度
			成功"提交"返回真，否则返回假，
			那可能是因为客户端已经断开或者根本就没有连接。
		 bool SendMsg(LPCTSTR TargetIp,char * pData,unsigned long Length);


         2、向目标套接字发送数据
		    第一参为客户端套接字
			第二参为数据区地址
			第三参为数据区长度
			成功"提交"返回真，否则返回假
			那可能是因为客户端已经断开连接
			提示：此函数为不需要检索的发送数据函数，具有高效率的特性。
			      你可以在你的数据通知回调中以第二参的sClient直接填写于
				  第一参中发送数据，如果你在接收到数据时需要回传消息，请
				  使用此函数
			成功"提交"返回真,否则返回假
		 bool SendMsg(SOCKET sClient,char * pData,unsigned long Length);


         3、向所有连线客户端发送数据
		    发送数据到所有已经正确连线的客户端
			第一参为数据区地址
			第二参为数据区长度
			成功"提交"返回真，否则返回假
			大部分情况下都会返回真 ^_^
		 bool SendMsgToAll(char * pData,unsigned long Length);


		 4、向除了某个IP外的其它所有在线客户端发送数据
		    第一参为除外的IP
			第二参为数据区地址,
			第三参为数据区长度，
			成功"提交"返回真，否则返回假
			大部分情况下都会返回真
		 bool SendMsgToOther(LPCTSTR SourceIp,char* pData,unsigned long Length);


		 5、向除了某个Socket外的其它所有在线客户端发送数据
		    第一参为除外的Socket
			第二参为数据区地址
			第三参为数据区长度
			成功"提交"返回真，否则返回假
			大部分情况下都会返回真
		 bool SendMsgToOther(SOCKET ExceptSocket,char * pData,unsigned long Length);

        附助函数组1
		1、const char * GetLocalIpAdd()
		   返回本地Ip地址，返回值为点分十进制的字符串
		2、unsigned short GetSvrPort()
		   返回服务使用的侦听端口号

		附助函数助2
		1、bool DisConnectClient(LPCTSTR ClientIp);
		   切断参数中指定的IP的客户端的连接，成功返回真，否则返回假。
		2、bool DisConnectClient(SOCKET sClient);
		   切断参数中指定的客户机的连接，参数中指定了要切断了套接口。
		3、void DisConnectAll();
		   切断所有客户机的连接。

编写者：杨飞 qq:5535833
编写时间：2004年12月20日

修改记录：--------------------------------------------------------------------------
          1、2016年2月2日   by hiquotion.
		    修改 _PER_HANDLE_DATA 结构体，使其包含ip对应的端口号。
		    修改获取本地ip函数的代码，使其返回第一个 192.168 开头的本地ip，如果没有这样的ip，则返回本地ip列表中的最后一个
		  --------------------------------------------------------------------------
		  2、
		  --------------------------------------------------------------------------

***************************************************************************************/

//服务端口
#define SVRPORT 10012
//缓冲区大小
#define BUFFER_SIZE 4096
//接收数据
#define RECV_POSTED 0
//发送数据
#define SEND_POSTED 1
//单句柄数据
typedef struct _PER_HANDLE_DATA
{
	unsigned long IpAddr;
	SOCKET sClient;	
	unsigned short nPort;
}PER_HANDLE_DATA,*LPPER_HANDLE_DATA;
//IO操作数据
typedef struct _PER_IO_OPERATION_DATA
{
	//重叠结构
	OVERLAPPED OverLapped;
	//数据缓冲区
	WSABUF RecvDataBuf;
	WSABUF SendDataBuf;
	char RecvBuf[BUFFER_SIZE];
	char SendBuf[BUFFER_SIZE];
	//操作类型表示
	bool OperType;
}PER_IO_OPERATION_DATA,*PPER_IO_OPERATION_DATA;

//回调处理数据函数原型
typedef void __stdcall ProcessRecvData(unsigned long sIP,
									   unsigned short nPort,
									   SOCKET sClient,
									   char * pData,
									   unsigned long DataLength);

DWORD WINAPI ServerWorkerProc(LPVOID lParam);
DWORD WINAPI ListenProc(LPVOID lParam);

class CIocpModeSvr  
{
public:
	CIocpModeSvr();
	virtual ~CIocpModeSvr();
public:
	//初始化
	bool Init(ProcessRecvData* pProcessRecvData,unsigned long iSvrPort=SVRPORT);
	//反初始化
	void UnInit();
	/*  用于发送消息的函数组*/
public:
	bool SendMsg(LPCTSTR TargetIp,char * pData,unsigned long Length);
	bool SendMsg(SOCKET sClient,char * pData,unsigned long Length);
	bool SendMsgToAll(char * pData,unsigned long Length);
	bool SendMsgToOther(LPCTSTR ExceptIp,char* pData,unsigned long Length);
	bool SendMsgToOther(SOCKET ExceptSocket,char * pData,unsigned long Length);
public:
	//获得本地Ip地址
	const char * GetLocalIpAdd(){ 
		if(IsStart)return HostIpAddr.c_str();
		else return NULL;
	}
	//获得服务器使用的端口号
	unsigned short GetSvrPort(){
		if(IsStart)return m_SvrPort;
		else return 0;
	}
public:
	bool DisConnectClient(LPCTSTR ClientIp);
	bool DisConnectClient(SOCKET sClient);
	void DisConnectAll();
protected:
	int InitNetWork(unsigned int SvrPort=SVRPORT,
		             std::string *pHostIpAddress=NULL);
	void WriteLogString(LPCTSTR strLog);


	ProcessRecvData* m_pProcessRecvData;
private:
	//完成句柄
	HANDLE CompletionPort;
	//主机IP
	std::string  HostIpAddr;
	//客户信息列表
	CArray <PER_HANDLE_DATA,PER_HANDLE_DATA> ClientInfo;
	//客户信息临界保护量
	CRITICAL_SECTION cInfoSection;
	//服务是否已经启动
	bool IsStart;
	//侦听端口
	SOCKET ListenSocket;
	//侦听线程句柄，用于反初始化时销毁侦听线程
	HANDLE ListenThreadHandle;
	//服务端口记录
	unsigned short m_SvrPort;

	friend DWORD WINAPI ServerWorkerProc(LPVOID lParam);
	friend DWORD WINAPI ListenProc(LPVOID lParam);
};

#endif // !defined(AFX_IOCPMODESVR_H__46FFF420_23C3_4356_A88D_AEBDA61EA186__INCLUDED_)
