// HttpRequest.h: interface for the CHttpRequest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTPREQUEST_H__A0786376_E7DA_460E_9FE8_96979FBFBC06__INCLUDED_)
#define AFX_HTTPREQUEST_H__A0786376_E7DA_460E_9FE8_96979FBFBC06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wininet.h>

using namespace std;

struct ResponseHead
{
	string contextLength;
    string statusCode;
    string statusText;
};

class CHttpRequest  
{
public:
	CHttpRequest();
	virtual ~CHttpRequest();

	int connect(string userAgent, string url, string method="POST");
	void closeConnect();
	// header 是类似这样的字符串："Content-type: application/x-www-form-urlencoded\r\n"
	int addHeader(string header);
	int sendData(char *data, long dataLength, ResponseHead &ret);
	int sendString(string data, ResponseHead &ret);
	int readData(char *buffer, long bufferLength, long *dataLength);
	int readString(string &data);

	DWORD getWinLastError() const { return m_winLastError; }

private:
	void closeExceptSession();
	void closeAll();

private:
	HINTERNET m_session;
	HINTERNET m_connection;
	HINTERNET m_request;

	DWORD m_winLastError;
};

#endif // !defined(AFX_HTTPREQUEST_H__A0786376_E7DA_460E_9FE8_96979FBFBC06__INCLUDED_)
