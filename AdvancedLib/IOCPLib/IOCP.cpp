// IOCP.cpp: implementation of the CIOCP class.
//
//////////////////////////////////////////////////////////////////////

#include "IOCP.h"

void Connected(Client *pClt)
{
	if(!pClt)
		return;

	CIOCP *iocp=pClt->pExt;
	if(!iocp)
		return;

	iocp->InConnected(pClt);
}

void Closed(Client* pClt, SynIO* pIO)
{
	if(!pClt)
		return;

	if(!pIO)
		return;
	
	CIOCP *iocp=pClt->pExt;
	if(!iocp)
		return;
	
	iocp->InClosed(pClt, pIO);
}

void Error(Client* pClt, SynIO* pIO, int iErr)
{
	if(!pClt)
		return;
	
	if(!pIO)
		return;
	
	CIOCP *iocp=pClt->pExt;
	if(!iocp)
		return;
	
	iocp->InError(pClt, pIO, iErr);
}

void RecvCompleted(Client* pClt, SynIO* pIO)
{
	if(!pClt)
		return;
	
	if(!pIO)
		return;
	
	CIOCP *iocp=pClt->pExt;
	if(!iocp)
		return;
	
	iocp->InRecvCompleted(pClt, pIO);
}

void SendCompleted(Client* pClt, SynIO* pIO)
{
	if(!pClt)
		return;
	
	if(!pIO)
		return;
	
	CIOCP *iocp=pClt->pExt;
	if(!iocp)
		return;
	
	iocp->InSendCompleted(pClt, pIO);
}

void CltFree(Client *pClt)
{
	if(!pClt)
		return;
	
	CIOCP *iocp=pClt->pExt;
	if(!iocp)
		return;
	
	iocp->InClientFree(pClt);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIOCP::CIOCP()
{

}

CIOCP::~CIOCP()
{

}
