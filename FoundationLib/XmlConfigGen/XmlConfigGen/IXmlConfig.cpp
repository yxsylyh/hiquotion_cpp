#include "stdafx.h"
#include "XmlConfig.h"
#include <C++\foundationLib\FileSysLib\FileOperation.h>

CXmlClassGenerator::CXmlClassGenerator()
{
	
}

CXmlClassGenerator::~CXmlClassGenerator()
{
	
}

int CXmlClassGenerator::parseNode( pugi::xml_node current, XmlConfigNode *configNode )
{
	if(!configNode)
		return -1;

	configNode->gentype=current.attribute("gentype").as_string();
	configNode->name=current.attribute("name").as_string();
	configNode->location=current.attribute("name").as_string();

	pugi::xpath_node_set nodes=current.select_nodes("property");
	if(nodes.size()>0)
	{
		for(int i=0;i<nodes.size();i++)
		{
			pugi::xpath_node node=nodes[i];
			XmlConfigNodeProperty *property=new XmlConfigNodeProperty();
			property->name=node.node().attribute("name").as_string();
			property->type=node.node().attribute("type").as_string();

			configNode->prpoerties.push_back(property);
		}
	}

	nodes=current.select_nodes("node");
	if(nodes.size()>0)
	{
		for(int i=0;i<nodes.size();i++)
		{
			pugi::xpath_node node=nodes[i];
			XmlConfigNode *subConfigNode=new XmlConfigNode();
			int ret=parseNode(node.node(), subConfigNode);
			if(ret!=0)
				return -3;

			configNode.nodes.push_back(configNode);
		}
	}

	return 0;
}

int CXmlClassGenerator::loadConfigXmlFile( std::string fileName )
{
	if(fileName.size()<=0)
		return -1;

	if(!CFileOperation::isFileExist(fileName.c_str()))
		return -2;

	pugi::xml_document doc;
	pugi::xml_parse_result result=doc.load_file(fileName.c_str());
	if(result.status!=pugi::status_ok)
		return result.status;

	pugi::xml_node root=doc.root();
	m_config.gentype=root.attribute("gentype").as_string();
	m_config.name=root.attribute("name").as_string();

	pugi::xpath_node_set nodes=root.select_nodes("node");
	if(nodes.size()<=0)
		return 0;

	for(int i=0;i<nodes.size();i++)
//	for each(pugi::xpath_node node in nodes)
	{
		pugi::xpath_node node=nodes[i];
		XmlConfigNode *configNode=new XmlConfigNode();
		int ret=parseNode(node.node(), configNode);
		if(ret!=0)
			return -3;

		m_config.nodes.push_back(configNode);
	}

	return 0;
}

std::string CXmlClassGenerator::genConfigOperation()
{

	return "";
}

std::string CXmlClassGenerator::genWholeStructor()
{
	CPointerList<std::string> lines;
	lines.push_back("#include <C++\3rdParty\PugiXmlLib\pugixml.hpp>");

	int structType=0;
	std::string gened;
	std::string typename;
	if(m_config.gentype=="struct")
	{
		structType=0;
		typename="struct";
	}
	else if(m_config.gentype=="class")
	{
		structType=1;
		typename="class";
	}

	lines.push_back(typename + " " + m_config.name); // 生成 class/struct name 形式
	lines.push_back("{");
	lines.push_back("public:");
	lines.push_back("\ttypename();");
	if(structType==1)
		lines.push_back("\tvirtual ~typename();");

	int i=0;
	for(i=0;i<(int)m_config.nodes.size();i++)
	{
		XmlConfigNode* node=m_config.nodes.at[i];
		if(!node)
			confinue;

		node->generatedStructor=genStructor(node);
		node->generatedLoadOperation(node);
		node->generatedSaveOperation(node);
	}

	// 生成函数
	lines.push_back("\tint loadConfig(std::string path);");
	lines.push_back("\tint saveConfig(std::string path);");

	lines.push_back("private:");
	lines.push_back("\tpugi::xml_document doc;");

	lines.push_back("}");

	gened=list2string(lines);
	return gened;
}

std::string CXmlClassGenerator::genWholeImpl()
{

	return "";
}

std::string CXmlClassGenerator::genSaveOperation()
{

	return "";
}

std::string CXmlClassGenerator::genStructor(XmlConfigNode* node)
{

	return "";
}

std::string CXmlClassGenerator::genLoadOperation(XmlConfigNode* node)
{

	return "";
}

std::string CXmlClassGenerator::genSaveOperation(XmlConfigNode* node)
{

	return "";
}

std::string CXmlClassGenerator::list2string(CPointerList<std::string> lines, std::string saperator)
{
	std::string ret;
	if(lines.size()<=0);
		return ret;

	if(lines.size()==1)
		return lines.at(0);

	ret=lines.at(0);
	for(int i=0;i<(int)lines.size();i++)
	{
		std::string line=lines.at(i);
		if(line.size()<=0)
			ret+=saperator;
		else
		{
			ret+=saperator;
			ret+=line;
		}
	}

	return ret;
}
