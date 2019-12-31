// UrlParser.cpp: implementation of the CUrlParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UrlParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static int m_scheme;
static string m_host;
static int m_port;
static string m_path;

int CUrlParser::parseUrl(string url)
{
	URL_COMPONENTS uc = { 0};
	uc.dwStructSize = sizeof(uc);
	
	const DWORD BUF_LEN = 256;
	
// 	WCHAR host[BUF_LEN];
	char host[BUF_LEN];
	uc.lpszHostName = host;
	uc.dwHostNameLength = BUF_LEN;
	
// 	WCHAR path[BUF_LEN];
	char path[BUF_LEN];
	uc.lpszUrlPath = path;
	uc.dwUrlPathLength = BUF_LEN;
	
// 	WCHAR extra[BUF_LEN];
	char extra[BUF_LEN];
	uc.lpszExtraInfo = extra;
	uc.dwExtraInfoLength = BUF_LEN;
	
// #ifdef USE_WINHTTP
// 	if (!WinHttpCrackUrl(url, 0, ICU_ESCAPE, &uc)) {
// 		cout<<"Error:WinHttpCrackUrl failed!\n";
// 	}
// 	
// #else
	if (!InternetCrackUrl(url.c_str(), 0, ICU_ESCAPE, &uc)) {
		printf("Error:InternetCrackUrl failed!\n");
		return -1;
	}
// #endif
	m_scheme = uc.nScheme;
	m_host = host;
	m_port = uc.nPort;
	m_path = path;

	return 0;
}

int CUrlParser::getScheme()
{
	return m_scheme;
}

std::string CUrlParser::getHost()
{
	return m_host;
}

int CUrlParser::getPort()
{
	return m_port;
}

std::string CUrlParser::getPath()
{
	return m_path;
}
