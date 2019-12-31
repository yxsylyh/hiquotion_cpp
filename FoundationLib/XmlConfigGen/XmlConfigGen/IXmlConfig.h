#pragma once
#include <string>
#include <C++/FoundationLib/DataStructLib/PointerList.h>
#include <C++\3rdParty\PugiXmlLib\pugixml.hpp>

#define XPathLocateFromNode(node, path, xpathNodes) pugi::xmlpath_nodes ##xpathNodes## = ##node##.select_xpath(##path##);
#define PropertyLoad(var, node, property, type) var## = ##node##.attribute(##property##).as_##type##();
#define PropertyLoadString(var, node, property) var## = ##node##.attribute(##property##).as_string();
#define PropertyLoadInt(var, node, property) var## = ##node##.attribute(##property##).as_int();
#define ValueLoad(var, node, type) var## = ##node.value.as_##type##();
#define ValueLoadString(value, node) var## = ##node.value.as_string();
#define ValueLoadInt(value, node) var## = ##node.value.as_int();
#define AddList(var, lst) lst##.push_back(##var##);

class CXmlClassGenerator
{
public:
	CXmlClassGenerator();
	~CXmlClassGenerator();
	
	int parseNode(pugi::xml_node current, XmlConfigNode *configNode );
	int loadConfigXmlFile(std::string fileName);
	std::string genConfigOperation();

private:
	std::string genWholeStructor();
	std::string genWholeImpl();

	std::string genStructor(XmlConfigNode* node);
	std::string genLoadOperation(XmlConfigNode* node);
	std::string genSaveOperation(XmlConfigNode* node);

	std::string list2string(CPointerList<std::string> lines, std::string saperator="\n");

private:
	XmlConfig m_config;

	std::string generatedWholeStructor;
	std::string generatedWholeImpl;
};
