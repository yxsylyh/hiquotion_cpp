// StatuteAnalyze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "StatuteAnalyze.h"
//#include "StatuteAnalyzer\StatuteAnalyzer.h"
// #include "StatuteAnalyzer\KernelStatuteAnalyzer.h"
#include "..\KernelLex\KernelLexer\KernelLexer.h"
#include "..\..\..\FoundationLib\FileSysLib\FileOperation.h"
#include "StatuteAnalyzer\StatuteStatusGraphBuilder.h"
#include "StatuteAnalyzer\StatuteAnalyzer.h"

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
		// test1
//		std::string text="Z=>S\r\nS=>E+T\r\nE=>T b\r\nT=>E a\r\nE=>a";  // (need remove space空格 in definition string)
		// test2
//		std::string text="Z=>E\r\nE=>E+T\r\nE=>T\r\nT=>T*F\r\nT=>F\r\nF=>(E)\r\nF=>3\r\nF=>5\r\nF=>2";
		// test3
// 		CFile fileLang;
// // 		fileLang.Open("LangTest.txt", CFile::shareDenyWrite);
// 		fileLang.Open("RegularDef.txt", CFile::shareDenyWrite);
// 		char lang[10240];
// 		int len=fileLang.GetLength();
// 		fileLang.Read(lang, len);
// 		lang[len]='\0';
// 		fileLang.Close();
// 		
// 		CFile fileSrc;
// // 		fileSrc.Open("LangSrcTest.txt", CFile::shareDenyWrite);
// 		fileSrc.Open("Regular.txt", CFile::shareDenyWrite);
// 		char src[10240];
// 		len=fileSrc.GetLength();
// 		fileSrc.Read(src, len);
// 		src[len]='\0';
// 		fileSrc.Close();
// 		
// 		std::string text=lang;
// 
// //			char *a="aab+aa";   // for test1
// //			char *a="3*(5+2)";  // for test2
// 			char *a=src;        // for test from file
// 		int charLen=strlen(a);
// 
// 		CKernelStatuteStatusGraphBuilder kernelBulder;
// 		kernelBulder.setText(text);
// 		int ret=kernelBulder.build();
// 		if(ret!=0)
// 		{
// 			printf("构建内部规约状态图失败。");
// 			system("pause");
// 			return -1;
// 		}
// 
// // 		CKernelStatuteAnalyzer analyzer;
// // 		int ret=analyzer.build(text);
// // 		if(ret!=0)
// // 		{
// // 			printf("语法定义分析失败。");
// // 			system("pause");
// // 			return -1;
// // 		}
// 
// 		CPointerList<MachineToken *> tokenList;
// 		tokenList.setSelfDestroy(TRUE);
// 
// 		string asrc=a;
// 		CKernelLexer lex;
// 		CValueList<string> errlst;
// 		ret=lex.analyze(asrc, tokenList, errlst);
// 		if(ret!=0)
// 		{
// 			stringstream ss;
// 			ss<<"源代码有词法错误！错误码是 " << ret;
// 			printf(ss.str().c_str());
// 			printf("\n");
// 			system("pause");
// 			return -2;
// 		}
// 
// // 		CStdioFile fileToken;
// // 		fileToken.Open("tokens.txt", CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite);
// // 		for(int i=0;i<tokenList.size();i++)
// // 		{
// // 			fileToken.WriteString(tokenList.at(i)->token.c_str());
// // 			fileToken.WriteString("\r\n");
// // 		}
// // 		fileToken.Close();
// 
// 		CStatuteAnalyzer kernelAnalyzer;
// 		kernelAnalyzer.setStatuteStatusGraph(kernelBulder.getStatuteStatusGraph());
// 
// 		CStatuteTreeNode root;
// 		CPointerList<MachineToken *> grammer_errList;
// 		ret=kernelAnalyzer.analyze(tokenList, &root, grammer_errList);
// 		if(ret!=0)
// 		{
// 			stringstream ss;
// 			ss<<"源代码有语法错误！错误码是 " << ret;
// 			printf(ss.str().c_str());
// 			printf("\n");
// 			system("pause");
// 			return -3;
// 		}
// 
// 		printf("源码分析成功！");

		// test4
		CKernelLexer kernelLexer;
		CStatuteStatusGraphBuilder builder;
		int ret=builder.buildStatuteStatusGraphFromDefFile("RegularDef.txt", &kernelLexer);
		if(ret!=0)
		{
			printf("构建内部正则表达式规约状态图失败。\n");
			return -1;
		}

		CFile fileSrc;
// 		fileSrc.Open("LangSrcTest.txt", CFile::shareDenyWrite);
		fileSrc.Open("Regular.txt", CFile::shareDenyWrite);
		char src[10240];
		int len=fileSrc.GetLength();
		fileSrc.Read(src, len);
		src[len]='\0';
		fileSrc.Close();
		
		CPointerList<MachineToken *> tokenList;
		tokenList.setSelfDestroy(TRUE);
		string asrc=src;
		CKernelLexer lex;
		CValueList<string> errlst;
		ret=lex.analyze(asrc, tokenList, errlst);
		if(ret!=0)
		{
			stringstream ss;
			ss<<"源代码有词法错误！错误码是 " << ret;
			printf(ss.str().c_str());
			printf("\n");
			system("pause");
			return -2;
		}

		CStatuteAnalyzer kernelAnalyzer;
		kernelAnalyzer.setStatuteStatusGraph(builder.getStatuteStatusGraph());

		CStatuteTreeNode root;
		CPointerList<MachineToken *> grammer_errList;
		ret=kernelAnalyzer.analyze(tokenList, &root, grammer_errList);
		if(ret!=0)
		{
			stringstream ss;
			ss<<"源代码有语法错误！错误码是 " << ret;
			printf(ss.str().c_str());
			printf("\n");
			system("pause");
			return -3;
		}

		printf("源码分析成功！");
	}

	system("pause");

	return nRetCode;
}


