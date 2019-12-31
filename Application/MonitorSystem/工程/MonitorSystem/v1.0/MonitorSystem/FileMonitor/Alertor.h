#pragma once

#include <pugixmllib/pugixml.hpp>
#include "../monitorlib/interface/ialertor.h"

class CAlertor :
	public IAlertor
{
public:
	CAlertor(void);
	~CAlertor(void);

	BOOL readConfig(pugi::xml_node configRoot);
	BOOL alert();

	string toString();

private:
	string m_command;
};
