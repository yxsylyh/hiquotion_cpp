// NetClient.cpp: implementation of the CNetClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetClient.h"
#include <fstream>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNetClient::CNetClient()
{
	IsStart=false;
	bOprUnInit=false;
	m_pProcessRecvData=NULL;
	hSendEvent=CreateEvent(NULL,false,false,NULL);
	hWorkEvent=CreateEvent(NULL,false,false,NULL);
	hExitEvent=CreateEvent(NULL,false,false,NULL);
}
CNetClient::~CNetClient()
{
	CloseHandle(hSendEvent);
	CloseHandle(hWorkEvent);
	CloseHandle(hExitEvent);
}
DWORD _stdcall SendProc(LPVOID pParam)
{
	CNetClient * pNetClient=(CNetClient*) pParam;
	HANDLE event[2];
	event[0]=pNetClient->hSendEvent;
	event[1]=pNetClient->hExitEvent;

	while(true)
	{
		Sleep(1);
		::EnterCriticalSection(&pNetClient->SendMsgQueSection);
		//队列为空，等待发送事件触发
		if(pNetClient->SendMsgQueue.IsEmpty())
		{
			::LeaveCriticalSection(&pNetClient->SendMsgQueSection);
			//为空，或者发送完毕
			ResetEvent(pNetClient->hSendEvent);
			TRACE("\nTheSendProc Is Waiting....");	
			DWORD Index=::WaitForMultipleObjects(2,event,false,INFINITE);
			if((Index-WAIT_OBJECT_0)==1)return 0L;
		}
		else
		{
			//取下一个结点，并发送
			MSG_NODE p=pNetClient->SendMsgQueue.DeQueue();
			//释放队列
			::LeaveCriticalSection(&pNetClient->SendMsgQueSection);
			DWORD retlen;
			bool bRet=pNetClient->m_sClient.SendMsg(p.pData,p.DataLength,&retlen,WSA_INFINITE);
			if(bRet==false || retlen!=p.DataLength)
			{
				if(GetLastError()!=CLIENT_FUNERROR)
				pNetClient->m_pProcessRecvData(NULL,0);
				pNetClient->UnInit();
			}	
		}
	}
	return 0L;
}
DWORD _stdcall WorkProc(LPVOID pParam)
{
	CNetClient* pNetClient=(CNetClient*)pParam;
	HANDLE event[2];
	event[0]=pNetClient->hWorkEvent;
	event[1]=pNetClient->hExitEvent;
	
	while(true)
	{
		Sleep(1);
		::EnterCriticalSection(&pNetClient->RecvMsgQueSection);
		//队列为空，等待发送事件触发
		if(pNetClient->RecvMsgQueue.IsEmpty())
		{
			::LeaveCriticalSection(&pNetClient->RecvMsgQueSection);
			//为空，或者发送完毕
			ResetEvent(pNetClient->hWorkEvent);
			TRACE("\nTheWorkProc Is Waiting....");			
			DWORD Index=::WaitForMultipleObjects(2,event,false,INFINITE);
			if((Index-WAIT_OBJECT_0)==1)return 0L;
		}
		else
		{
			//取下一个结点，并发送
			MSG_NODE p=pNetClient->RecvMsgQueue.DeQueue();
			//释放队列
			::LeaveCriticalSection(&pNetClient->RecvMsgQueSection);
			//调用回调函数，处理数据
			pNetClient->m_pProcessRecvData(p.pData,p.DataLength);
		}
	}
	return 0L;
}
DWORD _stdcall RecvProc(LPVOID pParam)
{
	CNetClient * pNetClient=(CNetClient*)pParam;
	char RecvBuf[BUFFER_SIZE];
	DWORD retlen;
	while (true)
	{
		Sleep(1);
		TRACE("\nTheRecvThread Is Waiting...");
		if(!pNetClient->m_sClient.RecvMsg(RecvBuf,BUFFER_SIZE,&retlen,WSA_INFINITE) &&  GetLastError()!=CLIENT_FUNERROR)
		{
			if(pNetClient->bOprUnInit)return 0L;//应用程序请求退出	
			//连接已经被断开，通知上层(通过调用回调函数)
			pNetClient->m_pProcessRecvData(NULL,0);
			pNetClient->UnInit();
			return 0L;
		}
		else
		{
			//没收到字节？还是出错
			if(retlen==0)
			{
				pNetClient->m_pProcessRecvData(NULL,0);
				pNetClient->UnInit();
				return 0L;
			}
			//将接收到的数据放到接收队列里
			MSG_NODE Msg;
			Msg.DataLength=retlen;
			memcpy(Msg.pData,RecvBuf,retlen);
			//插入消息队列
			::EnterCriticalSection(&pNetClient->RecvMsgQueSection);
			if(pNetClient->SendMsgQueue.IsEmpty())
			{
				pNetClient->RecvMsgQueue.EnQueue(Msg);
				::LeaveCriticalSection(&pNetClient->RecvMsgQueSection);
				//如果消息队列为空，告诉工作线程可以进行工作了
				SetEvent(pNetClient->hWorkEvent);
			}
			else
			{
				pNetClient->RecvMsgQueue.EnQueue(Msg);
				::LeaveCriticalSection(&pNetClient->RecvMsgQueSection);
			}
		}
	}
	return 0L;
}
bool CNetClient::Init(ProcessRecvData* pProcessRecvData,LPCTSTR szSvrAddr, unsigned long iSvrPort)
{
	if(pProcessRecvData==NULL //回调函数空
		|| szSvrAddr==NULL //地址空
		|| IsStart)//已经启动过了
		return false;	
	::InitializeCriticalSection(&SendMsgQueSection);
	::InitializeCriticalSection(&RecvMsgQueSection);	
	IsStart=false;
	bOprUnInit=false;
	m_pProcessRecvData=pProcessRecvData;
	int  bRet=InitNetWork(szSvrAddr,iSvrPort,HostIpAddr);
	if(0==bRet)
	{
		IsStart=true;
		return true;
	}
	else
		return false;
}
void CNetClient::UnInit()
{
	if(!IsStart)return;
	bOprUnInit=true;
	SetEvent(hExitEvent);	
	SetEvent(hExitEvent);
	m_sClient.UnInit();	
	::DeleteCriticalSection(&SendMsgQueSection);
	::DeleteCriticalSection(&RecvMsgQueSection);
	SendMsgQueue.MakeEmpty();
	RecvMsgQueue.MakeEmpty();	
	m_pProcessRecvData=NULL;
	IsStart=false;
}
int CNetClient::InitNetWork(LPCTSTR szSvrAddr,unsigned int SvrPort,LPCTSTR pHostIpAddress)
{
	CString LogStr;
	int Error=0;
	WSADATA wsaData;
	char Name[100];
	hostent *pHostEntry;
	in_addr rAddr;
	memset((void *)pHostIpAddress,0,sizeof(pHostIpAddress));
	//Net Start Up
	Error=WSAStartup(MAKEWORD(0x02,0x02),&wsaData);
	if(Error!=0)
	{
		Error = WSAGetLastError();
		LogStr.Format("WSAStartUp Faild With Error: %d",Error);
		WriteLogString(LogStr);

		return Error;
	}
	//Make Version
	if ( LOBYTE( wsaData.wVersion ) != 2 ||
         HIBYTE( wsaData.wVersion ) != 2 )
	{
		WSACleanup( );
		
		WriteLogString("The Local Net Version Is not 2");

		return -1;
	}
	//Get Host Ip
	Error = gethostname ( Name, sizeof(Name) );
	if( 0 == Error )
	{
		pHostEntry = gethostbyname( Name );
		if( pHostEntry != NULL )
		{
			memcpy( &rAddr, pHostEntry->h_addr_list[0], sizeof(struct in_addr) );
			sprintf((char * )pHostIpAddress,"%s",inet_ntoa( rAddr ));
		}
		else
		{
			Error = WSAGetLastError();
			LogStr.Format("GetHostIp faild with Error: %d",Error);
			WriteLogString(LogStr);

		}
	}
	else
	{
		Error = WSAGetLastError();
		LogStr.Format("gethostname faild with Error: %d",Error);
		WriteLogString(LogStr);
	}
	//Socket Create
	if(0==Error)
	{
		if(!m_sClient.CreateSocket(SOCK_STREAM))
		{
			Error=WSAGetLastError();
			LogStr.Format("Create Client Socket Faild :%d",Error);
			//WriteLogString(LogStr);
			return Error;
		}
	}
	if(0==Error)
	{
		if(!m_sClient.ConnectSocket((char *)szSvrAddr,SvrPort))
		{
			Error=WSAGetLastError();
			LogStr.Format("Create Client Socket Faild :%d",Error);
			WriteLogString(LogStr);
			return Error;
		}
	}
	//启动工作线程，并升高工作线程的等级至最高
	if(0==Error)
	{
		HANDLE WorkHan=0;
		unsigned long WorkID;
		if((WorkHan=CreateThread(NULL,0,WorkProc,this,0,&WorkID))==NULL)
		{
			Error=GetLastError();
			LogStr.Format("Create WorkThread Faild With Error %d",Error);
			WriteLogString(LogStr);
			return Error;
		}
		SetThreadPriority(WorkHan,THREAD_PRIORITY_HIGHEST);
		CloseHandle(WorkHan);
	}
	//启动接收线程
	if(0==Error)
	{
		HANDLE RecvHan=0;
		unsigned long RecvID;
		if((RecvHan=CreateThread(NULL,0,RecvProc,this,0,&RecvID))==NULL)
		{
			Error=GetLastError();
			LogStr.Format("Create RecvThread Faild With Error %d",Error);
			WriteLogString(LogStr);
			SetEvent(hExitEvent);//退出先前创建的线程
			return Error;
		}
		CloseHandle(RecvHan);
	}
	//启动发送线程
	if(0==Error)
	{
		HANDLE ThreHan;
		unsigned long ThrID;
		if((ThreHan=CreateThread(NULL,0,SendProc,this,0,&ThrID))==NULL)
		{
			Error=GetLastError();
			LogStr.Format("Create SEND Thred Faild With Error %d",Error);
			WriteLogString(LogStr);
			SetEvent(hExitEvent);//退出先前创建的线程
			return Error;
		}
		CloseHandle(ThreHan);
	}
	return Error;
}
bool CNetClient::SendMsg(char * pData,unsigned long DataLength)
{		
		//未调用初始化函数
		if(!IsStart || pData==NULL || DataLength==0)return false;
		//构造消息
		MSG_NODE Msg;
		Msg.DataLength=DataLength;
		memcpy(Msg.pData,pData,DataLength);
		//插入消息队列
		::EnterCriticalSection(&SendMsgQueSection);
		if(SendMsgQueue.IsEmpty())
		{
			SendMsgQueue.EnQueue(Msg);
			::LeaveCriticalSection(&SendMsgQueSection);
			//如果消息队列为空，告诉等待的发送线程可以发送了
			SetEvent(hSendEvent);
		}
		else
		{
			SendMsgQueue.EnQueue(Msg);
			::LeaveCriticalSection(&SendMsgQueSection);
		}
		return true;
}
void CNetClient::WriteLogString(LPCTSTR strLog)
{
	SYSTEMTIME sysTm;
	::GetLocalTime(&sysTm);
	ofstream       OutputFile;
	OutputFile.open( "NetClientLog.txt" ,ios::app);
	OutputFile<<sysTm.wYear<<"年"<<sysTm.wMonth<<"月"<<sysTm.wDay<<"日"<<sysTm.wHour<<"时"<<sysTm.wMinute<<"分"<<sysTm.wSecond<<"秒"<<":"<<"    "<<strLog<<"\n"<<endl;
	OutputFile.close();
}
/********************************************************************
函数名  : Queue<T>::~Queue() 
输入参数:
输出参数:
功能描述: 队列析构函灵敏，清空所有队列元素
全局变量: 无
调用模块: 
附加说明: 
********************************************************************/
template <class T>  Queue<T>::~Queue()
{
	QueueNode<T> *p=front;
	while(front!=NULL)
	{
		p=front;
		front=front->link;
		delete p;
	}
}
/********************************************************************
函数名  : Queue<T>::EnQueue
输入参数:
const T & item :要插入的结点的引用
输出参数:
功能描述: 在队列中插入一个结点
全局变量: 无
调用模块: 
附加说明: 
********************************************************************/
template <class T> void Queue<T>::EnQueue(const T & item)
{
	if(front==NULL)front=rear=new QueueNode<T>(item,NULL);
	else rear=rear->link=new QueueNode<T>(item,NULL);
}
/********************************************************************
函数名  : Queue<T>::DeQueue() 
输入参数:
T  :返回被删除结点的值
输出参数:
功能描述: 从队列中取出一个结点，并返回该结点的值
全局变量: 无
调用模块: 
附加说明: 
********************************************************************/
template <class T> T Queue<T>::DeQueue()
{
	T  retvalue;
	memset(&retvalue,0,sizeof(T));
	if(IsEmpty())
		return retvalue;
	QueueNode<T> * p=front;
	retvalue=p->data;
	front=front->link;
	delete p;
	return retvalue;
}
/********************************************************************
函数名  : Queue<T>::MakeEmpty() 
输入参数:
输出参数:
功能描述: 将队列元素清空
全局变量: 无
调用模块: 
附加说明: 
********************************************************************/
template <class T> void Queue<T>::MakeEmpty()
{
	if(front==NULL)return ;
	QueueNode<T> * p=front;
	while(front!=NULL)
	{
		p=front;
		front=front->link;
		delete p;
	}
	front=rear=NULL;
}
/*************************************************************************/
CClientSocket::CClientSocket()
{

}			
CClientSocket::~CClientSocket()
{
}
void CClientSocket::UnInit()
{
	ShutDownSocket();
	CloseSocekt();
	if(m_hExitEvent != (WSAEVENT)0xcccccccc)WSACloseEvent(m_hExitEvent);
}
bool CClientSocket::CreateSocket(SOCKET *pNewSocket,int iSockType)
{
	m_hExitEvent=WSACreateEvent();
	WSAResetEvent(m_hExitEvent);
	
	return ((*pNewSocket=WSASocket(AF_INET,iSockType,0,NULL,0,WSA_FLAG_OVERLAPPED))==INVALID_SOCKET)?
		false:true;
}
bool CClientSocket::BindSocket(SOCKET BindSocket,char *szHostAddr,unsigned short iHostPort)
{
	struct sockaddr_in inAddr;
	inAddr.sin_addr.S_un.S_addr=inet_addr(szHostAddr);
	inAddr.sin_family=AF_INET;
	inAddr.sin_port=htons(iHostPort);
	return (bind(BindSocket,(PSOCKADDR)&inAddr,sizeof(inAddr)))
		==SOCKET_ERROR?false:true;
}
bool CClientSocket::ShutDownSocket(SOCKET nowSocket)
{
	return shutdown(nowSocket,SD_BOTH)?false:true;
}
bool CClientSocket::CloseSocket(SOCKET nowSocket)
{
	return (closesocket(nowSocket)==SOCKET_ERROR)?false:true;
}
bool CClientSocket::SendData(SOCKET socket,char *data,DWORD len,DWORD *retlen,WSAEVENT hSendEvent,DWORD time)
{
	WSABUF DataBuf;
	WSAEVENT hEvents[2];
	WSAOVERLAPPED SendOverLapp;
	DWORD flag;

	hEvents[0]=m_hExitEvent;
	hEvents[1]=hSendEvent;
	DataBuf.buf=data;
	DataBuf.len=len;
	memset(&SendOverLapp,0,sizeof(WSAOVERLAPPED));
	SendOverLapp.hEvent=hSendEvent;
	flag=0;
	/////////////////////////////////////
	int ret;
	if((ret=WSASend(socket,&DataBuf,1,retlen,flag,&SendOverLapp,NULL))==0)
		return true;
	else if((ret==SOCKET_ERROR)&&(WSAGetLastError()==WSA_IO_PENDING))
	{
		DWORD EventCaused=WSAWaitForMultipleEvents(2,hEvents,FALSE,time,FALSE);
		WSAResetEvent(hSendEvent);
		if(EventCaused == WSA_WAIT_FAILED || EventCaused == WAIT_OBJECT_0)
		{
			if(EventCaused == WAIT_OBJECT_0)
				SetLastError(CLIENT_FUNERROR);
			return false;
		}
		flag=0;
		return WSAGetOverlappedResult(socket,&SendOverLapp,retlen,false,&flag)?
			true:false;
	}
	else
		return false;
}
bool CClientSocket::RecvData(SOCKET socket,char *data,DWORD len,DWORD *retlen,WSAEVENT hRecvEvent,DWORD time)
{
	WSABUF DataBuf;
	WSAEVENT hEvents[2];
	WSAOVERLAPPED RecvOverLapp;
	DWORD flag;

	hEvents[0]=m_hExitEvent;
	hEvents[1]=hRecvEvent;
	DataBuf.buf=data;
	DataBuf.len=len;
	memset(&RecvOverLapp,0,sizeof(WSAOVERLAPPED));
	RecvOverLapp.hEvent=hRecvEvent;
	flag=0;
	/////////////////////////////////////
	int ret;
	if((ret=WSARecv(socket,&DataBuf,1,retlen,&flag,&RecvOverLapp,NULL))==0)
		return true;
	else if((ret==SOCKET_ERROR)&&(WSAGetLastError()==WSA_IO_PENDING))
	{ 
		DWORD EventCaused=WSAWaitForMultipleEvents(2,hEvents,false,time,false);
		WSAResetEvent(hRecvEvent);
		if(EventCaused == WSA_WAIT_FAILED || EventCaused == WAIT_OBJECT_0)
		{
			if(EventCaused == WAIT_OBJECT_0)
				SetLastError(CLIENT_FUNERROR);
			return false;
		}
		flag=0;
		return WSAGetOverlappedResult(socket,&RecvOverLapp,retlen,false,&flag)?
			true:false;
	}
	else
		return false;
}
bool CClientSocket::SendDataS(SOCKET socket,char *data,DWORD len,DWORD *retlen,WSAEVENT hSendEvent,DWORD time)
{
	DWORD left,idx,thisret;
	left=len;
	idx=0;
	int oflag=0;
	while(left>0)
	{
		if(!SendData(socket,&data[idx],left,&thisret,hSendEvent,time))
		{
			*retlen=0;
			return false;
		}
		WSAResetEvent(hSendEvent);
		left-=thisret;
		idx+=thisret;
		if(thisret==0)
		{
			oflag++;
			if(oflag>5)
				break;
		}
	}
	*retlen=idx;
	return (idx==len)?true:false;
}
bool CClientSocket::RecvDataS(SOCKET socket,char *data,DWORD len,DWORD *retlen,WSAEVENT hRecvEvent,DWORD time)
{
	DWORD left,idx,thisret;
	left=len;
	idx=0;
	int oflag=0;
	while(left>0)
	{
		if(!RecvData(socket,&data[idx],left,&thisret,hRecvEvent,time))
		{
			*retlen=0;
			return false;
		}
		WSAResetEvent(hRecvEvent);
		left-=thisret;
		idx+=thisret;
		if(thisret==0)
		{
			oflag++;
			if(oflag>5)
				break;
		}
	}
	*retlen=idx;
	return (idx==len)?true:false;
}
bool CClientSocket::SendMsg(char * data,DWORD len,DWORD *retlen,DWORD time)
{
	WSAEVENT hEvent=WSACreateEvent();
	bool bSend=SendDataS(m_Socket,data,len,retlen,hEvent,time);
	WSACloseEvent(hEvent);
	return bSend;
}
bool CClientSocket::RecvMsg(char * data,DWORD len,DWORD *retlen,DWORD time)
{	
	WSAEVENT hEvent=WSACreateEvent();
	bool Recv=RecvData(m_Socket,data,len,retlen,hEvent,time);
	WSACloseEvent(hEvent);
	return Recv;
}
bool CClientSocket::ConnectSocket(char * szDestAddr,unsigned short iDestPort)
{
	struct sockaddr_in inAddr;
	inAddr.sin_family=AF_INET;
	inAddr.sin_port=htons(iDestPort);
	inAddr.sin_addr.S_un.S_addr=inet_addr(szDestAddr);
	return (connect(m_Socket,(PSOCKADDR)&inAddr,sizeof(inAddr)))
		    ==SOCKET_ERROR ? false:true;
}