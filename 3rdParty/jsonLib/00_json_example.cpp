#include "stdafx.h"
#include<iostream> 
#include <string>
#include "json.h" //包含头文件

using namespace std;
using namespace Json;

void readJson();
void writeJson();

int main(int argc, char** argv)
{

	readJson();

	cout << "---------------------------------------------" << endl;

	writeJson();

	return 0;
}
 
//解析JSON数据
void readJson() 
{
	std::string strValue = "{\"name\":\"json\",\"array\":	[{\"cpp\":\"jsoncpp\"},{\"java\":\"jsoninjava\"},	{\"php\":\"support\"}]}";

	Json::Reader reader;
	Json::Value value;

	if (reader.parse(strValue, value))
	{
		std::string out = value["name"].asString();
		std::cout << out << std::endl;
		const Json::Value arrayObj = value["array"];
		for (unsigned int i = 0; i < arrayObj.size(); i++)
		{
			if (!arrayObj[i].isMember("cpp")) 
				continue;
			out = arrayObj[i]["cpp"].asString();
			std::cout << out;
			if (i != (arrayObj.size() - 1))
				std::cout << std::endl;
		}
	}
}

//生成JSON格式数据
void writeJson() 
{
	Json::Value root;
	Json::Value arrayObj;
	Json::Value item;

	item["cpp"] = "jsoncpp";
	item["java"] = "jsoninjava";
	item["php"] = "support";
	arrayObj.append(item);

	root["name"] = "json";
	root["array"] = arrayObj;

//	root.toStyledString();
	std::string out = root.toStyledString(); 

	std::cout << out << std::endl;
}
