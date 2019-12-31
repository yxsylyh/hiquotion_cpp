#include "StdAfx.h"
#include "CommandAlertor.h"

CCommandAlertor::CCommandAlertor(void)
{
	m_command="";
}

CCommandAlertor::~CCommandAlertor(void)
{
}

BOOL CCommandAlertor::readConfig(pugi::xml_node configRoot)
{
	try
	{
		m_command=configRoot.child("Commands").child_value("Command");
	}
	catch (CException* e)
	{
		return FALSE;
	}

	if(m_command=="")
	{
		return FALSE;
	}

	return TRUE;

}

BOOL CCommandAlertor::alert()
{
	int ret=WinExec(m_command.c_str(), SW_HIDE);
	if(ret>31)
		return TRUE;
	else
		return FALSE;
}

string CCommandAlertor::toString()
{
	return "±¨¾¯Æ÷Ö´ĞĞµÄÃüÁî£º" + m_command;
}
