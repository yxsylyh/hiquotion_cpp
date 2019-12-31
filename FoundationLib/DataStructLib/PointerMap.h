#pragma once

// #include <map>
#include "ValueMap.h"

template <class S, class T>
class CPointerMap : public CValueMap<S, T> // std::map<S, T>
{
public:
	CPointerMap(void){};
	~CPointerMap(void)
	{
// 		map<S, T>::iterator i;
// 		for(i = begin(); i != end(); i++)
// 			delete i->second;
		clear();
	};

/*
	T get(S s)
	{
		std::map<S, T>::iterator i;
		i = find(s);
		if(i != end())
			return i->second;
		else
			return NULL;
	};

	T get(int index)
	{
		if(index<0 || index>=size())
			return NULL;

		std::map<S, T>::iterator it=begin();
		for(int i=0;i<index;i++)
			it++;

		return it->second;
	};

	void put(S s, T t)
	{
		insert(std::pair<S, T>(s, t));
	}
*/

	void destroyAll()
	{
		std::map<S, T>::iterator i;
		for(i = begin(); i != end(); i++)
			delete i->second;
	}
};
