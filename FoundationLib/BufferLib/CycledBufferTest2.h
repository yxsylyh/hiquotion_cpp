// CycledBufferTest2.h: interface for the CCycledBufferTest2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CYCLEDBUFFERTEST2_H__20F7A6F1_828A_4981_BD17_C40F789ED77D__INCLUDED_)
#define AFX_CYCLEDBUFFERTEST2_H__20F7A6F1_828A_4981_BD17_C40F789ED77D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ISimpleTest.h"
#include "CycledBuffer.h"

class CCycledBufferTest2 : ISimpleTest<CCycledBuffer>
{
public:
	CCycledBufferTest2();
	virtual ~CCycledBufferTest2();

	// 开始测试
	void startTest()
	{
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

// 	3	初始状态		0	-1	0	是	检查写满和取空
// 		写入10个元素	0	9	10	否	1,2,3,4,5,6,7,8,9,10
// 		读取10个元素	0	9	0	是	(1,2,3,4,5,6,7,8,9,10)
	void testcase3()
	{
		printf("testcase3\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);

// 		写入10个元素
		char data[10]={1,2,3,4,5,6,7,8,9,10};
		printBufferData("data to write is:", data, 10);

		buffer->write(data, 10);

		char dataContent[10];
		int dataLength=0;
		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=10)
		{
			printFailed("buffer content data length is not equals to 10!");
			return;
		}

		printBufferData("data written is:", dataContent, dataLength);
		if(!compareBufferData(data, dataContent, 10))
		{
			printFailed("data content is not same with written!");
			return;
		}

// 		读取10个元素
		char dataRead[10];
		buffer->read(dataRead, 10);

		printBufferData("data read is:", dataRead, 10);

		char dataReadExpected[10]={1,2,3,4,5,6,7,8,9,10};
		if(compareBufferData(dataRead, dataReadExpected, 10))
			printOK();
		else
			printFailed("data read is not same with data expected!");

		testCaseCleanup(buffer);
	}

// 	4	初始状态	0	-1	0	是	检查从头写入，从中间写入，从中间写满（不带循环）
// 		写入3个元素	0	2	3	否	1,2,3
// 		写入4个元素	0	6	7	否	1,2,3,4,5,6,7
// 		写入3个元素	0	9	10	否	1,2,3,4,5,6,7,8,9,10
	void testcase4()
	{
		printf("testcase4\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		
// 		写入3个元素
		char data[3]={1,2,3};
		char data2[4]={4,5,6,7};
		char data3[3]={8,9,10};

		buffer->write(data, 3);
		buffer->write(data2, 4);
		buffer->write(data3, 3);

		char dataContent[10];
		int dataLength=0;
		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=10)
		{
			printFailed("buffer content data length is not equals to 10!");
			return;
		}

		printBufferData("data written is:", dataContent, dataLength);

		char dataExpected[10]={1,2,3,4,5,6,7,8,9,10};
		if(compareBufferData(dataContent, dataExpected, 10))
			printOK();
		else
			printFailed("data read is not same with data expected!");

		testCaseCleanup(buffer);
}
	
// 	5	初始状态	0	-1	0	是	检查从头读取，从中间读取，从中间取空（不带循环），取空后再写入（不带循环）
// 		写入7个元素	0	6	7	否	1,2,3,4,5,6,7
// 		读取2个元素	2	6	5	否	3,4,5,6,7(1,2)
// 		读取4个元素	6	6	1	否	7(3,4,5,6)
// 		读取1个元素	7	6	0	是	(7)
// 		写入2个元素	7	8	2	否	8,9
// 		写入1个元素	7	9	3	否	8,9,10
	void testcase5()
	{
		printf("testcase5\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		
// 		写入7个元素
		char a[7]={1,2,3,4,5,6,7};
		buffer->write(a, 7);
// 		读取2个元素
		char read1[2];
		buffer->read(read1, 2);
		char read1Expected[2]={1,2};
		if(!compareBufferData(read1, read1Expected, 2))
		{
			printFailed("data read 2 bytes is not same with expected!");
			return;
		}

// 		读取4个元素
		char read2[4];
		buffer->read(read2, 4);
		char read2Expected[4]={3,4,5,6};
		if(!compareBufferData(read2, read2Expected, 4))
		{
			printFailed("data read 4 bytes is not same with expected!");
			return;
		}

// 		读取1个元素
		char read3[1];
		buffer->read(read3, 1);
		char read3Expected[1]={7};
		if(!compareBufferData(read3, read3Expected, 1))
		{
			printFailed("data read 1 bytes is not same with expected!");
			return;
		}

		char write1[2]={8,9};
		buffer->write(write1, 2);
		char content1[10];
		int dataLength=0;
		
		getCycledBufferContent(buffer, content1, &dataLength);
		if(dataLength!=2)
		{
			printFailed("data content length is not equals to 2!");
			return;
		}

		if(!compareBufferData(content1, write1, 2))
		{
			printFailed("data content is not same with data expected!");
			return;
		}

		char write2[1]={10};
		buffer->write(write2, 1);
		char content2[10];

		getCycledBufferContent(buffer, content2, &dataLength);
		if(dataLength!=3)
		{
			printFailed("data content length is not equals to 3!");
			return;
		}
		
		char dataExpected[3]={8,9,10};
		if(compareBufferData(content2, dataExpected, 3))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}
	
// 	6	初始状态	7	6	0	是	检查从中间写入到缓冲区尾，再写入（带循环）
// 		写入3个元素	7	9	3	否	1,2,3
// 		写入5个元素	7	4	8	否	1,2,3,4,5,6,7,8
	void testcase6()
	{
		printf("testcase6\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);

		buffer->setStartIndex(7);
		buffer->setEndIndex(6);
		buffer->setEmpty(TRUE);

		char data[3]={1,2,3};
		buffer->write(data, 3);

		char data2[5]={4,5,6,7,8};
		buffer->write(data2, 5);

		char dataContent[10];
		int dataLength=0;

		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=8)
		{
			printFailed("data content length is not equals to 8!");
			return;
		}

		char dataExpected[8]={1,2,3,4,5,6,7,8};
		if(compareBufferData(dataContent, dataExpected, 8))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}
	
// 	7	初始状态	7	4	8	否	检查从中间读取，从中间读取到缓冲区尾，再读取（带循环）
// 									1,2,3,4,5,6,7,8
// 		读取1个元素	8	4	7	否	2,3,4,5,6,7,8(1)
// 		读取2个元素	0	4	5	否	4,5,6,7,8(2,3)
// 		读取3个元素	3	4	2	否	7,8(4,5,6)
	void testcase7()
	{
		printf("testcase7\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);

		char initData[8]={1,2,3,4,5,6,7,8};
		initCycledBuffer(buffer, 7, 4, initData);

		char read1[1];
		buffer->read(read1, 1);

		char read1Expected[1]={1};
		if(!compareBufferData(read1, read1Expected, 1))
		{
			printFailed("data read is not same with expected!");
			return;
		}

		char read2[2];
		buffer->read(read2, 2);

		char read2Expected[2]={2,3};
		if(!compareBufferData(read2, read2Expected, 2))
		{
			printFailed("data read is not same with expected!");
			return;
		}
		
		char read3[3];
		buffer->read(read3, 3);
		
		char read3Expected[3]={4,5,6};
		if(!compareBufferData(read3, read3Expected, 3))
		{
			printFailed("data read is not same with expected!");
			return;
		}
		
		char dataContent[10];
		int dataLength=0;
		
		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=2)
		{
			printFailed("data content length is not equals to 2!");
			return;
		}
		
		char dataExpected[2]={7,8};
		if(compareBufferData(dataContent, dataExpected, 2))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}
	
// 	8	初始状态	7	6	0	是	检查从中间写入（带循环），循环后再写入
// 		写入6个元素	7	2	6	否	1,2,3,4,5,6
// 		写入2个元素	7	4	8	否	1,2,3,4,5,6,7,8
	void testcase8()
	{
		printf("testcase8\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);

		buffer->setStartIndex(7);
		buffer->setEndIndex(6);
		buffer->setEmpty(TRUE);

		char data1[6]={1,2,3,4,5,6};
		buffer->write(data1, 6);

		char dataContent[10];
		int dataLength=0;

		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=6)
		{
			printFailed("data content length is not equals to 6!");
			return;
		}
		
		if(!compareBufferData(data1, dataContent, 6))
		{
			printFailed("data content is not same with expected!");
			return;
		}

		char data2[2]={7,8};
		buffer->write(data2, 2);
		
		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=8)
		{
			printFailed("data content length is not equals to 8!");
			return;
		}

		char dataExpected[8]={1,2,3,4,5,6,7,8};
		if(compareBufferData(dataContent, dataExpected, 8))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}
	
// 	9	初始状态	7	4	8	否	检查从中间读取（带循环），循环后再读取
// 									1,2,3,4,5,6,7,8
// 		读取6个元素	3	4	2	否	7,8(1,2,3,4,5,6)
// 		读取1个元素	4	4	1	否	8(7)
	void testcase9()
	{
		printf("testcase9\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);

		buffer->setStartIndex(7);
		buffer->setEndIndex(4);
		buffer->setEmpty(FALSE);

		char data[8]={1,2,3,4,5,6,7,8};
		initCycledBuffer(buffer, 7, 4, data);

		char read1[6];
		buffer->read(read1, 6);

		char read1Expected[6]={1,2,3,4,5,6};
		if(!compareBufferData(read1, read1Expected, 6))
		{
			printFailed("data read is not same with expected!");
			return;
		}

		char read2[1];
		buffer->read(read2, 1);
		
		char read2Expected[1]={7};
		if(!compareBufferData(read2, read2Expected, 1))
		{
			printFailed("data read is not same with expected!");
			return;
		}

		char dataContent[10];
		int dataLength=0;
		
		getCycledBufferContent(buffer, dataContent, &dataLength);
		if(dataLength!=1)
		{
			printFailed("data content length is not equals to 1!");
			return;
		}
		
		char dataExpected[1]={8};
		if(compareBufferData(dataContent, dataExpected, 1))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}
	
// 	10	初始状态		7	6	0	是	检查从中间写满（带循环），从中间取空（带循环）
// 		写入10个元素	7	6	10	否	1,2,3,4,5,6,7,8,9,10
// 		读取10个元素	7	6	0	是	(1,2,3,4,5,6,7,8,9,10)
	void testcase10()
	{
		printf("testcase10\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);

		char data[10]={1,2,3,4,5,6,7,8,9,10};
		initCycledBuffer(buffer, 7, 6, data);

		char read[10];
		buffer->read(read, 10);

		if(compareBufferData(read, data, 1))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}
	
// 	11	初始状态	7	2	6	否	检查从中间写满（带循环，之前有数据），从中间取空（带循环）
// 									1,2,3,4,5,6
// 		写入4个元素	7	6	10	否	1,2,3,4,5,6,7,8,9,10
// 		读取10个元素	7	6	0	是	(1,2,3,4,5,6,7,8,9,10)
	void testcase11()
	{
		printf("testcase11\n");
		CCycledBuffer *buffer=testCaseInit();
		buffer->redimLength(10);
		
		char data[6]={1,2,3,4,5,6};
		initCycledBuffer(buffer, 7, 2, data);

		char data2[4]={7,8,9,10};
		buffer->write(data2, 4);

		char read[10];
		buffer->read(read, 10);

		char readExpected[10]={1,2,3,4,5,6,7,8,9,10};

		if(compareBufferData(read, readExpected, 10))
			printOK();
		else
			printFailed("data read is not same with data expected!");
		
		testCaseCleanup(buffer);
	}

	void printOK()
	{
		printf("--------------------------------------  OK!\n");
	}

	void printFailed(char *msg)
	{
		printf("%s \t -------- \t  Oh!No!\n", msg);
	}
	
	// 初始化CycledBuffer的数据、起始位置和结束位置
	void initCycledBuffer(CCycledBuffer *buffer, int startIndex, int endIndex, char *data)
	{
		int i=startIndex;
		int dataIndex=0;
		while(i!=endIndex)
		{
			buffer->setBufferData(i, data[dataIndex]);
			i=(i+1)%buffer->getBufferLength();
			dataIndex++;
		}
		buffer->setBufferData(endIndex, data[dataIndex]);

		buffer->setStartIndex(startIndex);
		buffer->setEndIndex(endIndex);
		buffer->setEmpty(FALSE);
	}

	void getCycledBufferContent(CCycledBuffer *buffer, char *data, int *dataLength)
	{
		int i=buffer->getStartIndex();
		int dataIndex=0;
		while(i!=buffer->getEndIndex())
		{
			data[dataIndex]=buffer->getBufferData(i);
			i=(i+1)%buffer->getBufferLength();
			dataIndex++;
		}
		data[dataIndex]=buffer->getBufferData(buffer->getEndIndex());

		*dataLength=dataIndex+1;
	}

	BOOL compareBufferData(char *arr1, char *arr2, int len)
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
	
	void printBufferData(char *msg, char *arr, int len)
	{
		if(len<=0)
		{
			printf("No data.");
			return;
		}

		if(msg)
			printf("%s", msg);
		
		CString display="",tmp="";
		display.Format("%d",arr[0]);
		
		for(int i=1;i<len;i++)
		{
			tmp.Format("%d", arr[i]);
			display+=","+tmp;
		}
		printf("%s\n", (LPTSTR)(LPCSTR)display);
		
	}
};

#endif // !defined(AFX_CYCLEDBUFFERTEST2_H__20F7A6F1_828A_4981_BD17_C40F789ED77D__INCLUDED_)
