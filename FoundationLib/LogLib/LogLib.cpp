// LogLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LogLib.h"
#include "LogLibLog.h"
#include "LogConfig.h"
#include "ScreenLog.h"
#include "FileLog.h"
#include "LogList.h"
#include "LogBuilder.h"
#include "Remark.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

CLogLibLog loglibLog;

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
	}

// 	; 是否在每条日志前显示时间
// 	ShowTimeBeforeLevel=
// 	
// 	; 屏幕日志是否创建
// 	CreateScreenLog=
// 	; 设置屏幕日志输出级别
// 	ScreenLogLevel=
// 	
// 	; 文件日志是否创建
// 	CreateFileLog=
// 	; 设置文件日志输出级别
// 	FileLogLevel=
// 	; 日志文件名（不带扩展名，扩展名为.log）
// 	LogFileName=log
// 	; 日志文件名是否加日期后缀
// 	LogFileNameAddDate=
// 	; 可以把日志文件创建的日志放到一个子文件夹中，指定子文件夹名（SubFolderName=），若为空则在同目录内创建文件日志。
// 	SubFolderName=Logs
// 	; 是否覆写（否则为追加内容）
// 	FileLogOverwritten=
	
// 	CLogConfig logConfig;
// 	printf("ShowTimeBeforeLevel=%d\n",logConfig.getShowTimeBeforeLevel());
// 	printf("CreateScreenLog=%d\n",logConfig.getCreateScreenLog());
// 	printf("ScreenLogLevel=%s\n",CLogLevel::LogLevel2String(logConfig.getScreenLogLevel()).c_str());
// 	printf("CreateFileLog=%d\n",logConfig.getCreateFileLog());
// 	printf("FileLogLevel=%s\n",CLogLevel::LogLevel2String(logConfig.getFileLogLevel()).c_str());
// 	printf("LogFileName=%s\n",logConfig.getLogFileName().c_str());
// 	printf("LogFileNameAddDate=%d\n",logConfig.getLogFileNameAddDate());
// 	printf("SubFolderName=%s\n",logConfig.getSubFolderName().c_str());
// 	printf("FileLogOverwritten=%d\n",logConfig.getFileLogOverwritten());

// 	CScreenLog screenLog;
// 	CFileLog fileLog("MyLog.log");
//	CLogList logs;

// 	logs.add((ILog *)&screenLog);
// 	logs.writeLn("仅屏幕输出");
// 	logs.add((ILog *)&fileLog);
// 	logs.writeLn("屏幕和文件都输出");
// 	logs.remove(screenLog.getLogName());
// 	logs.writeLn("仅文件输出");


// 	CLogBuilder logBuilder(&logs,"C:\\");
// 	logs.writeLn("heihei haha hoho!");
// 	logs.writeLn(LOGLEVEL_SHOWINFO,"LOGLEVEL_SHOWINFO");

	CRemark remark;
	remark.doLog(LOGLEVEL_SHOWERROR,"hahahohohehe!");

	system("pause");

	return nRetCode;
}
