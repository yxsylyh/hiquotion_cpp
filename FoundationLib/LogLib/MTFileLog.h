#pragma once
#include "filelog.h"

class CMTFileLog :
	public CFileLog
{
public:
	CMTFileLog(string logFile, string extName, BOOL isOverWritten=FALSE,BOOL ShowTimeBeforeLevel=FALSE);
	~CMTFileLog(void);

	void write(LogLevel expectedLevel,string logMsg, DWORD threadID);
	void writeLn(LogLevel expectedLevel,string logMsg, DWORD threadID);

};
