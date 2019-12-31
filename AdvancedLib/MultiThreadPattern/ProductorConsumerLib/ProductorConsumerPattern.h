// ProductorConsumerPattern.h: interface for the CProductorConsumerPattern class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRODUCTORCONSUMERPATTERN_H__A34DC90B_A53D_4338_89BB_DF80D5EA00C1__INCLUDED_)
#define AFX_PRODUCTORCONSUMERPATTERN_H__A34DC90B_A53D_4338_89BB_DF80D5EA00C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\DataStructLib\PointerList.h>

#define DEFALT_CAPABILITY 128

template<class T>
class CProductorConsumerPattern  
{
public:
	CProductorConsumerPattern()
	{
		m_capacity=DEFALT_CAPABILITY;
		
		//创建信号量
		m_emptySemaphore = CreateSemaphore(NULL, DEFALT_CAPABILITY, DEFALT_CAPABILITY, NULL);//初值为缓冲池大小，最大为缓冲池大小
		m_fullSemaphore = CreateSemaphore(NULL, 0, DEFALT_CAPABILITY, NULL);       //初值为0，最大为缓冲池大小
		m_mutexSemaphore = CreateSemaphore(NULL,1,1,NULL);               //初值为1,最大为1
	}

	CProductorConsumerPattern(int capacity)
	{
		//创建信号量
		if(capacity>0)
		{
			m_capacity=capacity;
			m_emptySemaphore = CreateSemaphore(NULL, capacity, capacity, NULL);//初值为缓冲池大小，最大为缓冲池大小
			m_fullSemaphore = CreateSemaphore(NULL, 0, capacity, NULL);       //初值为0，最大为缓冲池大小
		}
		else
		{
			m_capacity=DEFALT_CAPABILITY;
			
			m_emptySemaphore = CreateSemaphore(NULL, DEFALT_CAPABILITY, DEFALT_CAPABILITY, NULL);//初值为缓冲池大小，最大为缓冲池大小
			m_fullSemaphore = CreateSemaphore(NULL, 0, DEFALT_CAPABILITY, NULL);       //初值为0，最大为缓冲池大小
		}
		
		m_mutexSemaphore = CreateSemaphore(NULL,1,1,NULL);               //初值为1,最大为1
	}

	virtual ~CProductorConsumerPattern()
	{
		CloseHandle(m_emptySemaphore);
		CloseHandle(m_fullSemaphore);
		CloseHandle(m_mutexSemaphore);
	}

	void produce(T product)
	{
		WaitForSingleObject(m_emptySemaphore, INFINITE);//等待同步信号量empty
		
		WaitForSingleObject(m_mutexSemaphore, INFINITE);//等待互斥信号量mutex
		m_products.push_back(product);
#ifdef _DEBUG
		printf("Produced a product.\n");
#endif
		ReleaseSemaphore(m_mutexSemaphore, 1, NULL);//释放互斥信号量mutex
		
		ReleaseSemaphore(m_fullSemaphore, 1, NULL);//释放同步信号量full
	}

	void comsume(T *product)
	{
		WaitForSingleObject(m_fullSemaphore, INFINITE);//等待同步信号量full
		
		WaitForSingleObject(m_mutexSemaphore, INFINITE);//等待互斥信号量mutex
		*product=m_products.front();
		m_products.erase(0);
#ifdef _DEBUG
		printf("Comsumed a product.\n");
#endif
		ReleaseSemaphore(m_mutexSemaphore, 1, NULL);//释放互斥信号量mutex
		
		ReleaseSemaphore(m_emptySemaphore, 1, NULL);//释放信号量
	}

protected:
	//空信号量
	HANDLE m_emptySemaphore;
	//满信号量
	HANDLE m_fullSemaphore;
	//互斥信号量，生产者与生产者互斥，消费者与消费者互斥，生产者与消费者互斥
	HANDLE m_mutexSemaphore;
	// 产品
	CPointerList<T> m_products;

	// 仓库容量
	int m_capacity;
};

#endif // !defined(AFX_PRODUCTORCONSUMERPATTERN_H__A34DC90B_A53D_4338_89BB_DF80D5EA00C1__INCLUDED_)
