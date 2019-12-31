#pragma once
#include <string>
#include <C++/FoundationLib/DataStructLib/PointerList.h>
#include <C++\3rdParty\PugiXmlLib\pugixml.hpp>
#include <C++\foundationLib\DataStructLib\ValueList.h>

struct XmlConfigNodeProperty
{
	std::string name;
	std::string type;
};

struct XmlConfigNode
{
	std::string gentype;	// 生成类型
							// valuable表示每个property（属性）都生成变量，pusher_ip和pusher_port。
							// struct表示生成结构体，ip和port为pusher结构体中的变量
	std::string name;    // gentype 的名称，比如gentype是struct，name是config，则会生成 struct config的代码
	std::string location;
	CPointerList<XmlConfigNodeProperty*> properties;
	CPointerList<XmlConfigNode*> nodes;

	std::string generatedStructor;
	std::string generatedOperationLoad;
	std::string generatedOperationSave;
};

struct XmlConfig
{
	std::string gentype; // value="struct"/"class"
	std::string name;    // gentype 的名称，比如gentype是struct，name是config，则会生成 struct config的代码
	CPointerList<XmlConfigNode*> nodes;
};

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

	std::string list2string(CValueList<std::string> lines, std::string saperator="\n");

private:
	XmlConfig m_config;

	std::string generatedWholeStructor;
	std::string generatedWholeImpl;
};
