#include "StdAfx.h"
#include "Alertor.h"

CAlertor::CAlertor(void)
{
	m_command="";
}

CAlertor::~CAlertor(void)
{
}

BOOL CAlertor::readConfig(pugi::xml_node configRoot)
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

BOOL CAlertor::alert()
{
	int ret=WinExec(m_command.c_str(), SW_HIDE);
	if(ret>31)
		return TRUE;
	else
		return FALSE;
}
