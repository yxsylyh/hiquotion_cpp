#pragma once

#include "ialertor.h"
#include <pugixmllib/pugixml.hpp>

class CAlertor :
	public IAlertor
{
public:
	CAlertor(void);
	~CAlertor(void);

	BOOL readConfig(pugi::xml_node configRoot);
	BOOL alert();

private:

	string m_command;
};
