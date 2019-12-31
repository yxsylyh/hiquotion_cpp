/*
IOCP Server v1.0
www.ipsky.net
*/

#include "iocpserver.h"

/************************************************************************/
/*                          全局变量                                    */
/************************************************************************/
static unsigned int uiClearPer;	/*清除空闲链表之间的两次时间间隔 s*/

static CRITICAL_SECTION csSIO;	/*同步对SIO的操作*/
static SynIO *pFreeSIO;			/*空闲SIO链表*/
static unsigned int uiData;		/*SIO中数据区的大小*/
static unsigned int uiFreeSIO;	/*空闲SIO链表中元素的数量*/
static unsigned int uiSIOTime;	/*下一次清理空闲链表的时间*/
static long uiAllocIO;			/*已分配出去的SIO数量*/

static CRITICAL_SECTION csClt;
static Client *pFreeClt;
static unsigned int uiFreeClt;
static unsigned int uiCltTime;
static long uiAllocClt;

/************************************************************************/
/*                             宏                                       */
/************************************************************************/
#define IOLock() ::EnterCriticalSection(&csSIO)
#define IOUnLock() ::LeaveCriticalSection(&csSIO)
#define CltLock() ::EnterCriticalSection(&csClt)
#define CltUnLock() ::LeaveCriticalSection(&csClt)

/************************************************************************/
/*                     空闲池的初始化与释放                             */
/************************************************************************/
/*
uiDataLen		数据区的长度
				（1）可能直接使用 IOCP FreePool 模块的内存进行收发
				（2）如果uiDataLen为0则表示缓存区由用户（非模块内置）提供
uiClearPerSec	两次清空空闲链表的时间间隔
				清除操作仅在 Xxx_Free 时执行
*/
void FreePool_Init(unsigned int uiDataLen,
				   unsigned int uiClearPerSec)
{
	// 清理周期，每隔 uiClearPer ms 释放一半的缓存
	uiClearPer = uiClearPerSec * 1000;
	// 初始化 I/O 缓存
	::InitializeCriticalSection(&csSIO);
	pFreeSIO = NULL;
	uiData = uiDataLen;
	uiFreeSIO = 0;
	uiSIOTime = ::GetTickCount() + uiClearPer;
	uiAllocIO = 0;
	// 初始化 Clt 缓存
	::InitializeCriticalSection(&csClt);
	pFreeClt = NULL;
	uiFreeClt = 0;
	uiCltTime = ::GetTickCount() + uiClearPer;
	uiAllocClt = 0;
}

void FreePool_Free()
{
	// 删除临界区
	::DeleteCriticalSection(&csSIO);
	::DeleteCriticalSection(&csClt);
	// 释放所有的空闲项
	for(SynIO *pIO = pFreeSIO, *pNextIO; pIO; )
	{
		pNextIO = pIO->pNext;
		MemFree(pIO);
		pIO = pNextIO;
	}
	for(Client *pClt = pFreeClt, *pNextClt; pClt; )
	{
		pNextClt = pClt->pNext;
		MemFree(pClt);
		pClt = pNextClt;
	}
}

void FreePool_Clear()
{
	SynIO *pIO;
	Client *pClt;
	unsigned int ui;

	IOLock();
	// 如果已到达清理周期
	if(::GetTickCount() > uiSIOTime)
	{
		// 去除一半的空闲项
		ui = uiFreeSIO >> 1;
		uiFreeSIO -= ui;
		// 重置计时器
		uiSIOTime = GetTickCount() + uiClearPer;
		// 将待清理的表项从链表中移除
		while(pFreeSIO && ui--)
		{
			pIO = pFreeSIO;
			pFreeSIO = pFreeSIO->pNext;
			MemFree(pIO);
		}
	}
	IOUnLock();
	CltLock();
	if(::GetTickCount() > uiCltTime)
	{
		ui = uiFreeClt >> 1;
		uiFreeClt -= ui;
		uiCltTime = GetTickCount() + uiClearPer;
		while(pFreeClt && ui--)
		{
			pClt = pFreeClt;
			pFreeClt = pFreeClt->pNext;
			MemFree(pClt);
		}
	}
	CltUnLock();
}

/************************************************************************/
/*                                 SIO                                  */
/************************************************************************/
/*
分配一个可用的SynIO
如果空闲链表非空则直接取出一个可用的SIO
否则生成新的SIO
*/
SynIO* SIO_Alloc()
{
	SynIO *pIO = NULL;

	// 如果空闲链表非空直接从空闲表中取出第一个
	IOLock();
	if(pIO = pFreeSIO)
	{
		pFreeSIO = pFreeSIO->pNext;
	}
	IOUnLock();
	// 空闲表没有可用的SIO，生成新的
	if(pIO || 
		(pIO = (SynIO*)MemAlloc(sizeof(SynIO) + uiData)))
	{
		memset(pIO, 0, sizeof(SynIO));
		pIO->pData = pIO->Data;
		pIO->uiData = uiData;
		pIO->sSocket = INVALID_SOCKET;
		::InterlockedIncrement(&uiAllocIO);
	}

	return pIO;
}
/*
释放一个SIO
如果到达清理时间则释放 uiFreeSIO/2 的空闲表项
*/
void SIO_Free(SynIO* pIO)
{
	IOLock();
	// 将SIO插入链表中
	pIO->pNext = pFreeSIO;
	pFreeSIO = pIO;
	uiFreeSIO++;
	IOUnLock();
	::InterlockedDecrement(&uiAllocIO);
}

/*
获取当前已分配出去的SIO
AllocNumber = SIO_Alloc的调用次数 - SIO_Free的调用次数
*/
unsigned int SIO_GetAllocNumber() { return uiAllocIO; }

/************************************************************************/
/*                               Client                                 */
/************************************************************************/
Client* Clt_Alloc(SOCKET sSocket)
{
	Client *pClt = NULL;

	CltLock();
	if(pClt = pFreeClt)
	{
		pFreeClt = pFreeClt->pNext;
	}
	CltUnLock();

	if(NULL == pClt && 
		(pClt = (Client*)MemAlloc(sizeof(Client))))
	{
		::InitializeCriticalSection(&pClt->csLock);
	}
	if(pClt)
	{
		CRITICAL_SECTION cs = pClt->csLock;
		memset(pClt, 0, sizeof(Client));
		pClt->csLock = cs;
		pClt->iState = CLT_CONN;
		pClt->sClient = sSocket;
		::InterlockedIncrement(&uiAllocClt);
	}
	
	return pClt;
}

void Clt_Free(Client *pClt)
{
	CltLock();
	pClt->pNext = pFreeClt;
	pClt->iState = CLT_FREE;
	pFreeClt = pClt;
	uiFreeClt++;
	CltUnLock();
	::InterlockedDecrement(&uiAllocClt);
}

unsigned int Clt_GetAllocNumber() { return uiAllocClt; }
