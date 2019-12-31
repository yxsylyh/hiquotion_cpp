// MovingThread.cpp: implementation of the CMovingThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MovingThread.h"
#include <C++\FoudationLib\MovingLib\MovingInfo.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMovingThread::CMovingThread(float minStep, float frameRate, int maxTotalTime)
: m_poker(NULL), m_pointTo(CPoint(0, 0)), m_minStep(minStep), m_frameRate(frameRate), m_maxTotalTime(maxTotalTime)
{
	
}

CMovingThread::CMovingThread(CPoker *poker, CPoint pointTo, float minStep, float frameRate, int maxTotalTime)
: m_poker(poker), m_pointTo(pointTo), m_minStep(minStep), m_frameRate(frameRate), m_maxTotalTime(maxTotalTime)
{
	
}

CMovingThread::~CMovingThread()
{

}

UINT CMovingThread::threadRun()
{
	if(!m_poker)
	{
		raiseAnimateMovingDone();
		return 0;
	}

	CRect rectFrom=m_poker->getRect();
	int width=rectFrom.Width();
	int height=rectFrom.Height();
	CPoint pointFrom=rectFrom.TopLeft();
// 	float stepx=CMovingInfo::getMovingStep(pointFrom.x, m_pointTo.x, m_frameRate, m_minStep, m_maxTotalTime);
// 	float stepy=CMovingInfo::getMovingStep(pointFrom.y, m_pointTo.y, m_frameRate, m_minStep, m_maxTotalTime);
	float stepx=CMovingInfo::getMovingStep(pointFrom.x, m_pointTo.x, m_frameRate, m_maxTotalTime);
	float stepy=CMovingInfo::getMovingStep(pointFrom.y, m_pointTo.y, m_frameRate, m_maxTotalTime);

	int interval=m_maxTotalTime/m_frameRate;
 	int count=0;
	if(stepx!=0)
	{
		count=abs((int)((m_pointTo.x-pointFrom.x)/stepx));
		stepy=(float)(m_pointTo.y-pointFrom.y)/(float)count;
	}
	else if(stepy!=0)
	{
		count=abs((int)((m_pointTo.y-pointFrom.y)/stepy));
		stepx=(float)(m_pointTo.x-pointFrom.x)/(float)count;
	}
	else
	{
		raiseAnimateMovingDone();
		return 0;
	}

	for(int i=0;i<count;i++)
	{
		int left=pointFrom.x+(int)i*stepx;
		int top=pointFrom.y+int(i*stepy);
		Sleep(interval);
		m_poker->setRect(left, top, left+width, top+height);
		raiseAnimateMovingStep();
	}
	Sleep(interval);
	m_poker->setRect(m_pointTo.x, m_pointTo.y, m_pointTo.x+width, m_pointTo.y+height);
	raiseAnimateMovingStep();

	raiseAnimateMovingDone();
	return 0;
}

void CMovingThread::raiseAnimateMovingStep()
{
	IEvent e(this, "AnimateMovingStep");
	AnimateMovingStep.raiseEvent(this, &e);
}

void CMovingThread::raiseAnimateMovingDone()
{
	IEvent e(this, "AnimateMovingDone");
	AnimateMovingDone.raiseEvent(this, &e);
}
