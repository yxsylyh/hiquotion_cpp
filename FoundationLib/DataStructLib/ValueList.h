#pragma once

#include <vector>

template <class T>
class CValueList : public std::vector<T>
{
public:
	CValueList(void)
	{

	}

	~CValueList(void)
	{
		clear();
	}

	T removeByIndex(int index)
	{
		if(index<0 || index>=size())
			return NULL;

		if(index==0)
		{
			T t=at(0);
			erase(begin());
			return t;
		}

		CValueList<T>::iterator it=begin();
		for(int i=0;i<index;i++)
			it++;

		T t=*it;
		erase(it);
		return t;
	}

	// 传入的参数就是自身，所以没必要再返回了
	void remove(T t)
	{
		if(size()<=0)
			return;

		std::vector<T>::iterator it;
		for(it=begin();it!=end();it++)
		{
			if (*it==t)
			{
				erase(it);
				break;
			}
		}
	}

	BOOL contain(T t)
	{
		if(getIndexOf(t)>=0)
			return TRUE;

		return FALSE;
	}

	int getIndexOf(T t)
	{
		if(size()<=0)
			return -1;

		int i=0;
		std::vector<T>::iterator it;
		for(it=begin();it!=end();it++)
		{
			if (*it==t)
				return i;

			i++;
		}

		return -1;
	}

	// 查找src1中有但src2中没有的元素，添加到diff1中
	static void findDifferent(CValueList<T> &src1, CValueList<T> &src2, CValueList<T> &diff1)
	{
		if(src1.size()==0 || src2.size()==0)
			return;
		
		for(int i=0;i<src1.size();i++)
		{
			if(!src2.contain(src1.at(i)))
				diff1.push_back(src1.at(i));
		}
	}

	// 查找两个列表中的不同的
	// 相当于把src1和src2中相同的元素去掉，
	// src1剩下元素的列表就是diff1，src2剩下元素的列表就是diff2
	static void findDifferent(CValueList<T> &src1, CValueList<T> &src2, CValueList<T> &diff1, CValueList<T> &diff2)
	{
		if(src1.size()==0 && src2.size()==0)
			return;

		findDifferent(src1, src2, diff1);
		findDifferent(src2, src1, diff2);
	}
};
