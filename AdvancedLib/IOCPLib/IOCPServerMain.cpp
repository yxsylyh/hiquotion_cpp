/*
IOCP Server v1.0
www.ipsky.net
*/

#include "iocpserver.h"
#include <stdio.h>

static CRITICAL_SECTION cs;
#define LOCKCS ::EnterCriticalSection(&cs)
#define UNLOCKCS ::LeaveCriticalSection(&cs)

void OnConnected(Client *pClt)
{
	for(int i=0; i<2; i++)
	{
		if(IOCP_OK != PostRecv(pClt, 0, 4096))
		{
			DisConn(pClt);
		}
	}

	LOCKCS;
	printf("新连接  %s : %d\n", inet_ntoa(pClt->saClient.sin_addr), htons(pClt->saClient.sin_port));
	UNLOCKCS;
}

void OnClosed(Client* pClt, SynIO* pIO)
{
	SIO_Free(pIO);
	LOCKCS;
	printf("OnClosed.\n");
	UNLOCKCS;
}

void OnError(Client* pClt, SynIO* pIO, int iErr)
{
	SIO_Free(pIO);
	LOCKCS;
	printf("OnError.\n");
	UNLOCKCS;
}

void OnRecvCompleted(Client* pClt, SynIO* pIO)
{
	pIO->uiData = pIO->uiTrans;
	if(IOCP_OK != PostSend(pClt, pIO))
	{
		SIO_Free(pIO);
		DisConn(pClt);
	}
	if(IOCP_OK != PostRecv(pClt, 0, 1024))
	{
		DisConn(pClt);
	}
}

void OnSendCompleted(Client* pClt, SynIO* pIO)
{
	SIO_Free(pIO);
}

void OnCltFree(Client *pClt)
{
	LOCKCS;
	printf("完全断开!\n\n");
	UNLOCKCS;
}

void main()
{
	char buf[1024] = {0};

	::InitializeCriticalSection(&cs);
	if(IOCP_OK == IOCP_Init(OnConnected, 
		OnClosed, 
		OnError, 
		OnRecvCompleted, 
		OnSendCompleted,
		OnCltFree))
	{
		if(IOCP_OK == IOCP_Start("0"))
		{
			printf("启动成功.\n");
			while(1)
			{
				gets(buf);
				if(0 == strcmp("exit", buf))
				{
					break;
				}
				extern unsigned int SIO_GetAllocNumber();
				extern unsigned int Clt_GetAllocNumber();
				printf("Con : %d\nSIO : %d\nClt : %d\n", 
					IOCP_GetConnNumber(), 
					SIO_GetAllocNumber(), 
					Clt_GetAllocNumber());
			}
		}
		IOCP_Shutdown();
	}
	::DeleteCriticalSection(&cs);
	IOCP_Free();
	getchar();
	getchar();
	getchar();
}

