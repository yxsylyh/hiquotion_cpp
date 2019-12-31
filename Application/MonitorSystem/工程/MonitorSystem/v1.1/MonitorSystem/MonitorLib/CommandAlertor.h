#pragma once

#include <C++\3rdParty\PugiXmlLib\pugixml.hpp>
#include "../monitorlib/interface/ialertor.h"

class CCommandAlertor :
	public IAlertor
{
public:
	CCommandAlertor(void);
	~CCommandAlertor(void);

	BOOL readConfig(pugi::xml_node configRoot);
	BOOL alert();

	string toString();

private:
	string m_command;
};
