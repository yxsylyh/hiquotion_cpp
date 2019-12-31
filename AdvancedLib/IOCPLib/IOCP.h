// IOCP.h: interface for the CIOCP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IOCP_H__A0545D7D_A081_40DF_8CE3_8E78AC6222CA__INCLUDED_)
#define AFX_IOCP_H__A0545D7D_A081_40DF_8CE3_8E78AC6222CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BOOL int
#define TRUE 1
#define FALSE 0

void Connected(Client *pClt);
void Closed(Client* pClt, SynIO* pIO);
void Error(Client* pClt, SynIO* pIO, int iErr);
void RecvCompleted(Client* pClt, SynIO* pIO);
void SendCompleted(Client* pClt, SynIO* pIO);
void CltFree(Client *pClt);

class CIOCP  
{
public:
	CIOCP();
	virtual ~CIOCP();

	// 初始化IOCP模块
	BOOL init(unsigned int uiDataLen = 4096,		/*
													除了0之外
													只要投递WSASend/WSARecv，返值为WSA_IO_PENGDING
													系统都会为IO锁定4KB的内存
													所以将IO的缓存区设置为4KB
													*/
			  unsigned int uiClearPerSec = 30		/* 多少s对空闲链表进行一次清理 */
		);

	// 启动IOCP服务器
	BOOL start(unsigned short Port = 15100,			/* 服务端口 */
			long InitAcceptNumber = 30,			/* 初始化投递多少个AcceptEx ，并尽量将最大投递维持在这个范围内 */
			unsigned int uiThread = 0,			/* IOCP的线程数 ， 默认为 4 * CPU */
			unsigned long KeepAlive = 60			/* 多少s检测一次在线情况 : KeepAlive */
		);

	// 停止IOCP服务器
	int IOCP_Shutdown();

	// 释放IOCP模块的资源
	int IOCP_Free();

	// 获取当前的连接数
	unsigned int IOCP_GetConnNumber();

	// 内部事件通知，用于该类内部的处理（比如内部记录日志等），之后会调用相应的外部事件通知
	void InConnected(Client *pClt);
	void InClosed(Client* pClt, SynIO* pIO);
	void InError(Client* pClt, SynIO* pIO, int iErr);
	void InRecvCompleted(Client* pClt, SynIO* pIO);
	void InSendCompleted(Client* pClt, SynIO* pIO);
	void InClientFree(Client *pClt);


	// 外部事件通知，用户子类继承
	virtual void OnConnected(Client *pClt);
	virtual void OnClosed(Client* pClt, SynIO* pIO);
	virtual void OnError(Client* pClt, SynIO* pIO, int iErr);
	virtual void OnRecvCompleted(Client* pClt, SynIO* pIO);
	virtual void OnSendCompleted(Client* pClt, SynIO* pIO);
	virtual void OnClientFree(Client *pClt);

};

#endif // !defined(AFX_IOCP_H__A0545D7D_A081_40DF_8CE3_8E78AC6222CA__INCLUDED_)
