/*
IOCP Server v1.0
www.ipsky.net
*/

#include "iocpserver.h"

/************************************************************************/
/*                          全局变量 / 定义 / 声明                      */
/************************************************************************/
/*
回调函数指针
*/
static PFUNC_OnConnected OnConnected;
static PFUNC_OnClosed OnClosed;
static PFUNC_OnError OnError;
static PFUNC_OnRecvCompleted OnRecvCompleted;
static PFUNC_OnSendCompleted OnSendCompleted;
static PFUNC_OnClientFree OnCltFree;
/*
服务器监听客户端的连接
*/
static SOCKET sListen;
static unsigned int uiIP;
static unsigned short usPort;
static HANDLE hListenThread;
static HANDLE hCompletion;
static HANDLE hAcceptEvent;
static unsigned int uiWorkThread;
static LPFN_ACCEPTEX lpfnAcceptEx;
static LPFN_GETACCEPTEXSOCKADDRS lpfnGetAcceptExSockaddrs;

static CRITICAL_SECTION csAccept;	/*
									同步对 lAcceptPending 的操作
									试用过 ::InterlockedXxx 系列函数
									发现最后的 SIO 数小于 lAcceptPending ??? 不解 ...
									*/
static long lInitAcceptNumber;
long lAcceptPending;

/*
管理所有的已连接Clt
接受连接 / 断开连接( closesocket )
*/
static Client *pConn;
static unsigned int uiConn;
static CRITICAL_SECTION csConn;
// SIO的缓存区长度
static unsigned int uiData;
// 清空空1/2闲链表的时间
static unsigned int uiClearTime;
// 机器的CPU数量
static unsigned int uiCPU;
// 服务器的启动标记：0 / 1
static int iStart;

// 其它模块的导入函数
extern void FreePool_Init(unsigned int uiDataLen,
				   unsigned int uiClearPerSec);
extern void FreePool_Free();
extern void FreePool_Clear();
extern unsigned int SIO_GetAllocNumber();
extern Client* Clt_Alloc(SOCKET sSocket);
extern void Clt_Free(Client *pClt);
extern unsigned int Clt_GetAllocNumber();

// 如果uiData为0，则分配AcceptEx的缓存区长度默认长度为 ACCEPTBUFLEN
#define ACCEPTBUFLEN 96
// 同步锁
#define LockClt(PCLT) ::EnterCriticalSection(&PCLT->csLock)
#define UnLockClt(PCLT) ::LeaveCriticalSection(&PCLT->csLock)
#define LockConn() ::EnterCriticalSection(&csConn)
#define UnLockConn() LeaveCriticalSection(&csConn)
#define LockAccept() ::EnterCriticalSection(&csAccept)
#define UnLockAccept() LeaveCriticalSection(&csAccept)

static std::string errMessage="";

std::string getErrMessage()
{
	return errMessage;
}

// 扩展用的外部数据
static void *ext=NULL;

void setExtData(void *extData)
{
	ext=extData;
}

/************************************************************************/
/*                                I/O 函数                              */
/************************************************************************/
/*
投递一个AcceptEx I/O请求
如果成功则返值为 IOCP_OK
失败的话返值为 IOCP_ERR ，sListen 被关闭时导致投递失败
*/
int PostAccept(SynIO *pIO)
{
	errMessage="";
	
	DWORD dwBytes = 0;

	// IO类型
	pIO->iIOType = IO_ACCEPT;
	// 生成套接字
	pIO->sSocket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if(INVALID_SOCKET != pIO->sSocket)
	{
		// 投递AcceptEx请求
		if(NO_ERROR != lpfnAcceptEx(sListen, 
			pIO->sSocket,
			pIO->pData, 
			0,
			sizeof(SOCKADDR_IN) + 16, 
			sizeof(SOCKADDR_IN) + 16, 
			&dwBytes, 
			&pIO->olIO))
		{
			// 出错
			if(WSA_IO_PENDING != ::WSAGetLastError())
			{
				return IOCP_ERR;
			}
		}
	}
	else
	{
		// 生成套接字失败，当作没有缓存
		return IOCP_NOBUF;
	}

	return IOCP_OK;
}
/*
投递一个发送请求
参数：
pClt	发送数据到此客户端
pData	所发送数据的缓存区
iLen	数据的长度（要小于uiData，因为只发送小于等于uiData的数据，多出的数据不被发送）
返值：
IOCP_ERR	出错，应该DisConn
IOCP_NOBUF	没有内存：（1）分配SIO失败  （2）调用WSASend是出现IOCP_NOBUF错误
IOCP_OK		投递成功
*/
int PostSend(Client *pClt, char *pData, int iLen)
{
	errMessage="";
	
	SynIO *pIO = 0;

	// 分配一个SIO
	if(pIO = SIO_Alloc())
	{
		// uiData为空，将使用pData的缓存区首址
		// !!! pData 的内存不能在PostSend完成时被释放或修改
		if(0 == uiData)
		{
			pIO->pData = pData;
		}
		// uiData非空，将pData的内存拷贝到SIO的缓存区中
		else
		{
			iLen = (iLen > (int)uiData ? uiData : iLen);
			memcpy(pIO->pData, pData, iLen);
		}
		// 数据的长度
		pIO->uiData = iLen;
		// 投递出发送请求
		switch(PostSend(pClt, pIO))
		{
			// 投递Send IO成功，IOCP模块将调用OnSendCompleted回调函数
		case IOCP_OK:
			break;
			// 没有内存WSAENOBUFS，过多的WSASend使得系统内部已用完所有的4KB内存块
		case IOCP_NOBUF:
			{
				SIO_Free(pIO);
				return IOCP_NOBUF;
			}
			// WSASend调用出错
		default:
			{
				SIO_Free(pIO);
				return IOCP_ERR;
			}
		}
	}
	else
	{
		return IOCP_NOBUF;
	}

	return IOCP_OK;
}
/*
投递一个接收请求
具体用法与PostSend类似
*/
int PostRecv(Client *pClt, char *pData, int iLen)
{
	errMessage="";
	
	SynIO *pIO = 0;

	if(pIO = SIO_Alloc())
	{
		if(0 == uiData)
		{
			pIO->pData = pData;
		}
		pIO->uiData = (iLen > (int)uiData ? uiData : iLen);
		switch(PostRecv(pClt, pIO))
		{
		case IOCP_OK:
			break;
		case IOCP_NOBUF:
			{
				SIO_Free(pIO);
				return IOCP_NOBUF;
			}
		default:
			{
				SIO_Free(pIO);
				return IOCP_ERR;
			}
		}
	}
	else
	{
		return IOCP_NOBUF;
	}

	return IOCP_OK;
}
/*
投递一个发送请求，需手工设置SIO的 pData / uiData
此函数是为了提供更大的灵活性，可以在OnRecvCompleted后重用SIO
*/
int PostSend(Client *pClt, SynIO *pIO)
{
	errMessage="";
	
	DWORD dwBytes = 0;
	DWORD dwFlags = 0;
	WSABUF wsaBuf = {0};

	// IO类型
	pIO->iIOType = IO_SEND;
	// 填WSABUF
	wsaBuf.buf = pIO->pData;
	wsaBuf.len = pIO->uiData;

	// 投递发送请求
	if(NO_ERROR != ::WSASend(pClt->sClient, 
								&wsaBuf, 
								1, 
								&dwBytes, 
								dwFlags, 
								&pIO->olIO, 
								NULL))
	{
		// 如果投递成功，则返值为 NO_ERROR ，IOCP模块会回调OnSendCompleted
		// 如果投递失败，WSAGetLastError() 非 WSA_IO_PENDING ，则说明连接已关闭
		// 由于这个IO在投递时就失败，没有进行到完成端口的IO队列，所以IOCP模块不会为此SIO回调OnError或OnClosed
		switch(::WSAGetLastError())
		{
		case WSA_IO_PENDING:
			break;
		case WSAENOBUFS:
			return WSAENOBUFS;
		default:
			return IOCP_ERR;
		}
	}

	pClt->uiPendingSend ++;

	return IOCP_OK;
}
/*
投递一个读请求
与PostSend类似
*/
int PostRecv(Client *pClt, SynIO *pIO)
{
	errMessage="";
	
	DWORD dwBytes = 0;
	DWORD dwFlags = 0;
	WSABUF wsaBuf = {0};

	pIO->iIOType = IO_RECV;
	pIO->uiSeq = pClt->uiReadIOSeq;
	
	wsaBuf.buf = pIO->pData;
	wsaBuf.len = pIO->uiData;
	
	if(NO_ERROR != ::WSARecv(pClt->sClient, 
								&wsaBuf, 
								1, 
								&dwBytes, 
								&dwFlags, 
								&pIO->olIO, 
								NULL))
	{
		switch(::WSAGetLastError())
		{
		case WSA_IO_PENDING:
			break;
		case WSAENOBUFS:
			return WSAENOBUFS;
		default:
			return IOCP_ERR;
		}
	}
	
	pClt->uiPendingRecv ++;
	pClt->uiReadIOSeq ++;

	return IOCP_OK;
}
/*
断开与pClt的连接
仅能在回调函数内调用
*/
void DisConn(Client *pClt)
{
	errMessage="";
	
	Client *pCur = 0 , *pBack = 0;
	// 锁定pConn链表与uiConn
	LockConn();
	// 找出pClt在pConn的位置
	for(pCur = pConn; pCur; )
	{
		if(pCur == pClt)
		{
			break;
		}
		pBack = pCur;
		pCur = pCur->pNext;
	}
	// 将pClt从pConn中断开
	if(pCur)
	{
		(pBack ? pBack->pNext : pConn) = pCur->pNext;
		pCur->pNext = NULL;
		uiConn--;
	}
	// 如果pClient没有关闭套接字则将其关闭，并置位其字段（防止多次调用DisConn  ...）
	if(INVALID_SOCKET != pClt->sClient)
	{
		::closesocket(pClt->sClient);
		pClt->sClient = INVALID_SOCKET;
		pClt->iState = CLT_DISC;
	}
	UnLockConn();
}

/************************************************************************/
/*                             辅助函数.内部调用                        */
/************************************************************************/
// 分配一个AcceptEx的SIO
inline SynIO* AllocAcceptIO()
{
	errMessage="";
	
	SynIO *pIO = SIO_Alloc();
	if(pIO)
	{
		// 如果uiData为0则必须要为AcceptEx的缓存区分配一块内存
		if(0 == uiData)
		{
			pIO->pData = (char*)MemAlloc(ACCEPTBUFLEN);
			if(NULL == pIO->pData)
			{
				SIO_Free(pIO);
				return NULL;
			}
			pIO->uiData = ACCEPTBUFLEN;
		}
		// 增加计数器，停止服务器的时候必须先清空投递的AcceptEx IO
		lAcceptPending++;
	}

	return pIO;
}
// 释放一个AcceptEx的SIO
inline void FreeAcceptIO(SynIO *pIO)
{
	errMessage="";
	
	if(pIO)
	{
		lAcceptPending--;
		if(0 == uiData)
		{
			MemFree(pIO->pData);
		}
		SIO_Free(pIO);
	}
}
// 投递一个AcceptEx，封装了AllocAcceptIO与前面的PostAccept
inline int PostAccept()
{
	errMessage="";
	
	SynIO *pIO = 0;

	if(pIO = AllocAcceptIO())
	{
		if(IOCP_OK == PostAccept(pIO))
		{
			return IOCP_OK;
		}
		else
		{
			FreeAcceptIO(pIO);
		}
	}

	return IOCP_ERR;
}
// 向pConn链表插入一个新的pClt
inline void AddConn(Client *pClt)
{
	errMessage="";
	
	LockConn();
	pClt->pNext = pConn;
	pConn = pClt;
	uiConn++;
	UnLockConn();
}
// 清空pClt链表，断开所有的连接
inline void DisConnAll()
{
	errMessage="";
	
	LockConn();
	while(pConn)
	{
		// 关闭
		if(INVALID_SOCKET != pConn->sClient)
		{
			::closesocket(pConn->sClient);
			pConn->sClient = INVALID_SOCKET;
		}
		pConn->iState = CLT_DISC;
		// 下一个Clt
		pConn = pConn->pNext;
	}
	uiConn = 0;
	UnLockConn();
}

/************************************************************************/
/*                             线程                                     */
/************************************************************************/
// 当RecvIO完成时，先排序，调用此函数后，返回一个排序后的IO链表
inline SynIO* SortReadIO(Client *pClt, SynIO *pIO)
{
	errMessage="";
	
	// 对读I/O进行排序
	for(SynIO *pCur = pClt->pReadIO, *pBack = 0; pCur; )
	{
		if(pCur->uiSeq > pIO->uiSeq)
		{
			break;
		}
		pBack = pCur;
		pCur = pCur->pNext;
	}
	if(pBack)
	{
		pIO->pNext = pBack->pNext;
		pBack->pNext = pIO;
	}
	else
	{
		pIO->pNext = pClt->pReadIO;
		pClt->pReadIO = pIO;
	}
	// 获取所有按序完成的读IO
	for(pCur = pClt->pReadIO, pBack = NULL, pIO = NULL; pCur; )
	{
		// 已没有按序的读IO
		if(pCur->uiSeq != pClt->uiReadSeq)
		{
			// pBack指向的是最后一个按序的读IO
			if(pBack)
			{
				pBack->pNext = NULL;
			}
			break;
		}
		// pIO为按序读IO链表的首结点
		if(NULL == pIO)
		{
			pIO = pClt->pReadIO;
		}
		// 重置缓存链表及其它排序信息
		pClt->pReadIO = pCur->pNext;
		pBack = pCur;
		pCur = pClt->pReadIO;
		pClt->uiReadSeq++;
	}

	return pIO;
}

// 工作线程
DWORD WINAPI WorkThread(LPVOID lp)
{
	errMessage="";

	// 完成端口函数
	BOOL bRet;
	SynIO *pIO;
	Client *pClt;
	DWORD dwTrans;
	// 下一个IO（ 排序乱序的读IO / 释放乱序的读IO ）
	SynIO *pNextIO;
	// 退出码
	DWORD dwRetCode = IOCP_ERR;
	// AcceptEx后获取套接字信息
	int nLocalLen, nRmoteLen;
	LPSOCKADDR pLocalAddr, pRemoteAddr;

	while(1)
	{
		// 等待系统处理I/O完成或其它地方调用PostQueuedCompletionStatus
		bRet = ::GetQueuedCompletionStatus(hCompletion, 
			&dwTrans, 
			(LPDWORD)&pClt, 
			(LPOVERLAPPED*)&pIO, 
			WSA_INFINITE);

		// 由于超时参数为 WSA_INFINITE 所以返值有两种，0（出错）与非0
		if(bRet)
		{
			// 只有PostQueuedCompletionStatus(hCompletion, -1, 0, NULL)才发送空I/O
			if(pIO)
			{
				if(IO_ACCEPT != pIO->iIOType)
				{
					// 保存下已传输的字节数
					pIO->uiTrans = dwTrans;
					// 锁定pClt !!!
					LockClt(pClt);
					// Recv IO
					if(IO_RECV == pIO->iIOType)
					{
						// IO计数器减1
						pClt->uiPendingRecv--;
						// 传输dwTrans字节的数据
						if(dwTrans)
						{
							// 排序
							pIO = SortReadIO(pClt, pIO);
							// 依次提交
							for(; pIO; )
							{
								pNextIO = pIO->pNext;
								// 回调后pIO的释放操作由回调函数完成
								if(OnRecvCompleted)
									OnRecvCompleted(pClt, pIO);
								// 处理接收的时候外部调用DisConn()断开连接
								if(CLT_DISC == pClt->iState)
								{
									// 释放完剩余的已排序读IO
									for(pIO = pNextIO; pIO; )
									{
										pNextIO = pIO->pNext;
										SIO_Free(pIO);
										pIO = pNextIO;
									}
									// 检查是否可以释放Clt
									goto ONFREE;
								}
								pIO = pNextIO;
							}
						}
						// 套接字已被关闭（2、客户端关闭套接字）
						else
						{
ONCLOSED:
							// 通知上层连接已关闭
							if(OnClosed)
								OnClosed(pClt, pIO);
ONFREE:
							// 如果未关闭套接字则将其关闭
							if(CLT_CONN == pClt->iState)
							{
								DisConn(pClt);
							}
							// 如果已没有未决I/O则释放Clt
							if(0 == pClt->uiPendingRecv && 0 == pClt->uiPendingSend)
							{
								// 释放掉乱序的读IO
								for(pIO = pClt->pReadIO; pIO; )
								{
									pNextIO = pIO->pNext;
									SIO_Free(pIO);
									pIO = pNextIO;
								}
								// 解锁（Clt有可能没有被释放内存，下次重用的时候会造成死锁）
								UnLockClt(pClt);
								// 通知上层pClt将被释放掉，不能再对此内存进行任何操作
								if(OnCltFree)
								{
									OnCltFree(pClt);
								}
								// 调用Clt模块的释放函数
								Clt_Free(pClt);
								// 继续等待IO完成
								continue;
							}
						}
					}
					else
					{
						pClt->uiPendingSend--;
						if(dwTrans)
						{
							if(OnSendCompleted)
								OnSendCompleted(pClt, pIO);
							if(CLT_DISC == pClt->iState)
							{
								goto ONFREE;
							}
						}
						else
						{
							goto ONCLOSED;
						}
					}
					UnLockClt(pClt);
				}
				else
				{
					// 分配Client、设置sClient属性与sListen相同
					// AcceptEx 不自动继承 sListen 套接字的属性
					if((pClt = Clt_Alloc(pIO->sSocket)) &&
						(SOCKET_ERROR != ::setsockopt( pIO->sSocket,
						SOL_SOCKET,
						SO_UPDATE_ACCEPT_CONTEXT,
						(char*)&sListen,
						sizeof(sListen))))
					{
						// 设置客户端的扩展属性字段
						pClt->pExt=ext;

						// 添加到连接链表
						AddConn(pClt);
						// 获取连接的信息
						lpfnGetAcceptExSockaddrs(
							pIO->pData,
							0,
							sizeof(sockaddr_in) + 16,
							sizeof(sockaddr_in) + 16,
							(SOCKADDR **)&pLocalAddr,
							&nLocalLen,
							(SOCKADDR **)&pRemoteAddr,
							&nRmoteLen);
						memcpy(&pClt->saServer, pLocalAddr, nLocalLen);
						memcpy(&pClt->saClient, pRemoteAddr, nRmoteLen);
						// 将客户端套接字关联到完成端口
						::CreateIoCompletionPort((HANDLE)pClt->sClient, hCompletion, (DWORD)pClt, 0);
						LockClt(pClt);
						// 通知上层
						if(OnConnected)
							OnConnected(pClt);
						// 上次关闭此连接
						if(CLT_DISC == pClt->iState)
						{
							goto ONFREE;
						}
						UnLockClt(pClt);
					}
					// 分配Clt失败或者是设置套接字属性失败
					else
					{
						::closesocket(pIO->sSocket);
						if(pClt)
						{
							Clt_Free(pClt);
						}
					}
					// 如果未达到 lInitAcceptNumber上限，再次投递一个AcceptEx IO
					LockAccept();
					if(lAcceptPending > lInitAcceptNumber || 
						IOCP_OK != PostAccept(pIO))
					{
						FreeAcceptIO(pIO);
					}
					UnLockAccept();
				}
			}
			// 退出
			else
			{
				dwRetCode = IOCP_OK;
				break;
			}
		}
		// ???出错
		else
		{
			// 失败的I/O操作
			if(pIO)
			{
				// WSARecv / WSASend 投递的I/O出错（2、本地主动关闭套接字）
				if(IO_ACCEPT != pIO->iIOType)
				{
					// 锁定pClt
					LockClt(pClt);
					// I/O计数器减1
					if(IO_RECV == pIO->iIOType)
					{
						pClt->uiPendingRecv--;
					}
					else
					{
						pClt->uiPendingSend--;
					}
					// 通知上层
					if(OnError)
						OnError(pClt, pIO, ::GetLastError());
					// 跳到释放处理过程
					goto ONFREE;
				}
				// AcceptEx出错 ，sListen 被关闭
				// 还不能退出线程 ，可能是Listen线程在清空所有的未决AcceptEx
				else
				{
					::closesocket(pIO->sSocket);
					LockAccept();
					FreeAcceptIO(pIO);
					UnLockAccept();
				}
			}
			// ?为空...什么情况??
			else
			{
				;
			}
		}
	}

	return dwRetCode;
}

// 监听线程
DWORD WINAPI ListenThread(LPVOID lp)
{
	errMessage="";
	
	unsigned int ui = 0;
	SynIO *pIO = 0;
	HANDLE hWaitEvents[1 + 512] = {0};
	int nEventCount = 0;
	WSANETWORKEVENTS wsaEvent = {0};

	// 初始化lAcceptPending
	lAcceptPending = 0;
	// 投递lInitAcceptNumber个Accept I/O
	LockAccept();
	for(ui = 0; ui < (unsigned int)lInitAcceptNumber; ui++)
	{
		PostAccept();
	}
	UnLockAccept();
	// 生成工作线程
	hWaitEvents[nEventCount ++] = hAcceptEvent;
	for(ui = 0; ui < uiWorkThread; ui++)
	{
		hWaitEvents[nEventCount ++] = ::CreateThread(NULL, 0, WorkThread, 0, 0, NULL);
	}
	// 等待hAcceptEvent和退出通知
	while(1)
	{
		ui = ::WSAWaitForMultipleEvents(nEventCount, hWaitEvents, FALSE, 30000, FALSE);
		if(0 == iStart || WSA_WAIT_FAILED == ui)
		{
			// 关闭监听套接字
			::closesocket(sListen);
			// 等待所有的AcceptEx IO被结束并释放
			while(lAcceptPending)
			{
				::Sleep(10);
			}
			// 断开所有的连接
			DisConnAll();
			while(Clt_GetAllocNumber())
			{
				::Sleep(10);
			}
			// 通知所有线程退出
			for(ui = 1; (int)ui < nEventCount; ui++)
			{
				::PostQueuedCompletionStatus(hCompletion, -1, 0, NULL);
			}
			// 等待所有的I/O处理线程退出
			::WaitForMultipleObjects(nEventCount - 1, &hWaitEvents[1], TRUE, INFINITE);
			// 关闭所有线程的句柄
			for(ui = 1; (int)ui < nEventCount; ui++)
			{	
				::CloseHandle(hWaitEvents[ui]);
			}
			// 关闭完成端口的句柄
			::CloseHandle(hCompletion);
			// 退出
			ui = IOCP_OK;
			break;
		}
		if(WSA_WAIT_TIMEOUT == ui)
		{
			// 释放掉空闲池一半的表项
			FreePool_Clear();
			// ..
		}
		else
		{
			ui -= WAIT_OBJECT_0;
			if(0 == ui)
			{
				::WSAEnumNetworkEvents(sListen, hWaitEvents[ui], &wsaEvent);
				// hAcceptEvent受信，事件为FD_ACCEPT，投递的Accept I/O不够用
				if(wsaEvent.lNetworkEvents & FD_ACCEPT)
				{
					// 这里不限制lInitAcceptNumber每次增加10个AcceptEx，是为了增加新的连接
					// 而WorkThread限制lInitAcceptNumber，是为了防止限制的Accept IO膨胀
					LockAccept();
					for(ui = 0; ui < 10; ui++)
					{
						PostAccept();
					}
					UnLockAccept();
				}
			}
			else
			{
				// 工作线程退出，有错误发生，停止服务器
				iStart = 0;
				continue;
			}
		}
	}

	return ui;
}

/************************************************************************/
/*                            模块的控制函数                            */
/************************************************************************/
int IOCP_Init(PFUNC_OnConnected fConnected,
			  PFUNC_OnClosed fClosed,
			  PFUNC_OnError fErr,
			  PFUNC_OnRecvCompleted fRecv,
			  PFUNC_OnSendCompleted fSend,
			  PFUNC_OnClientFree fCltFree,
			  unsigned int uiDataLen,
			  unsigned int uiClearPerSec)
{
	errMessage="";

	// 获取CPU的数量
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	uiCPU = SystemInfo.dwNumberOfProcessors;

	// 初始化WinSock2.2
	WSADATA wsaData = {0};
	WORD sockVersion = MAKEWORD(2, 2);
	int ret=::WSAStartup(sockVersion, &wsaData);
	if(ret!=0)
	{
		switch(ret)
		{
		case WSASYSNOTREADY:
			errMessage="WSAStartup 调用失败！网络通信依赖的网络子系统还没有准备好";
			break;
		case WSAVERNOTSUPPORTED:
			errMessage="WSAStartup 调用失败！所需的Windows Sockets API的版本未由特定的Windows Sockets实现提供。（需要 Windows Sockets 版本为 2.0）";
			break;
		case WSAEINVAL:
			errMessage="WSAStartup 调用失败！应用程序指出的Windows Sockets版本（2.0）不被该DLL支持";
			break;
		}
		return IOCP_ERR;
	}

	if(LOBYTE(wsaData.wVersion) < 2 || HIBYTE(wsaData.wVersion) < 2)//判断版本号，是否和定义的一样
	{
		errMessage="Windows Sockets 的版本低于 2.0";
		WSACleanup();   //若出问题，卸载支持，并结束程序返回-1
		return IOCP_ERR;
	}
	
	// 为回调函数赋值
	OnConnected = fConnected;
	OnClosed = fClosed;
	OnError = fErr;
	OnRecvCompleted = fRecv;
	OnSendCompleted = fSend;
	OnCltFree = fCltFree;

	// 初始化FreePool
	uiData = uiDataLen;
	uiClearTime = uiClearPerSec;
	FreePool_Init(uiData, uiClearTime);

	// 为监听线程生成事件对象，当投递的AcceptEx不够时得到通知
	hAcceptEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	if(!hAcceptEvent)
	{
		int errNo=GetLastError();
		std::stringstream ss;
		ss << "创建事件对象失败！Windows 错误码为" << errNo;
		errMessage=ss.str();
		return IOCP_ERR;
	}

	// 初始化csConn
	::InitializeCriticalSection(&csConn);
	pConn = NULL;
	uiConn = 0;
	//
	::InitializeCriticalSection(&csAccept);

	// 2016.4.21  -  hiquotion
	// 将以下创建完成端口对象的代码，移动到初始化函数中

	// 创建完成端口对象
	hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if(!hCompletion)
	{
		errMessage="创建完成端口失败！";
		return IOCP_ERR;
	}

	return IOCP_OK;
}

int IOCP_Free()
{
	errMessage="";
	
	// 尝试停止服务
	IOCP_Shutdown();
	// 关闭FreePool模块
	FreePool_Free();
	// 释放WinSock库的资源
	::WSACleanup();
	// 关闭事件对象句柄
	::CloseHandle(hAcceptEvent);
	//
	::DeleteCriticalSection(&csConn);
	::DeleteCriticalSection(&csAccept);

	return IOCP_OK;
}

int IOCP_Start(const char *IP, 
			   unsigned short Port,
			   long InitAcceptNumber,
			   unsigned int uiThread,
			   unsigned long KeepAlive)
{
	errMessage="";

	// 检查是否已启动
	if(iStart)
	{
		errMessage="服务已经启动";
		return IOCP_OK;
	}

	// 初始投递的Accept请求数
	lInitAcceptNumber = InitAcceptNumber;
	// 初始化服务绑定的地址信息
	SOCKADDR_IN si = {0};
	si.sin_family = AF_INET;
	si.sin_port = ::ntohs(Port);
	si.sin_addr.S_un.S_addr = ::inet_addr(IP);

	// 生成监听套接字
	sListen = ::WSASocket(AF_INET, 
		SOCK_STREAM, 
		0, 
		NULL, 
		0, 
		WSA_FLAG_OVERLAPPED);

	// KeepAlive
	if(KeepAlive)
	{
		#define SIO_KEEPALIVE_VALS IOC_IN | IOC_VENDOR | 4
		struct
		{
			unsigned long OnOff;
			unsigned long KeepAliveTime;
			unsigned long KeepAliveInterval;
		}ka = {0};
		unsigned long ulRet = 0;
		ka.OnOff = 1;						// 启用KeepAlive
		ka.KeepAliveTime = KeepAlive * 1000;// ms. 超时时间（多少ms检测在线情况）
		ka.KeepAliveInterval = 5000;		// ms. Resend if No-Reply（如果一个KeepAlive包没有响应间隔多少ms发送下一个）
		if(SOCKET_ERROR == ::WSAIoctl(sListen, SIO_KEEPALIVE_VALS, &ka, sizeof(ka), NULL, 0, &ulRet, 0, NULL))
		{
			int errNo=WSAGetLastError();
			std::stringstream ss;
			ss << "为实现 KeepAlive 功能支持时，调用 WSAIoctl 失败！Windows 错误码为 " << errNo;
			errMessage=ss.str();
			std::string errmsg="";
			switch(errNo)
			{
			case WSANOTINITIALISED:
				errmsg="在调用本API之前应成功调用WSAStartup()";
				break;
			case WSAENETDOWN:
				errmsg="网络子系统失效";
				break;
			case WSAEINVAL:
				errmsg="cmd不是一个合法的命令；或者一个输入参数非法；或者命令对于该种类型的套接口不适用";
				break;
			case WSAEINPROGRESS:
				errmsg="在一个回调函数运行时调用了该函数";
				break;
			case WSAENOTSOCK:
				errmsg="描述字不是一个套接口";
				break;
			case WSAEOPNOTSUPP:
				errmsg="指定的ioctl命令无法实现，例如在SIO_SET_QOS或 SIO_SET_GROUP_QOS中指定的流描述无法实现";
				break;
			case WSA_IO_PENDING:
				errmsg="一个重叠操作被成功启动，过后将报告完成情况";
				break;
			case WSAEWOULDBLOCK:
				errmsg="套接口标志为非阻塞，且所需操作将产生阻塞";
				break;
			}
			errMessage+="(" + errmsg + ")";
			::closesocket(sListen);
			sListen = INVALID_SOCKET;
			return IOCP_ERR;
		}
	}

	// 将套接字与本地地址绑定
	if(SOCKET_ERROR == ::bind(sListen, (sockaddr*)&si, sizeof(si)))
	{
		int errNo=WSAGetLastError();
		std::stringstream ss;
		ss << "socket 绑定失败！Windows 错误码为 " << errNo;
		errMessage=ss.str();
		std::string errmsg="";
		switch(errNo)
		{
		case WSANOTINITIALISED:
			errmsg="在使用此API之前应首先成功地调用WSAStartup()";
			break;
		case WSAENETDOWN:
			errmsg="网络子系统失效";
			break;
		case WSAEADDRINUSE:
			errmsg="待绑定端口已在使用中（参见setoption()中的SO_REUSEADDR选项）";
			break;
		case WSAEFAULT:
			errmsg="namelen参数太小（小于sockaddr结构的大小）";
			break;
		case WSAEINPROGRESS:
			errmsg="一个阻塞的套接口调用正在运行中";
			break;
		case WSAEAFNOSUPPORT:
			errmsg="本协议不支持所指定的地址族";
			break;
		case WSAEINVAL:
			errmsg="该套接口已与一个地址捆绑";
			break;
		case WSAENOBUFS:
			errmsg="无足够可用缓冲区，连接过多";
			break;
		case WSAENOTSOCK:
			errmsg="描述字不是一个套接口";
			break;
		}
		errMessage+="(" + errmsg + ")";
		::closesocket(sListen);
		sListen = INVALID_SOCKET;
		return IOCP_ERR;
	}

	// 开始监听
	if(SOCKET_ERROR == ::listen(sListen, SOMAXCONN))
	{
		int errNo=WSAGetLastError();
		std::stringstream ss;
		ss << "socket 监听失败！Windows 错误码为 " << errNo;
		errMessage=ss.str();
		std::string errmsg="";
		switch(errNo)
		{
		case WSANOTINITIALISED:
			errmsg="在使用此API之前应首先成功地调用WSAStartup()";
			break;
		case WSAENETDOWN:
			errmsg="网络子系统失效";
			break;
		case WSAEADDRINUSE:
			errmsg="待绑定端口已在使用中（参见setoption()中的SO_REUSEADDR选项）";
			break;
		case WSAEINPROGRESS:
			errmsg="一个阻塞的套接口调用正在运行中";
			break;
		case WSAEINVAL:
			errmsg="该套接口已与一个地址捆绑";
			break;
		case WSAEISCONN:
			errmsg="套接口已被连接";
			break;
		case WSAEMFILE:
			errmsg="无可用文件描述字";
			break;
		case WSAENOBUFS:
			errmsg="无足够可用缓冲区，连接过多";
			break;
		case WSAENOTSOCK:
			errmsg="描述字不是一个套接口";
			break;
		case WSAEOPNOTSUPP:
			errmsg="调用listen()时，该套接口不正常";
			break;
		}
		errMessage+="(" + errmsg + ")";
		::closesocket(sListen);
		sListen = INVALID_SOCKET;
		return IOCP_ERR;
	}

	// 2016.4.21  -   hiquotion
	// 将以下注释部分，移动到 Init 函数内

// 	// 创建完成端口对象
// 	hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 
// 		0, 
// 		0, 
// 		0);
	if(!hCompletion)
	{
		errMessage="完成端口句柄为空！请先调用 IOCP_INIT 来创建完成端口";
		return IOCP_ERR;
	}

	// 将监听套节字关联到完成端口
	if(!::CreateIoCompletionPort((HANDLE)sListen, hCompletion, (DWORD)0, 0))
	{
		errMessage="调用 CreateIoCompletionPort() 使完成端口和套接字绑定时出现错误！";
		return IOCP_ERR;
	}

	/*
	AcceptEx()被置于Winsock2架构之外，每次调用时它都被迫通过WSAIoctl()取得函数指针
	为了避免对性能的影响，手工调用WSAIoctl来加载AcceptEx和GetAcceptExSockaddrs
	*/
	// 加载AcceptEx
	GUID GuidAcceptEx = WSAID_ACCEPTEX;
	DWORD dwBytes = 0;
	if(SOCKET_ERROR == ::WSAIoctl(sListen, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidAcceptEx, 
		sizeof(GuidAcceptEx), &lpfnAcceptEx, sizeof(lpfnAcceptEx), &dwBytes, NULL, NULL))
	{
		int errNo=WSAGetLastError();
		std::stringstream ss;
		ss << "取 lpfnAcceptEx 函数指针时，调用 WSAIoctl 失败！Windows 错误码为 " << errNo;
		errMessage=ss.str();
		return IOCP_ERR;
	}

	// 加载GetAcceptExSockaddrs
	GUID GuidGetAcceptExSockaddrs = WSAID_GETACCEPTEXSOCKADDRS;
	if(SOCKET_ERROR == ::WSAIoctl(sListen, SIO_GET_EXTENSION_FUNCTION_POINTER, &GuidGetAcceptExSockaddrs,
		sizeof(GuidGetAcceptExSockaddrs), &lpfnGetAcceptExSockaddrs, sizeof(lpfnGetAcceptExSockaddrs), &dwBytes, NULL, NULL))
	{
		int errNo=WSAGetLastError();
		std::stringstream ss;
		ss << "取 lpfnGetAcceptExSockaddrs 函数指针时，调用 WSAIoctl 失败！Windows 错误码为 " << errNo;
		errMessage=ss.str();
		return IOCP_ERR;
	}

	/*
	注册FD_ACCEPT事件，
	如果投递的AcceptEx I/O不够，线程会接收到FD_ACCEPT网络事件，
	说明应该投递更多的AcceptEx I/O
	*/
	if(SOCKET_ERROR == WSAEventSelect(sListen, hAcceptEvent, FD_ACCEPT))
	{
		int errNo=WSAGetLastError();
		std::stringstream ss;
		ss << "为实现“投递的AcceptEx I/O不够的事件通知”时，调用 WSAEventSelect 函数失败！Windows 错误码为 " << errNo;
		errMessage=ss.str();
		return IOCP_ERR;
	}

	// 工作线程数
	uiWorkThread = (uiThread ? uiThread : 4 * uiCPU);
	// 创建监听线程
	hListenThread = ::CreateThread(NULL, 0, ListenThread, 0, 0, NULL);
	if(!hListenThread)
	{
		errMessage="创建监听线程失败！";
		return IOCP_ERR;
	}

	// OK.
	iStart = 1;

	return IOCP_OK;
}

int IOCP_Shutdown()
{
	errMessage="";
	
	if(!iStart)
	{
		return IOCP_OK;
	}
	// 通知监听线程
	iStart = 0;
	::SetEvent(hAcceptEvent);
	// 等待监听线程退出
	::WaitForSingleObject(hListenThread, INFINITE);
	::CloseHandle(hListenThread);
	hListenThread = NULL;

	return IOCP_OK;
}

unsigned int IOCP_GetConnNumber()
{
	errMessage="";
	
	return uiConn;
}

