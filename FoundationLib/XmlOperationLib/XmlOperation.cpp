#include "stdafx.h"
#include "XmlOperation.h"

CXmlOperation::CXmlOperation()
	: m_errcode(0)
{
}

CXmlOperation::~CXmlOperation()
{
}

bool CXmlOperation::loadXml(std::string path)
{
	m_errcode = -1;

	if (path.size() <= 0)
		return false;

	pugi::xml_parse_result result = m_xmlDoc.load_file(path.c_str());
	if (result.status == pugi::status_ok)
	{
		m_errcode = 0;
		return true;
	}

	m_errcode = (int)result.status;
	return false;
}

bool CXmlOperation::loadBuffer(std::string xmlContent)
{
	m_errcode = -1;

	if (xmlContent.size() <= 0)
		return false;

	pugi::xml_parse_result result = m_xmlDoc.load(xmlContent.c_str());
	if (result.status == pugi::status_ok)
	{
		m_errcode = 0;
		return true;
	}

	m_errcode = (int)result.status;
	return false;
}

void CXmlOperation::addDeclaration(std::string encoding)
{
	pugi::xml_node xdec = m_xmlDoc.prepend_child(pugi::node_declaration);
	xdec.append_attribute("version").set_value("1.0");
	xdec.append_attribute("encoding").set_value(encoding.c_str());
}

pugi::xml_node CXmlOperation::addChild(pugi::xpath_node parentNode, std::string name)
{
// 	if (name.size() <= 0)
// 		return pugi::xml_node();

	return parentNode.node().append_child(name.c_str());
}

void CXmlOperation::setNodeValue(pugi::xpath_node node, std::string value)
{
	if (value.size() <= 0)
		return;

	node.node().set_value(value.c_str());
}

pugi::xml_attribute CXmlOperation::addAttribute(pugi::xpath_node node, std::string attribute)
{
// 	if (attribute.size() <= 0)
// 		return pugi::xml_attribute();

	return node.node().append_attribute(attribute.c_str());
}

void CXmlOperation::setAttributeString(pugi::xml_attribute attribute, std::string value)
{
	if (value.size() <= 0)
		return;

	attribute.set_value(value.c_str());
}

void CXmlOperation::setAttributeInt(pugi::xml_attribute attribute, int value)
{
	attribute.set_value(value);
}

void CXmlOperation::setAttributeBool(pugi::xml_attribute attribute, bool value)
{
	attribute.set_value(value);
}

void CXmlOperation::setAttributeDouble(pugi::xml_attribute attribute, double value)
{
	attribute.set_value(value);
}

void CXmlOperation::setAttributeFloat(pugi::xml_attribute attribute, float value)
{
	attribute.set_value(value);
}

void CXmlOperation::addAttributeString(pugi::xml_node node, std::string attribute, std::string value)
{
	if (attribute.size() <= 0 || value.size()<=0)
		return;

	pugi::xml_attribute attr = node.append_attribute(attribute.c_str());
	attr.set_value(value.c_str());
}

void CXmlOperation::addAttributeInt(pugi::xml_node node, std::string attribute, int value)
{
	if (attribute.size() <= 0)
		return;

	pugi::xml_attribute attr = node.append_attribute(attribute.c_str());
	attr.set_value(value);
}

void CXmlOperation::addAttributeBool(pugi::xml_node node, std::string attribute, bool value)
{
	if (attribute.size() <= 0)
		return;

	pugi::xml_attribute attr = node.append_attribute(attribute.c_str());
	attr.set_value(value);
}

void CXmlOperation::addAttributeDouble(pugi::xml_node node, std::string attribute, double value)
{
	if (attribute.size() <= 0)
		return;

	pugi::xml_attribute attr = node.append_attribute(attribute.c_str());
	attr.set_value(value);
}

void CXmlOperation::addAttributeFloat(pugi::xml_node node, std::string attribute, float value)
{
	if (attribute.size() <= 0)
		return;

	pugi::xml_attribute attr = node.append_attribute(attribute.c_str());
	attr.set_value(value);
}

bool CXmlOperation::remove(pugi::xml_node &node)
{
	return node.parent().remove_child(node);
}

bool CXmlOperation::removeChild(pugi::xml_node node, std::string name)
{
	if (name.size() <= 0)
		return false;

	return node.remove_child(name.c_str());
}

bool CXmlOperation::removeAttribute(pugi::xml_node node, std::string name)
{
	if (name.size() <= 0)
		return false;

	return node.remove_attribute(name.c_str());
}

pugi::xpath_node_set CXmlOperation::selectNodeSet(std::string xpath)
{
// 	pugi::xpath_node_set empty;
// 
// 	if (xpath.size() <= 0)
// 		return empty;

	return m_xmlDoc.select_nodes(xpath.c_str());  // 有错误会抛出异常
}

pugi::xpath_node CXmlOperation::selectNode(std::string xpath)
{
// 	pugi::xpath_node empty;
// 
// 	if (xpath.size() <= 0)
// 		return empty;

	return m_xmlDoc.select_single_node(xpath.c_str());  // 有错误会抛出异常
}

bool CXmlOperation::getAttributeBool(pugi::xpath_node node, std::string attribute)
{
	pugi::xml_attribute attr = node.node().attribute(attribute.c_str());
	return attr.as_bool();
}

int CXmlOperation::getAttributeInt(pugi::xpath_node node, std::string attribute)
{
	pugi::xml_attribute attr=node.node().attribute(attribute.c_str());
	return attr.as_int();
}

double CXmlOperation::getAttributeDouble(pugi::xpath_node node, std::string attribute)
{
	pugi::xml_attribute attr = node.node().attribute(attribute.c_str());
	return attr.as_double();
}

float CXmlOperation::getAttributeFloat(pugi::xpath_node node, std::string attribute)
{
	pugi::xml_attribute attr = node.node().attribute(attribute.c_str());
	return attr.as_float();
}

std::string CXmlOperation::getAttibuteString(pugi::xpath_node node, std::string attribute)
{
	pugi::xml_attribute attr = node.node().attribute(attribute.c_str());
	return attr.as_string();
}

bool CXmlOperation::save(std::string path)
{
	if (m_errcode)
		return false;

	if (path.size() <= 0)
		return false;

	return m_xmlDoc.save_file(path.c_str(), "  ", pugi::format_indent | pugi::format_save_file_text);
}
