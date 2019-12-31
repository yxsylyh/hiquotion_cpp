// NetClient.h: interface for the CNetClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETCLIENT_H__CF62B9AC_911A_4CE6_81B2_55CB2588A42E__INCLUDED_)
#define AFX_NETCLIENT_H__CF62B9AC_911A_4CE6_81B2_55CB2588A42E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SERVERPORT 10012
#define BUFFER_SIZE 4096

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
/*******************************************************************************************
文件名：NetClient.h NetClient.cpp
类名：CNetClient
类说明：本类是一个三线程加重叠IO模型的网络客户端引擎 (TCP协议)
运行平台:Windows2000
输入接口说明：本类接收一个回调函数地址，该函数具有如下原型
		void __stdcall ProcessRecvData(char * pData,unsigned long DataLength);
        此回调函数用来接收从服务端发来的数据或者和服务器的连接断开的通知
		char * pData:接收过的数据的指针
		unsigned long DataLength:接收过的数据的长度
		提示：如果pData为空并且DataLength为零则表示和服务器的连接已经断开，
		您需要重新调用Init()函数初始化引擎。
输出接口说明：
    1、 bool Init(ProcessRecvData* pProcessRecvData,LPCTSTR szSvrAddr,unsigned long iSvrPort=SERVERPORT);
        引擎初始化函数 第一参为回调地址(必须正确填写)，第二参为服务器Ip地址，第三参
		为服务端口号(服务器使用的Listen端口号)
	2、	void UnInit();
	    引擎反初始化函数  调用后将会使系统重新回到就绪状态	
	3、 bool SendMsg(char * pData,unsigned long DataLength);
	    发送消息函数，第一参为要发送的数据地址，第二参为要发送数据的真实长度
	4、 LPCTSTR GetLocalIP()
	    附助函数，当系统正确初始化以后，可以使用此函数获得本得的IP地址
编写者：杨飞 qq:5535833
编写时间：2004年12月20日
修改记录：--------------------------------------------------------------------------------
          1、
		  --------------------------------------------------------------------------------
		  2、
		  --------------------------------------------------------------------------------
*******************************************************************************************/
//错误定义:套接字上的数据操作正忙
#define  CLIENT_FUNERROR 0x100
class CClientSocket  
{
public:
	CClientSocket();
	CClientSocket(bool & bSuccess,int iSockType,char * szSvrAddr,unsigned short iSvrPort)
	{
		bSuccess=false;
		bSuccess=CreateSocket(iSockType);
		bSuccess=ConnectSocket(szSvrAddr,iSvrPort);
	}
	virtual ~CClientSocket();
public:
	void UnInit();
	bool CreateSocket(int iSockType){
		return CreateSocket(&m_Socket,iSockType);
	}
	bool BindSocket(char *szHostAddr,unsigned short  iHostPort){
		return BindSocket(m_Socket,szHostAddr,iHostPort);
	}
	bool ShutDownSocket(){
		return ShutDownSocket(m_Socket);
	}
	bool CloseSocekt(){
		return CloseSocket(m_Socket);
	}
	bool ConnectSocket(char * szDestAddr,unsigned short iDestPort);
	bool SendMsg(char * data,DWORD len,DWORD *retlen,DWORD time);
	bool RecvMsg(char * data,DWORD len,DWORD *retlen,DWORD time);
protected:
	bool CreateSocket(SOCKET *pNewSocket,int iSockType);
	bool BindSocket(SOCKET BindSocket,char *szHostAddr,unsigned short iHostPort);
	bool ShutDownSocket(SOCKET nowSocket);
	bool CloseSocket(SOCKET nowSocket);
	bool SendDataS(SOCKET socket,char *data,DWORD len,DWORD *retlen,WSAEVENT hSendEvent,DWORD time);
	bool RecvDataS(SOCKET socket,char *data,DWORD len,DWORD *retlen,WSAEVENT hRecvEvent,DWORD time);
private:
	bool SendData(SOCKET socket,char *data,DWORD len,DWORD *retlen,WSAEVENT hSendEvent,DWORD time);
	bool RecvData(SOCKET socket,char *data,DWORD len,DWORD *retlen,WSAEVENT hRecvEvent,DWORD time);
private:
	SOCKET m_Socket;
	WSAEVENT m_hExitEvent;
};
/*******************************************************************************
消息队列类：用于存储消息队列，即待发送的消息的集合，或者是接收过待处理的集合
*******************************************************************************/
template <class T> class Queue;
//链式队列结点定义
template <class T> class QueueNode
{
	friend class Queue<T>;
private:
	T data;//数据域
	QueueNode<T> *link;//链域
	QueueNode(T d,QueueNode *l=NULL):link(l){memcpy(&data,&d,sizeof(T));}//构造函数
};
//链式队列类定义
template <class T> class Queue
{
public:
	Queue():rear(NULL),front(NULL){}//构造函数
	~Queue();//析构函数
	void EnQueue(const T & item);//将item加入到队列中
	T DeQueue();//删除并返回队头元素
	T GetFront(){return front->data;}//查看队头元素的值
	void MakeEmpty();//置空队列
	int IsEmpty() const {return front==NULL;}//判断队列空否
private:
	QueueNode<T> *front ,*rear;//队头，队尾指针
};
typedef struct _MSG_NODE
{
	unsigned long DataLength;
	char pData[BUFFER_SIZE];
}MSG_NODE,*PMSG_NODE;
/*********************************************************************************/

//通过回调函数调用上层处理函数
typedef void __stdcall ProcessRecvData(char * pData,unsigned long DataLength);

//内部采用标准三线程模型
DWORD _stdcall SendProc(LPVOID pParam);
DWORD _stdcall WorkProc(LPVOID pParam);
DWORD _stdcall RecvProc(LPVOID pParam);

class CNetClient  
{
public:
	CNetClient();
	virtual ~CNetClient();
public:
	bool Init(ProcessRecvData* pProcessRecvData,LPCTSTR szSvrAddr,unsigned long iSvrPort=SERVERPORT);
	void UnInit();
	bool SendMsg(char * pData,unsigned long DataLength);
	LPCTSTR GetLocalIP(){return IsStart ? HostIpAddr:NULL;}
protected:
	int InitNetWork(LPCTSTR szSvrAddr,
		unsigned int SvrPort=SERVERPORT,
		LPCTSTR HostIpAddr=NULL);
	void WriteLogString(LPCTSTR strLog);
private:
	CClientSocket m_sClient;
	ProcessRecvData* m_pProcessRecvData;
	Queue <MSG_NODE> SendMsgQueue;
	CRITICAL_SECTION SendMsgQueSection;
	HANDLE hSendEvent;
	Queue <MSG_NODE> RecvMsgQueue;
	CRITICAL_SECTION RecvMsgQueSection;
	//开始工作事件
	HANDLE hWorkEvent;
	//退出事件	
	HANDLE hExitEvent;
	//是否用户进行了反初始化操作，如果是：接收线程将不再调用回调函数
	bool bOprUnInit;
	//是否已经被驱动
	bool IsStart;
	char HostIpAddr[16];

	friend DWORD _stdcall SendProc(LPVOID pParam);
	friend DWORD _stdcall WorkProc(LPVOID pParam);
	friend DWORD _stdcall RecvProc(LPVOID pParam);
};
#endif // !defined(AFX_NETCLIENT_H__CF62B9AC_911A_4CE6_81B2_55CB2588A42E__INCLUDED_)
