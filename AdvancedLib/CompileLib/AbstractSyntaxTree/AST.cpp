// AST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AST.h"

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
// 		CCppConverter converter;
// 		CPointerList<CAbstractSyntaxTreeNode *> astCenteces;
//  		ret=converter.convertST2AST(&root, astCenteces);
// 		if(ret!=0)
// 		{
// 			stringstream ss;
// 			ss<<"×ª»»³éÏóÊ÷Ê§°Ü£¡´íÎóÂëÊÇ " << ret;
// 			printf(ss.str().c_str());
// 			printf("\n");
// 			system("pause");
// 			return -4;
// 		}
// 
// 		CAbstractSyntaxTreeNode astRoot;
// 		for(int i=0;i<astCenteces.size();i++)
// 		{
// 			astRoot.addChild(astCenteces.at(i));
// 		}
// 		std::string filename="ast.txt";
// 		if(CFileOperation::isFileExist(filename.c_str()))
// 			DeleteFile(filename.c_str());
// 
// 		std::string info=astRoot.getTreeNodeInfo();
// 		CStdioFile astFile;
// 		if(!astFile.Open("ast.txt", CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
// 		{
// 			printf("create ast.txt failed.\n");
// 			system("pause");
// 			return -5;
// 		}
// 
// 		astFile.WriteString(info.data());
// 		astFile.Close();
	}

	return nRetCode;
}


