// UrlParser.h: interface for the CUrlParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_URLPARSER_H__F37071B3_56EE_4542_AB19_8683A214CF78__INCLUDED_)
#define AFX_URLPARSER_H__F37071B3_56EE_4542_AB19_8683A214CF78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std;

#include <wininet.h>

// #define USE_WINHTTP    //Comment this line to user wininet.
#ifdef USE_WINHTTP
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
#else
#include <wininet.h>
#pragma comment(lib, "wininet.lib")
#endif

class CUrlParser  
{
public:
	CUrlParser();
	virtual ~CUrlParser();

	static int parseUrl(string url);

	static int getScheme();
	static std::string getHost();
	static int getPort();
	static std::string getPath();

};

#endif // !defined(AFX_URLPARSER_H__F37071B3_56EE_4542_AB19_8683A214CF78__INCLUDED_)
