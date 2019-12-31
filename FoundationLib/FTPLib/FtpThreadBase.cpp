// FtpThreadBase.cpp: implementation of the CFtpThreadBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FtpThreadBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFtpThreadBase::CFtpThreadBase()
: m_hwnd(NULL), m_port(21), m_connectTimeout(30), m_readTimeout(30), m_ftpFolder("/"), m_isRaiseWndEvent(TRUE), m_retryTimes(RETRY_TIMES)
{
	m_threadType=-1;
}

CFtpThreadBase::~CFtpThreadBase()
{

}
