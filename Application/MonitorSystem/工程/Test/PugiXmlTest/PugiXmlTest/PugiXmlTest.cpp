// PugiXmlTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "PugiXmlTest.h"
#include "pugixmllib\pugixml.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: MFC 初始化失败\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: 在此处为应用程序的行为编写代码。
		std::string strFile = "F:\\工作\\项目\\省级社保生存认证子系统\\入库程序\\城居保\\Monitor\\工程\\Test\\PugiXmlTest\\Debug\\config.xml";
		pugi::xml_document doc;
		pugi::xml_parse_result result=doc.load_file(strFile.c_str());
		if (result.status!=pugi::status_ok) 
			return -1;

		pugi::xml_node node = doc.child("MonitorSystem").child("Monitor");
		std::string prop = node.attribute("interval").value();

		string path=node.child("MonitedObject").child_value("Path");

		return 0;
	}

	return nRetCode;
}
