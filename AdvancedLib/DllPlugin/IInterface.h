// IInterface.h: interface for the IInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IINTERFACE_H__ADFBA432_3FFF_4349_BB98_E0312B06CECF__INCLUDED_)
#define AFX_IINTERFACE_H__ADFBA432_3FFF_4349_BB98_E0312B06CECF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

class IInterface  
{
public:
	IInterface(){m_sender=NULL;};
	virtual ~IInterface(){};

	void setMessageSender(HWND sender)
	{
		m_sender=sender;
	};
	
// 	void sendMessage(UINT msg, std::string content)
// 	{
// 		if(m_sender)
// 			m_sender->SendMessage(msg, (WPARAM)content.c_str(), NULL);
// 	};

protected:
	HWND m_sender;
};

#define GET_INTERFACE_STRING "getInterface"
typedef IInterface* (*getInterfceFunc)();

#endif // !defined(AFX_IINTERFACE_H__ADFBA432_3FFF_4349_BB98_E0312B06CECF__INCLUDED_)
