// LogList.cpp: implementation of the CLogList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LogList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogList::CLogList()
{

}

CLogList::~CLogList()
{
	logs.clear();
}

void CLogList::write(string logMsg)
{
	list<ILog *>::iterator logi;
	for(logi=logs.begin();logi!=logs.end();logi++)
		(*logi)->write(logMsg);
}

void CLogList::writeLn(string logMsg)
{
	string msg=logMsg+"\n";
	write(msg);
}

void CLogList::write(LogLevel expectedLevel,string logMsg)
{
	list<ILog *>::iterator logi;
	for(logi=logs.begin();logi!=logs.end();logi++)
		(*logi)->write(expectedLevel,logMsg);
}

void CLogList::writeLn(LogLevel expectedLevel,string logMsg)
{
	string msg=logMsg+"\n";
	write(expectedLevel,msg);
}

void CLogList::add(ILog *log)
{
	logs.push_back(log);
}

// int CLogList::remove(string name)
// {
// 	list<ILog *>::iterator logi;
// 	for(logi=logs.begin();logi!=logs.end();logi++)
// 	{
// 		if((*logi)->getLogName()==name)
// 		{
// 			logs.erase(logi);
// 			break;
// 		}
// 	}
// 	return 1;
// }

// void CLogList::debugWrite(string logMsg)
// {
// #ifdef _DEBUG
// 	write(logMsg);
// #endif
// }
// 
// void CLogList::debugWriteLn(string logMsg)
// {
// 	string msg=logMsg+"\n";
// 	debugWrite(msg);
// }
