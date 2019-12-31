// FtpProgress.cpp: implementation of the CFtpProgress class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FtpProgress.h"
#include "FtpProgressEvent.h"
// #include "include/CkTask.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFtpProgress::CFtpProgress()
: m_fileId(0)
{

}

CFtpProgress::~CFtpProgress()
{

}

void CFtpProgress::PercentDone( int pctDone, bool *abort )
{
	CFtpProgressEvent e(this, "Progress", m_fileId, pctDone);
	Progress.raiseEvent(this, &e);
}

// void CFtpProgress::TaskCompleted( CkTask &task )
// {
// 	IEvent e(this, "Complete");
// 	Complete.raiseEvent(this, &e);
// }
