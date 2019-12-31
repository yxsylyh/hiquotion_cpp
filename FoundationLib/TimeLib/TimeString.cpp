#include "StdAfx.h"
#include "TimeString.h"

CTimeString::CTimeString(void)
{
}

CTimeString::~CTimeString(void)
{
}

CString CTimeString::getCurrentDateTimeString(int type)
{
	CTime time=CTime::GetCurrentTime();
	CString t="";
	switch(type)
	{
	case 0:
		t.Format("%dƒÍ%d‘¬%d»’ %d:%d:%d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
		break;
	case 1:
		t.Format("%d-%d-%d %d:%d:%d",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
		break;
	}
	return t;
}
