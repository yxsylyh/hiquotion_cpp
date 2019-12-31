// IInterfaceManager.h: interface for the IInterfaceManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IUNKOWN_H__EF8D39E7_DAA3_4FB6_9963_5E254EA6159E__INCLUDED_)
#define AFX_IUNKOWN_H__EF8D39E7_DAA3_4FB6_9963_5E254EA6159E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include "IInterface.h"

/*
  针对每个dll，调用getInterfce获取IInterfaceManager*接口类
  调用IInterfaceManager*接口类的queryInterface获取预定义的接口类IInterface*

  queryInterface返回IInterface子类，具体返回哪个IInterface子类，由IInterfaceManager的子类决定

*/

class IInterfaceManager  
{
public:
	IInterfaceManager(){};
	virtual ~IInterfaceManager(){};

	virtual IInterface* queryInterfaceObj(std::string name){ return NULL; };

};


#define GET_INTERFACE_MANAGER_STRING "getInterfaceManager"
typedef IInterfaceManager* (*getInterfceManagerFunc)();

#endif // !defined(AFX_IUNKOWN_H__EF8D39E7_DAA3_4FB6_9963_5E254EA6159E__INCLUDED_)
