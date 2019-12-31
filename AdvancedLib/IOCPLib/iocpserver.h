/*
IOCP Server v1.0
www.ipsky.net
*/

#ifndef ___IOCPSERVER
#define ___IOCPSERVER

#include <string>
#include <sstream>

// 函数返值的声明
#include "iocpret.h"
// WinSock2的函数
#include <winsock2.h>
// LPFN_ACCEPTEX 等WinSock2的扩展函数
#include <Mswsock.h>
// WinSock2的函数库，但不加载“Mswsock”的库，手动载入扩展函数
#pragma comment(lib, "ws2_32")

// 去掉结构体定义为0长度的数据警告
// warning C4200: nonstandard extension used : zero-sized array in struct/union
#pragma warning(disable:4200)

// 内存分配
const HANDLE hCurrentProcess = ::GetProcessHeap();
#define MemAlloc(LEN) ::HeapAlloc(hCurrentProcess, HEAP_ZERO_MEMORY, LEN)
#define MemFree(P) ::HeapFree(hCurrentProcess, 0, P)

// IO类型：接受连接/接收数据/发送数据
#define IO_ACCEPT	1
#define IO_RECV		2
#define IO_SEND		3

// Clt状态：已被释放/连接/已关闭
#define CLT_FREE	0
#define CLT_CONN	1
#define CLT_DISC	-1

typedef struct _SynIO
{
	WSAOVERLAPPED olIO;			/* 完成端口模型必须的结构体 */
	struct _SynIO *pNext;		/* 下一个I/O */
	void *pExt;					/* 扩展区 */
	SOCKET sSocket;				/* I/O对应的套接字 */
	char *pData;				/* PostXxx()时，请求处理的数据缓存区 */
	unsigned int uiData;		/* PostXxx()时，请求处理数据的长度 */
	unsigned int uiTrans;		/* 已传输的字节数 */
	unsigned int uiSeq;			/* 用于读请求，指示此I/O的序号 */
	int iIOType;				/* IO_Xxx 指示此I/O的类型 */
	char Data[0];
}SynIO;

typedef struct _Client
{
	struct _Client *pNext;		/* 下一个客户端 */
	void *pExt;					/* 扩展区 */
	SOCKET sClient;				/* 客户端对应的套接字 */
	SOCKADDR_IN saServer;		/* 服务器的连接地址信息 */
	SOCKADDR_IN saClient;		/* 客户端的连接地址信息 */
	int iState;					/* 是否正在关闭客户端的连接 */
	unsigned int uiPendingRecv;	/* 挂起（即未完成）的读操作请求数 */
	unsigned int uiPendingSend;	/* 挂起的写操作请求数 */
	unsigned int uiReadIOSeq;	/* 安排给接收IO的下一个序列号 */
	unsigned int uiReadSeq;		/* 当前要读的序列号 */
	SynIO *pReadIO;				/* 没有按顺序完成的读I/O */
	CRITICAL_SECTION csLock;	/* 同步对Client结构体的操作 */
}Client;

// 回调函数，任何回调函数所传入的IO都必须显式调用SIO_Free进行释放!!
/*
建立一个新连接
1、已对pClt进行了锁定，不能再对csLock进行加锁
2、可以调用DisConn来断开与pClt的连接
*/
typedef void (*PFUNC_OnConnected)(Client* pClt);
/*
对方关闭连接
注意：此函数回调后，不能再对pClt进行任何I/O操作，而且在调用 结束后pClt有可能被释放内存
*/
typedef void (*PFUNC_OnClosed)(Client* pClt, SynIO* pIO);
/*
本地主动关闭连接
注意：与OnClosed一样
*/
typedef void (*PFUNC_OnError)(Client* pClt, SynIO* pIO, int iErr);
/*
接收数据完成
1、内部已进行排序，RecvCompleted被回调后，pIO是有序的
2、可以调用DisConn来断开与pClt的连接
*/
typedef void (*PFUNC_OnRecvCompleted)(Client* pClt, SynIO* pIO);
/*
发送数据完成
注意：pIO->uiTrans为实质发送的字节数，pIO->uiData为投递发送请求时希望发送的字节数
	  如果不相等，则表明只发送了部分数据而已，剩下 pIO->uiData - pIO->uiTrans 没有被发送
*/
typedef void (*PFUNC_OnSendCompleted)(Client* pClt, SynIO* pIO);
/*
当pClt被释放时，此函数被回调，前面的OnClosed / OnError是有可能被释放
此回调是一定被释放pClt内存，所以pClt的内存不能再进行操作!!!
1、断开连接 DisConn		仅关闭套接字(pClt->sClient)且置位pClt->iState标记
2、释放内存	Clt_Free	释放内存(pClt)，pClt所有的未决I/O都完成后才能被释放
*/
typedef void (*PFUNC_OnClientFree)(Client* pClt);

// 初始化IOCP模块
int IOCP_Init(PFUNC_OnConnected fConnected=NULL,			/* 回调函数 */
			  PFUNC_OnClosed fClosed=NULL,
			  PFUNC_OnError fErr=NULL,
			  PFUNC_OnRecvCompleted fRecv=NULL,
			  PFUNC_OnSendCompleted fSend=NULL,
			  PFUNC_OnClientFree fCltFree=NULL,
			  unsigned int uiDataLen = 4096,		/*
													除了0之外
													只要投递WSASend/WSARecv，返值为WSA_IO_PENGDING
													系统都会为IO锁定4KB的内存
													所以将IO的缓存区设置为4KB
													*/
			  unsigned int uiClearPerSec = 30		/* 多少s对空闲链表进行一次清理 */
			  );
// 释放IOCP模块的资源
int IOCP_Free();

// 启动IOCP服务器
int IOCP_Start(const char *IP = "0",				/* 服务器监听的本地地址 , 0 表示监听本地的所有地址 */
//			   unsigned short Port = 2012,			/* 服务端口 */
			   unsigned short Port = 15100,			/* 服务端口 */
			   long InitAcceptNumber = 30,			/* 初始化投递多少个AcceptEx ，并尽量将最大投递维持在这个范围内 */
			   unsigned int uiThread = 0,			/* IOCP的线程数 ， 默认为 4 * CPU */
			   unsigned long KeepAlive = 60			/* 多少s检测一次在线情况 : KeepAlive */
			   );
// 停止IOCP服务器
int IOCP_Shutdown();

// 获取当前的连接数
unsigned int IOCP_GetConnNumber();

/*
以下函数仅能在回调函数内调用
对于 Recv / Send 暂时不要操作 0 字节的内存，IOCP模块内部会当作关闭套接字处理
*/
// 断开与pClt的连接
void DisConn(Client *pClt);
/*
投递读请求
返值：
1、IOCP_OK 投递成功，结果在Recv完成例程中得到
2、IOCP_ERR投递失败，关闭套接字!!!
3、IOCP_NOBUF分配ISO失败

PostXxx 系列函数都必须在LockClt内完成（与WorkThread类似）
*/
extern SynIO* SIO_Alloc();
extern void SIO_Free(SynIO* pIO);
int PostRecv(Client *pClt, char *pData, int iLen);
int PostSend(Client *pClt, char *pData, int iLen);
int PostRecv(Client *pClt, SynIO *pIO);
int PostSend(Client *pClt, SynIO *pIO);

#endif
