// BufferLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BufferLib.h"
// #include "CycledBuffer.h"
#include "CycledBufferTest.h"
#include "CycledBufferTest2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

void printData(unsigned int dataLen=0, unsigned int restLen=10, unsigned int startPos=0, unsigned int endPos=0)
{
	printf("data len is %d\nrest len is %d\nstart pos is %d\nend pos is %d\n",dataLen, restLen, startPos, endPos);
}

void printBufferData(char *data, int len)
{
	printf("data is %c", data[0]);
	for(int i=1;i<len;i++)
	{
		printf(",%c", data[i]);
	}
	printf("\n\n");
}

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

// 		CCycledBuffer buffer(10);
// 		char c6[6]={'0','1','2','3','4','5'};
// 		char c4[4]={'6','7','8','9'};
// 		char c5[5]={'6','7','8','9','a'};
// 		char r10[10]={'\0'};
// 
// 		unsigned int bufferLen=10, dataLen=0, restLen=10;
// 		unsigned int startPos=0, endPos=0;
// 
// 		printf("init\n\nbuffer len = %d\n\n", bufferLen);
// 
// 		printf("6,4,0,6\n");
// 		buffer.write(c6, 6);   // 6,4,0,6
// 		printData(buffer.getDataLength(), buffer.getRestLength(), buffer.getStartPosition(), buffer.getEndPosition());
// 		printBufferData(buffer.getCycledBuffer(), bufferLen);
// 
// 		printf("10,0,0,0\n");
// 		buffer.write(c4, 4);   // 10,0,0,0
// 		printData(buffer.getDataLength(), buffer.getRestLength(), buffer.getStartPosition(), buffer.getEndPosition());
// 		printBufferData(buffer.getCycledBuffer(), bufferLen);
// 
// 		printf("7,3,3,0\n");
// 		buffer.read(r10, 3);   // 7,3,3,0
// 		printData(buffer.getDataLength(), buffer.getRestLength(), buffer.getStartPosition(), buffer.getEndPosition());
// 		printBufferData(buffer.getCycledBuffer(), bufferLen);
// 
// 		printf("9,1,3,2\n");
// 		buffer.write(c5, 2);   // 9,1,3,2
// 		printData(buffer.getDataLength(), buffer.getRestLength(), buffer.getStartPosition(), buffer.getEndPosition());
// 		printBufferData(buffer.getCycledBuffer(), bufferLen);
// 
// 		printf("4,6,8,2\n");
// 		buffer.read(r10, 5);   // 4,6,8,2
// 		printData(buffer.getDataLength(), buffer.getRestLength(), buffer.getStartPosition(), buffer.getEndPosition());
// 		printBufferData(buffer.getCycledBuffer(), bufferLen);
// 
// 		printf("2,8,0,2\n");
// 		buffer.read(r10, 2);   // 2,8,0,2
// 		printData(buffer.getDataLength(), buffer.getRestLength(), buffer.getStartPosition(), buffer.getEndPosition());
// 		printBufferData(buffer.getCycledBuffer(), bufferLen);
// 
// 		printf("7,3,0,7\n");
// 		buffer.write(c5, 5);   // 7,3,0,7
// 		printData(buffer.getDataLength(), buffer.getRestLength(), buffer.getStartPosition(), buffer.getEndPosition());
// 		printBufferData(buffer.getCycledBuffer(), bufferLen);
// 	
// 		printf("10,0,0,0\n");
// 		buffer.write(c5, 3);   // 10,0,0,0
// 		printData(buffer.getDataLength(), buffer.getRestLength(), buffer.getStartPosition(), buffer.getEndPosition());
// 		printBufferData(buffer.getCycledBuffer(), bufferLen);
// 		
// 		printf("4,6,6,0\n");
// 		buffer.read(r10, 6);   // 4,6,6,0
// 		printData(buffer.getDataLength(), buffer.getRestLength(), buffer.getStartPosition(), buffer.getEndPosition());
// 		printBufferData(buffer.getCycledBuffer(), bufferLen);
// 		
// 		printf("9,1,6,5\n");
// 		buffer.write(c5, 5);   // 9,1,6,5
// 		printData(buffer.getDataLength(), buffer.getRestLength(), buffer.getStartPosition(), buffer.getEndPosition());
// 		printBufferData(buffer.getCycledBuffer(), bufferLen);
// 		
// 		printf("3,7,2,5\n");
// 		buffer.read(r10, 6);   // 3,7,2,5
// 		printData(buffer.getDataLength(), buffer.getRestLength(), buffer.getStartPosition(), buffer.getEndPosition());
// 		printBufferData(buffer.getCycledBuffer(), bufferLen);

		CCycledBufferTest test;
		test.startTest();
		CCycledBufferTest2 test2;
		test2.startTest();
		system("pause");
		
	}

	return nRetCode;
}


