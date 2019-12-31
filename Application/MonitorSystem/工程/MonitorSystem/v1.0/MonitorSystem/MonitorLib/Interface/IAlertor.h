#pragma once

#include <PugiXmlLib\pugixml.hpp>

class IAlertor
{
public:
	IAlertor(void);
	~IAlertor(void);

	virtual BOOL readConfig(pugi::xml_node configRoot){return TRUE;};
	virtual BOOL alert(){return TRUE;};
	virtual string toString(){return "";};
};
