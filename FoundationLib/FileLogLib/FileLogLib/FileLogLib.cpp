// FileLogLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileLogLib.h"
// #include "LogConfig.h"
// #include "LogLevel.h"
// #include "LogBuilder.h"
#include "Log.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CString strHello;
		strHello.LoadString(IDS_HELLO);
		cout << (LPCTSTR)strHello << endl;

		// 测试 CLogConfig 类
// 		CLogConfig config;
// 		bool showTimeBeforeLevel=config.getShowTimeBeforeLevel();
// 		LogLevel fileLogLevel=config.getLogLevel();
// 		string logFileName=config.getLogFileName();
// 		bool logFileNameAddDate=config.getLogFileNameAddDate();
// 		string subFolderName=config.getSubFolderName();
// 		bool fileLogOverwritten=config.getFileLogOverwritten();
// 
// 		if(showTimeBeforeLevel)
// 			printf("显示时间：是\n");
// 		else
// 			printf("显示时间：否\n");
// 		printf("显示时间：%d\n",showTimeBeforeLevel);
// 		printf("日志级别：%s\n",CLogLevel::LogLevel2String(fileLogLevel).c_str());
// 		printf("日志文件名：%s\n",logFileName.c_str());
// 		printf("日志文件名添加日期后缀：%d\n",logFileNameAddDate);
// 		printf("日志目录名：%s\n",subFolderName.c_str());
// 		printf("日志覆写：%d\n\n",fileLogOverwritten);
// 		system("pause");

// 		// 测试 CLogBuilder 类
// 		CLogBuilder logBuilder;
// 		CFileLog *log=logBuilder.getFileLog();
// 		if(!log)
// 			return 1;
// 		log->writeException(1,"Something wrong!(just for test purpose.)","_tmain","CFileLog","FileLogLib");

// 		CLog log;
// 		log.write("haha writing...");
// 		log.writeLn("OK!");
// 		log.writeLn(LOGLEVEL_SHOWDEBUG,"debug message.");
// 		log.writeException(-1,"exception thrown.","main","","FileLogLib");
// 		log.setProjectName("FileLogLib - set project name");
// 		log.writeLogHead();
// 		log.writeException(-1,"after set project name,throw exception","main","");
// 		log.writeInfo("haha","main","");
// 		log.writeWarning("writing warning","main","");
// 		log.writeLogEnd();
	}

	return nRetCode;
}


