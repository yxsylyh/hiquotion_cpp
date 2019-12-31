// CycledBufferTest.h: interface for the CCycledBufferTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CYCLEDBUFFERTEST_H__E085ACCC_4341_4429_969B_4335B7DEDED8__INCLUDED_)
#define AFX_CYCLEDBUFFERTEST_H__E085ACCC_4341_4429_969B_4335B7DEDED8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ISimpleTest.h"
#include "CycledBuffer.h"

class CCycledBufferTest : ISimpleTest<CCycledBuffer>
{
public:
	CCycledBufferTest();
	virtual ~CCycledBufferTest();

// 	// 全局初始化
// 	virtual void globalInit(){};
// 	
// 	// 全局清理
// 	virtual void globalCleanup(){};
	
// 	// 测试用例初始化
// 	virtual T *testCaseInit()
// 	{
// 		return new T();
// 	}
// 	
// 	// 测试用例清理
// 	virtual void testCaseCleanup(T *t)
// 	{
// 		delete t;
// 	}
	
	// 开始测试
	void startTest()
	{
		testcase1();
		testcase2();
		testcase3();
		testcase4();
		testcase5();
		testcase6();
		testcase7();
		testcase8();
		testcase9();
		testcase10();
		testcase11();
	}

	// 缓冲区大小		开始索引	结束索引	数据长度	空标志
	// 初始状态			0			-1			0			是			检查初始状态
	void testcase1()
	{
		printf("testcase1\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		initExpectedData(0, -1, 0, TRUE);
		printRealized(buffer);
		printExpected();
		printCompareResult(buffer);
		testCaseCleanup(buffer);
	}

	// 缓冲区大小		开始索引	结束索引	数据长度	空标志
	// 初始状态			0			-1			0			是			检查从初始状态直接写超
	// 	写入11个元素	0			-1			0			是			返回FALSE
	void testcase2()
	{
		printf("testcase2\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		initExpectedData(0, -1, 0, TRUE);
		printRealized(buffer);
		char a[11];
		BOOL ret=buffer->write(a, 11);
		printf("write result is %d.\n", ret);
		printRealized(buffer);
		printExpected();
		printCompareResult(buffer);
		testCaseCleanup(buffer);
	}

	// 缓冲区大小		开始索引	结束索引	数据长度	空标志
	// 初始状态			0			-1			0			是			检查写满和取空
	// 写入10个元素		0			9			10			否	
	// 读取10个元素		0			9			0			是	
	void testcase3()
	{
		printf("testcase3\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		initExpectedData(0, 9, 0, TRUE);
		printRealized(buffer);
		char a[10];
		buffer->write(a, 10);
		printRealized(buffer);
		buffer->read(a, 10);
		printRealized(buffer);
		printExpected();
		printCompareResult(buffer);
		testCaseCleanup(buffer);
	}

	// 缓冲区大小	开始索引	结束索引	数据长度	空标志
// 	初始状态		0			-1			0			是			检查写满和取空
// 	写入10个元素	0			9			10			否			1,2,3,4,5,6,7,8,9,10
// 	读取10个元素	0			9			0			是			(1,2,3,4,5,6,7,8,9,10)
	void testcase_3()
	{
		printf("testcase_3\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		char exectedRead[10]={1,2,3,4,5,6,7,8,9,10};
		printRealized(buffer);
		char a[10]={1,2,3,4,5,6,7,8,9,10};
		buffer->write(a, 10);
		printRealized(buffer);
		buffer->read(a, 10);
		printRealized(buffer);
		printBufferRead(a, 10);
		printExprectedWithBuffer(exectedRead, 10);
		printCompareResult(buffer);
		printCompareArrayResult(exectedRead,10 , a, 10);
		testCaseCleanup(buffer);

	}

	// 缓冲区大小		开始索引	结束索引	数据长度	空标志
	// 初始状态			0			-1			0			是			检查从头写入，从中间写入，从中间写满（不带循环）
	// 写入3个元素		0			2			3			否	
	// 写入4个元素		0			6			7			否	
	// 写入3个元素		0			9			10			否	
	void testcase4()
	{
		printf("testcase4\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		initExpectedData(0, 9, 10, FALSE);
		printRealized(buffer);
		char a[4];
		buffer->write(a, 3);
		printRealized(buffer);
		buffer->write(a, 4);
		printRealized(buffer);
		buffer->write(a, 3);
		printRealized(buffer);
		printExpected();
		printCompareResult(buffer);
		testCaseCleanup(buffer);
	}

	// 缓冲区大小		开始索引	结束索引	数据长度	空标志
// 	初始状态			0			-1			0			是			检查从头读取，从中间读取，从中间取空（不带循环），取空后再写入（不带循环）
// 	写入7个元素			0			6			7			否	
// 	读取2个元素			2			6			5			否	
// 	读取4个元素			6			6			1			否	
// 	读取1个元素			7			6			0			是	
// 	写入2个元素			7			8			2			否	
// 	写入1个元素			7			9			3			否	
	void testcase5()
	{
		printf("testcase5\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		initExpectedData(7, 9, 3, FALSE);
		printRealized(buffer);
		char a[7];
		buffer->write(a, 7);
		printRealized(buffer);
		buffer->read(a, 2);
		printRealized(buffer);
		buffer->read(a, 4);
		printRealized(buffer);
		buffer->read(a, 1);
		printRealized(buffer);
		buffer->write(a, 2);
		printRealized(buffer);
		buffer->write(a, 1);
		printRealized(buffer);
		printExpected();
		printCompareResult(buffer);
		testCaseCleanup(buffer);
	}

	// 缓冲区大小		开始索引	结束索引	数据长度	空标志
// 	初始状态			7			6			0			是	检查从中间写入到缓冲区尾，再写入（带循环）
// 	写入3个元素			7			9			3			否	
// 	写入5个元素			7			4			8			否	
	void testcase6()
	{
		printf("testcase6\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		initExpectedData(7, 4, 8, FALSE);
		buffer->setStartIndex(7);
		buffer->setEndIndex(6);
		buffer->setEmpty(TRUE);
		printRealized(buffer);
		char a[5];
		buffer->write(a, 3);
		printRealized(buffer);
		buffer->write(a, 5);
		printRealized(buffer);
		printExpected();
		printCompareResult(buffer);
		testCaseCleanup(buffer);
	}

	// 缓冲区大小		开始索引	结束索引	数据长度	空标志
// 	初始状态			7			4			8			否			检查从中间读取，从中间读取到缓冲区尾，再读取（带循环）
// 	读取1个元素			8			4			7			否	
// 	读取2个元素			0			4			5			否	
// 	读取3个元素			3			4			2			否	
	void testcase7()
	{
		printf("testcase7\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		initExpectedData(3, 4, 2, FALSE);
		buffer->setStartIndex(7);
		buffer->setEndIndex(4);
		buffer->setEmpty(FALSE);
		printRealized(buffer);
		char a[3];
		buffer->read(a, 1);
		printRealized(buffer);
		buffer->read(a, 2);
		printRealized(buffer);
		buffer->read(a, 3);
		printRealized(buffer);
		printExpected();
		printCompareResult(buffer);
		testCaseCleanup(buffer);
	}
	
	// 缓冲区大小		开始索引	结束索引	数据长度	空标志
// 	初始状态			7			6			0			是			检查从中间写入（带循环），循环后再写入
// 	写入6个元素			7			2			6			否	
// 	写入2个元素			7			4			2			否	
	void testcase8()
	{
		printf("testcase8\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		initExpectedData(7, 4, 8, FALSE);
		buffer->setStartIndex(7);
		buffer->setEndIndex(6);
		buffer->setEmpty(TRUE);
		printRealized(buffer);
		char a[6];
		buffer->write(a, 6);
		printRealized(buffer);
		buffer->write(a, 2);
		printRealized(buffer);
		printExpected();
		printCompareResult(buffer);
		testCaseCleanup(buffer);
	}
	
	// 缓冲区大小		开始索引	结束索引	数据长度	空标志
// 	初始状态			7			4			8			否			检查从中间读取（带循环），循环后再读取
// 	读取6个元素			3			4			2			否	
// 	读取1个元素			4			4			1			否	
	void testcase9()
	{
		printf("testcase9\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		initExpectedData(4, 4, 1, FALSE);
		buffer->setStartIndex(7);
		buffer->setEndIndex(4);
		buffer->setEmpty(FALSE);
		printRealized(buffer);
		char a[6];
		buffer->read(a, 6);
		printRealized(buffer);
		buffer->read(a, 1);
		printRealized(buffer);
		printExpected();
		printCompareResult(buffer);
		testCaseCleanup(buffer);
	}
	
	// 缓冲区大小		开始索引	结束索引	数据长度	空标志
// 	初始状态			7			6			0			是			检查从中间写满（带循环），从中间取空（带循环）
// 	写入10个元素		7			6			10			否	
// 	读取10个元素		7			6			0			是	
	void testcase10()
	{
		printf("testcase10\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		initExpectedData(7, 6, 0, TRUE);
		buffer->setStartIndex(7);
		buffer->setEndIndex(6);
		buffer->setEmpty(TRUE);
		printRealized(buffer);
		char a[10];
		buffer->write(a, 10);
		printRealized(buffer);
		buffer->read(a, 10);
		printRealized(buffer);
		printExpected();
		printCompareResult(buffer);
		testCaseCleanup(buffer);
	}
	
	// 缓冲区大小		开始索引	结束索引	数据长度	空标志
// 	初始状态			7			2			6			否			检查从中间写满（带循环，之前有数据），从中间取空（带循环）
// 	写入4个元素			7			6			10			否	
// 	读取10个元素		7			6			0			是	
	void testcase11()
	{
		printf("testcase11\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		initExpectedData(7, 6, 0, TRUE);
		buffer->setStartIndex(7);
		buffer->setEndIndex(2);
		buffer->setEmpty(FALSE);
		printRealized(buffer);
		char a[10];
		buffer->write(a, 4);
		printRealized(buffer);
		buffer->read(a, 10);
		printRealized(buffer);
		printExpected();
		printCompareResult(buffer);
		testCaseCleanup(buffer);
	}
	
protected:
	void initExpectedData(int startIndex, int endIndex, int dataLength, BOOL isEmpty)
	{
		m_startIndex=startIndex;
		m_endIndex=endIndex;
		m_dataLength=dataLength;
		m_isEmpty=isEmpty;
	}

	void printCompareResult(CCycledBuffer *buffer)
	{
		if(compare(buffer))
			printf("index check OK!\n");
		else
			printf("----------------------------------- Oh! No! buffer index error!\n");
	}

	void printCompareBufferResult(CCycledBuffer *buffer, char *arr, int len)
	{
		int ret=compareWithBuffer(buffer, arr, len);
		if(ret==0)
		{
			printf("OK!\n");
			return;
		}

		if(ret==-1)
			printf("----------------------------------- Oh! No! buffer len different with array!\n");
		else if(ret==-2)
			printf("----------------------------------- Oh! No! buffer data different with array!\n");
	}

	void printCompareArrayResult(char *arr1, int len1, char *arr2, int len2)
	{
		int ret=compareWithArray(arr1, len1, arr2, len2);
		if(ret==0)
		{
			printf("OK!\n");
			return;
		}
		
		if(ret==-1)
			printf("----------------------------------- Oh! No! buffer len different with array!\n");
		else if(ret==-2)
			printf("----------------------------------- Oh! No! buffer data different with array!\n");
	}

	BOOL compare(CCycledBuffer *buffer)
	{
		return compare(buffer, m_startIndex, m_endIndex, m_dataLength, m_isEmpty);
	}

	BOOL compare(CCycledBuffer *buffer, int startIndex, int endIndex, int dataLength, BOOL isEmpty)
	{
		if(buffer->getStartIndex()==startIndex && buffer->getEndIndex()==endIndex 
			&& buffer->getDataLength()==dataLength && buffer->isEmpty()==isEmpty)
			return TRUE;
		else
			return FALSE;
	}

	int compareWithBuffer(CCycledBuffer *buffer, char *arr, int len)
	{
		if(len!=buffer->getDataLength())
			return -1;

		if(!checkArray(buffer->getCycledBuffer()+m_startIndex, arr, len))
			return -2;

		return 0;
	}

	int compareWithArray(char *arr1, int len1, char *arr2, int len2)
	{
		if(len1!=len2)
			return -1;

		if(!checkArray(arr1, arr2, len2))
			return -2;

		return 0;
	}

	void printExpected()
	{
		printf("期望值--");
		printStatus(m_startIndex, m_endIndex, m_dataLength, m_isEmpty);
	}
	
	void printExprectedWithBuffer(char *arr, int len)
	{
		printExpected();
		printf("期望数据--");
		printBuffer(arr, len);
	}

	void printRealized(CCycledBuffer *buffer)
	{
		printf("实际值--");
		printStatus(buffer->getStartIndex(), buffer->getEndIndex(), buffer->getDataLength(), buffer->isEmpty());
		printf("数据--");
		printBufferData(buffer);
	}

	void printStatus(int startIndex, int endIndex, int dataLength, BOOL isEmpty)
	{
		printf("start:%d\tend:%d\tdata len:%d\tis empty:%d\n", startIndex, endIndex, dataLength, isEmpty);
	}

	void printBufferData(CCycledBuffer *buffer)
	{
		CString msg="",tmp="";
		if(buffer->getBufferLength()<0)
		{
			printf("No data.");
			return;
		}
		msg.Format("%d",buffer->getBufferData(0));

		for(int i=1;i<buffer->getDataLength();i++)
		{
			tmp.Format("%d", buffer->getBufferData(i));
			msg+=","+tmp;
		}
		printf("%s\n", (LPTSTR)(LPCSTR)msg);
	}

	void printBufferRead(char *arr, int len)
	{
		printf("buffer read:");
		if(len<0)
		{
			printf("buffer read len <0!");
			return;
		}
		printBuffer(arr, len);
	}

	void printBuffer(char *arr, int len)
	{
		if(len<0)
		{
			printf("No data.");
			return;
		}

		CString msg="",tmp="";
		msg.Format("%d",arr[0]);
		
		for(int i=1;i<len;i++)
		{
			tmp.Format("%d", arr[i]);
			msg+=","+tmp;
		}
		printf("%s\n", (LPTSTR)(LPCSTR)msg);

	}

	BOOL checkArray(char *arr1, char *arr2, int len)
	{
		if(len<=0)
			return FALSE;

		for(int i=0;i<len;i++)
		{
			if(arr1[i]!=arr2[i])
				return FALSE;
		}

		return TRUE;
	}
	
private:
	int m_startIndex;
	int m_endIndex;
	int m_dataLength;
	BOOL m_isEmpty;
};

#endif // !defined(AFX_CYCLEDBUFFERTEST_H__E085ACCC_4341_4429_969B_4335B7DEDED8__INCLUDED_)
