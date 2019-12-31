// BoostTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BoostTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <boost/circular_buffer.hpp>   
#include <numeric>   
#include <assert.h>   

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

		// 创建一个环形缓冲区来存放三个int类型的数据   
		boost::circular_buffer<int> cb(3);  

		//插入元素   
		cb.push_back(1);  
		cb.push_back(2);  
		cb.push_back(3);  

		int a = cb[0];  // a == 1   
		int b = cb[1];  // b == 2   
		int c = cb[2];  // c == 3   

		//环形缓冲区现在已经满了，继续插入元素将会覆盖掉最前面的元素   

		cb.push_back(4);  // 用4覆盖了1   
		cb.push_back(5);  // 用5覆盖了2   

		//环形缓冲区现在包含元素 3, 4 和 5.   

		a = cb[0];  // a == 3   
		b = cb[1];  // b == 4   
		c = cb[2];  // c == 5   

		//元素能够被从后面取出也可从前面取出   

		cb.pop_back();  // 5 被取出   
		cb.pop_front(); // 3 被取出   

		int d = cb[0];  // d == 4   

		return 0;  


// 		//创建一个容量为3的环形缓冲区   
// 		boost::circular_buffer<int> cb(3);  
// 		
// 		//插入2个元素进入环形缓冲区   
// 		cb.push_back(1);  
// 		cb.push_back(2);  
// 		
// 		// assertions   
// 		assert(cb[0] == 1);  
// 		assert(cb[1] == 2);  
// 		assert(!cb.full());  
// 		assert(cb.size() == 2);  
// 		assert(cb.capacity() == 3);  
// 		
// 		//再插入2个元素   
// 		cb.push_back(3);  
// 		cb.push_back(4);  
// 		
// 		//计算容器里所有元素之和   
// 		int sum = std::accumulate(cb.begin(), cb.end(), 0);  
// 		
// 		//断言   
// 		assert(cb[0] == 2);  
// 		assert(cb[1] == 3);  
// 		assert(cb[2] == 4);  
// 		assert(*cb.begin() == 2);  
// 		assert(cb.front() == 2);  
// 		assert(cb.back() == 4);  
// 		assert(sum == 9);  
// 		assert(cb.full());  
// 		assert(cb.size() == 3);  
// 		assert(cb.capacity() == 3);  
// 		
// 		return 0;  

	}

	return nRetCode;
}


