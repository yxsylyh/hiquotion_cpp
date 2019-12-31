#pragma once

// #include <vector>
#include "ValueList.h"

template <class T>
class CPointerList : public CValueList<T> // std::vector<T>
{
public:
	CPointerList(void)
	{
		m_isSelfDestroy=FALSE;
	}

	~CPointerList(void)
	{
		if(m_isSelfDestroy)
	 		destroyAll();
		clear();
	}

	void destroyAll()
	{
		for(int i=0;i<(int)size();i++)
		{
			if(at(i))
				delete at(i);
		}
		clear();
	}

	void destroyByIndex(int index)
	{
		if(size()<=0)
			return;

		if(index<0 || index>=size())
			return;

		T t=removeByIndex(index);
		if(t)
			delete t;
	}

	void destroy(T t)
	{
		if(remove(t))
			delete t;
	}

	T remove(T t)
	{
		if(size()<=0)
			return NULL;

		std::vector<T>::iterator it;
		for(it=begin();it!=end();it++)
		{
			if (*it==t)
			{
				erase(it);
				return t;    // 不能写成 *it，因为 *it所代表的 T 对象已经被移除了，*it会变成野指针，不是原来的 *it 了。
				break;
			}
		}

		return NULL;
	}

//	BOOL contain(T t)
//	int getIndexOf(T t)

	// 查找src1中有但src2中没有的元素，添加到diff1中
	static void findDifferent(CPointerList<T> *src1, CPointerList<T> *src2, CPointerList<T> *diff1)
	{
		if(src1->size()==0 || src2->size()==0)
			return;
		
		for(int i=0;i<src1->size();i++)
		{
			if(!src2->contain(src1->at(i)))
				diff1->push_back(src1->at(i));
		}
	}

	// 查找两个列表中的不同的
	// 相当于把src1和src2中相同的元素去掉，
	// src1剩下元素的列表就是diff1，src2剩下元素的列表就是diff2
	static void findDifferent(CPointerList<T> *src1, CPointerList<T> *src2, CPointerList<T> *diff1, CPointerList<T> *diff2)
	{
		if(src1->size()==0 && src2->size()==0)
			return;

		findDifferent(src1, src2, diff1);
		findDifferent(src2, src1, diff2);
	}

	BOOL isSelfDestroy() const { return m_isSelfDestroy; }
	void setSelfDestroy(BOOL val) { m_isSelfDestroy = val; }

protected:
	BOOL m_isSelfDestroy;
};
