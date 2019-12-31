#pragma once

#include <string>
#include <C++\3rdParty\PugiXmlLib\pugixml.hpp>

class CXmlOperation
{
public:
	CXmlOperation();
	~CXmlOperation();

	bool loadXml(std::string path);
	bool loadBuffer(std::string xmlContent);

	void addDeclaration(std::string encoding = "gb2312");

	pugi::xml_node addChild(pugi::xpath_node parentNode, std::string name);
	void setNodeValue(pugi::xpath_node node, std::string value);

	pugi::xml_attribute addAttribute(pugi::xpath_node node, std::string attribute);
	void setAttributeString(pugi::xml_attribute attribute, std::string value);
	void setAttributeInt(pugi::xml_attribute attribute, int value);
	void setAttributeBool(pugi::xml_attribute attribute, bool value);
	void setAttributeDouble(pugi::xml_attribute attribute, double value);
	void setAttributeFloat(pugi::xml_attribute attribute, float value);

	void addAttributeString(pugi::xml_node node, std::string attribute, std::string value);
	void addAttributeInt(pugi::xml_node node, std::string attribute, int value);
	void addAttributeBool(pugi::xml_node node, std::string attribute, bool value);
	void addAttributeDouble(pugi::xml_node node, std::string attribute, double value);
	void addAttributeFloat(pugi::xml_node node, std::string attribute, float value);

	bool remove(pugi::xml_node &node);  // 删除非根节点
	bool removeChild(pugi::xml_node node, std::string name);

	bool removeAttribute(pugi::xml_node node, std::string name);

	pugi::xpath_node_set selectNodeSet(std::string xpath);
	pugi::xpath_node selectNode(std::string xpath);

	bool getAttributeBool(pugi::xpath_node node, std::string attribute);
	int getAttributeInt(pugi::xpath_node node, std::string attribute);
	double getAttributeDouble(pugi::xpath_node node, std::string attribute);
	float getAttributeFloat(pugi::xpath_node node, std::string attribute);
	std::string getAttibuteString(pugi::xpath_node node, std::string attribute);

	bool save(std::string path);

protected:
	pugi::xml_document m_xmlDoc;
	int m_errcode;
};

