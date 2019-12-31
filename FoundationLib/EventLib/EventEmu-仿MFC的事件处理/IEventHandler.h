// IEventHandler.h: interface for the IEventHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IEVENTHANDLER_H__0ECD630B_E5EB_4152_9DEC_18678EF237B5__INCLUDED_)
#define AFX_IEVENTHANDLER_H__0ECD630B_E5EB_4152_9DEC_18678EF237B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IEvent.h"

// 声明 Event_Map 函数，在 .h 文件中
// 放在 pulic 中
#define Declare_Event_Map()			\
	virtual int handleEvent(IEventRaisable *sender, IEvent *e);		

// 开始 Event_Map 函数，在 .cpp 文件中（下同）
#define Begin_Event_Map(Class)		\
	int Class##::handleEvent(IEventRaisable *sender, IEvent *e)		\
	{									\
		int i=0;						\

// 模板类的 handleEvent 方法
#define Begin_Event_Map_With_Type(Class, T)			\
	template <class T>								\
	int Class##<##T##>##::handleEvent(IEventRaisable *sender, IEvent *e)		\
	{												

// Event_Map
// raiser_pointer 是事件触发对象的指针
#define Event_Map(raiser_pointer, eventIdValue, Func)		\
	if(raiser_pointer==sender)								\
	{												\
		if(e->getEventId()!="")						\
		{											\
			if(e->getEventId()==eventIdValue)		\
			{										\
				Func(e);							\
				return 0;							\
			}										\
		}											\
	}

// Event_Map
// raiser_list_obj 是事件触发对象所在的列表对象，列表中存储的是对象指针
#define Event_List_Map(raiser_list_obj, /*list_item_type,*/ eventIdValue, Func)	\
	for(i=0;i<(int)raiser_list_obj.size();i++)			\
	{														\
		IEventRaisable *item=(IEventRaisable *)raiser_list_obj.at(i);	\
		if(!item)		\
			continue;	\
		if(item==sender)								\
		{												\
			if(e->getEventId()!="")						\
			{											\
				if(e->getEventId()==eventIdValue)		\
				{										\
					Func(i, e);							\
					return 0;							\
				}										\
			}											\
		}												\
	}

// Event_Map
// raiser_array_obj 是事件触发对象的数组
#define Event_Array_Map(raiser_array_obj, array_element_count, eventIdValue, Func) \
	for(i=0;i<(int)array_element_count;i++)			\
	{														\
		IEventRaisable *item=(IEventRaisable *)&raiser_array_obj[i];	\
		if(!item)		\
			continue;	\
		if(item==sender)								\
		{												\
			if(e->getEventId()!="")						\
			{											\
				if(e->getEventId()==eventIdValue)		\
				{										\
					Func(i, e);							\
					return 0;							\
				}										\
			}											\
		}												\
	}

// 结束 Event_Map
#define End_Event_Map()								\
	return IEventHandler::handleEvent(sender, e);	\
}													

class IEventHandler  
{
public:
	IEventHandler();
	virtual ~IEventHandler();

	virtual int handleEvent(IEventRaisable *sender, IEvent *e);
};

#endif // !defined(AFX_IEVENTHANDLER_H__0ECD630B_E5EB_4152_9DEC_18678EF237B5__INCLUDED_)
