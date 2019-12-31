#pragma once

#include <map>

template <class S, class T>
class CValueMap : public std::map<S, T>
{
public:
	CValueMap(void){};
	~CValueMap(void)
	{
		clear();
	};

	BOOL contain(S s)
	{
		std::map<S, T>::iterator i;
		i = find(s);
		if(i != end())
			return TRUE;
		else
			return FALSE;
	}

	T get(S s)
	{
		std::map<S, T>::iterator i;
		i = find(s);
		if(i != end())
			return i->second;
		else
			return NULL;
	};

	T getByIndex(int index)
	{
		if(index<0 || index>=(int)size())
			return NULL;

// 		if(index==0)
// 			return begin()->second;

		std::map<S, T>::iterator it=begin();
		for(int i=0;i<index;i++)
			it++;

		return it->second;
	};

	void put(S s, T t)
	{
		insert(std::pair<S, T>(s, t));
	}

	void remove(S s)
	{
		std::map<S, T>::iterator i;
		i = find(s);
		if(i != end())
			erase(i);
	}
};
