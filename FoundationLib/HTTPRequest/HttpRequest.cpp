// HttpRequest.cpp: implementation of the CHttpRequest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HttpRequest.h"
#include "UrlParser.h"
#include <sstream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// extern "C"
// {
/***********************定义HTTP发送所用方法***********************************/
// HINTERNET OpenSession(LPCWSTR userAgent)
HINTERNET OpenSession(string userAgent)
{
// #ifdef USE_WINHTTP
//     return WinHttpOpen(userAgent, NULL, NULL, NULL, NULL);;
// #else
    return InternetOpen(userAgent.c_str(), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
// #endif
}
 
// HINTERNET Connect(HINTERNET hSession, LPCWSTR serverAddr, int portNo)
HINTERNET Connect(HINTERNET hSession, string serverAddr, int portNo)
{
// #ifdef USE_WINHTTP
//     return WinHttpConnect(hSession, serverAddr, (INTERNET_PORT) portNo, 0);
// #else
    return InternetConnect(hSession, serverAddr.c_str(), portNo, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
// #endif
}
 
// HINTERNET OpenRequest(HINTERNET hConnect, LPCWSTR verb, LPCWSTR objectName, int scheme)
HINTERNET OpenRequest(HINTERNET hConnect, string verb, string objectName, int scheme)
{
    DWORD flags = 0;
// #ifdef USE_WINHTTP
//     if (scheme == INTERNET_SCHEME_HTTPS) {
//         flags |= WINHTTP_FLAG_SECURE;
//     }
//  
//     return WinHttpOpenRequest(hConnect, verb, objectName, NULL, NULL, NULL, flags);
//  
// #else
    if (scheme == INTERNET_SCHEME_HTTPS) {
        flags |= INTERNET_FLAG_SECURE;
    }
 
    return HttpOpenRequest(hConnect, verb.c_str(), objectName.c_str(), NULL, NULL, NULL, flags, 0);
// #endif
}
 
// BOOL AddRequestHeaders(HINTERNET hRequest, LPCWSTR header)
BOOL AddRequestHeaders(HINTERNET hRequest, string header)
{
//     SIZE_T len = lstrlenW(header);
// #ifdef USE_WINHTTP
//     return WinHttpAddRequestHeaders(hRequest, header, DWORD(len), WINHTTP_ADDREQ_FLAG_ADD);
// #else
//     return HttpAddRequestHeaders(hRequest, header.c_str(), DWORD(len), HTTP_ADDREQ_FLAG_ADD);
    return HttpAddRequestHeaders(hRequest, header.c_str(), header.length(), HTTP_ADDREQ_FLAG_ADD);
// #endif
}
 
BOOL SendRequest(HINTERNET hRequest, const void* body, DWORD size)
{
// #ifdef USE_WINHTTP
//     return WinHttpSendRequest(hRequest, 0, 0, const_cast<void*>(body), size, size, 0);
// #else
    return HttpSendRequest(hRequest, 0, 0, const_cast<void*>(body), size);
// #endif
}
 
BOOL EndRequest(HINTERNET hRequest)
{
// #ifdef USE_WINHTTP
//     return WinHttpReceiveResponse(hRequest, 0);
// #else
    // if you use HttpSendRequestEx to send request then use HttpEndRequest in here!
    return TRUE;
// #endif
}
 
BOOL QueryInfo(HINTERNET hRequest, int queryId, char* szBuf, DWORD* pdwSize)
{
// #ifdef USE_WINHTTP
//     return WinHttpQueryHeaders(hRequest, (DWORD) queryId, 0, szBuf, pdwSize, 0);
// #else
    return HttpQueryInfo(hRequest, queryId, szBuf, pdwSize, 0);
// #endif
}
 
BOOL ReadData(HINTERNET hRequest, void* buffer, DWORD length, DWORD* cbRead)
{
// #ifdef USE_WINHTTP
//     return WinHttpReadData(hRequest, buffer, length, cbRead);
// #else
    return InternetReadFile(hRequest, buffer, length, cbRead);
// #endif
}
 
void CloseInternetHandle(HINTERNET hInternet)
{
    if (hInternet)
{
// #ifdef USE_WINHTTP
//         WinHttpCloseHandle(hInternet);
// #else
        InternetCloseHandle(hInternet);
// #endif
    }
}

#define BUF_SIZE 256
 
/**********************************************************/
///通过Http方式发送短信
// string SendSMS_HTTP(const long ececcid,const string & password ,const string & msisdn, const string &smsContent)
// {
//  string rtnStr ="-1";
//     HINTERNET hSession = 0;
//     HINTERNET hConnect = 0;
//     HINTERNET hRequest = 0;
//     string strHeader(/*L*/"Content-type: application/x-www-form-urlencoded\r\n");
//  
//     // Test data
// 	CUrlParser::parseUrl(/*L*/"http://pi.f3.cn/SendSMS.aspx");
// 	stringstream ss;
// 	ss<<"ececcid=600000&password="<<password<<"&msisdn="<<msisdn<<"&smscontent="<<smsContent<<"&msgtype=5&longcode=";
//  string StrPostData = ss.str();
//  
// //  StrPostData = string_To_UTF8(StrPostData);
//  
//     // Open session.
//     hSession = OpenSession(/*L*/"HttpPost by lyz_sea@163.com");
//     if (hSession == NULL) {
//         cout<<"Error:Open session!\n";
//         return "-1";
//     }
//  
//     // Connect.
//     hConnect = Connect(hSession, CUrlParser::getHost(), CUrlParser::getPort());
//     if (hConnect == NULL) {
//         cout<<"Error:Connect failed!\n";
//         return "-1";
//     }
//  
//     // Open request.
//     hRequest = OpenRequest(hConnect, /*L*/"POST", CUrlParser::getPath(), CUrlParser::getScheme());
//     if (hRequest == NULL) {
//         cout<<"Error:OpenRequest failed!\n";
//         return "-1";
//    }
//  
//     // Add request header.
//  if (!AddRequestHeaders(hRequest, strHeader.c_str())) {
//         cout<<"Error:AddRequestHeaders failed!\n";
//         return "-1";
//     }
//  
//     // Send post data.
//  if (!SendRequest(hRequest, StrPostData.c_str(), StrPostData.length())) {
//         cout<<"Error:SendRequest failed!\n";
//         return "-1";
//     }
//  
//     // End request
//     if (!EndRequest(hRequest)) {
//         cout<<"Error:EndRequest failed!\n";
//         return "-1";
//     }
//  
//     char szBuf[BUF_SIZE];
//     DWORD dwSize = 0;
//     szBuf[0] = 0;
//  
//     // Query header info.
// // #ifdef USE_WINHTTP
// //     int contextLengthId = WINHTTP_QUERY_CONTENT_LENGTH;
// //     int statusCodeId = WINHTTP_QUERY_STATUS_CODE;
// //     int statusTextId = WINHTTP_QUERY_STATUS_TEXT;
// // #else
//     int contextLengthId = HTTP_QUERY_CONTENT_LENGTH;
//     int statusCodeId = HTTP_QUERY_STATUS_CODE;
//     int statusTextId = HTTP_QUERY_STATUS_TEXT;
// // #endif
//     dwSize = BUF_SIZE;
//     if (QueryInfo(hRequest, contextLengthId, szBuf, &dwSize)) {
//         szBuf[dwSize] = 0;
//         cout<<"Content length: "<<szBuf<<endl;
//     }
//     dwSize = BUF_SIZE;
//     if (QueryInfo(hRequest, statusCodeId, szBuf, &dwSize)) {
//         szBuf[dwSize] = 0;
//         cout<<"Status code: "<< szBuf<<endl;
//     }
//  
//     dwSize = BUF_SIZE;
//     if (QueryInfo(hRequest, statusTextId, szBuf, &dwSize)) {
//         szBuf[dwSize] = 0;
//         cout<<"Status text:"<<szBuf<<endl;
//     }
//  
//     // read data.
//     for (;;) {
//         dwSize = BUF_SIZE;
//         if (ReadData(hRequest, szBuf, dwSize, &dwSize) == FALSE) {
//            break;
//         }
//  
//         if (dwSize <= 0) {
//             break;
//         }
//  
//         szBuf[dwSize] = 0;
//         
// // 	rtnStr =::UTF8_To_string(string(szBuf));
// 	rtnStr =string(szBuf);
//  
//   cout<<rtnStr<<endl;//Output 返回值
//    
//     }
//  
//     CloseInternetHandle(hRequest);
//     CloseInternetHandle(hConnect);
//     CloseInternetHandle(hSession);
//  
//  return  rtnStr;
// }
// };

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHttpRequest::CHttpRequest()
: m_session(NULL), m_connection(NULL), m_request(NULL), m_winLastError(0)
{

}

CHttpRequest::~CHttpRequest()
{
	closeAll();
}

// 0：成功
// -1：Session 打开Session失败
// -2：connection 打开Connection失败
// -3：request 打开Request失败
int CHttpRequest::connect(string userAgent, string url, string method)
{
	m_winLastError=0;
	closeExceptSession();

	if(!m_session)
		m_session=OpenSession(userAgent);
	if(!m_session)
	{
		m_winLastError=GetLastError();
		return -1;
	}

	CUrlParser::parseUrl(url);


	m_connection=Connect(m_session, CUrlParser::getHost(), CUrlParser::getPort());
	if(!m_connection)
	{
		m_winLastError=GetLastError();
		return -2;
	}

	m_request=OpenRequest(m_connection, method, CUrlParser::getPath(), CUrlParser::getScheme());
	if(!m_request)
	{
		m_winLastError=GetLastError();
		return -3;
	}

	return 0;
}

void CHttpRequest::closeConnect()
{
	closeExceptSession();
}

// 0：成功
// -1：request未打开
// -2：header添加失败
int CHttpRequest::addHeader(string header)
{
	m_winLastError=0;

	if(!m_request)
		return -1;

	if(!AddRequestHeaders(m_request, header))
	{
		m_winLastError=GetLastError();
		return -2;
	}

	return 0;
}

int CHttpRequest::sendData(char *data, long dataLength, ResponseHead &ret)
{
	m_winLastError=0;

	if(!m_request)
		return -1;

	if(!SendRequest(m_request, data, dataLength))
	{
		m_winLastError=GetLastError();
		return -2;
	}

    // Query header info.
    char szBuf[BUF_SIZE];
    DWORD dwSize = 0;
    szBuf[0] = 0;

	// #ifdef USE_WINHTTP
	//     int contextLengthId = WINHTTP_QUERY_CONTENT_LENGTH;
	//     int statusCodeId = WINHTTP_QUERY_STATUS_CODE;
	//     int statusTextId = WINHTTP_QUERY_STATUS_TEXT;
	// #else
    int contextLengthId = HTTP_QUERY_CONTENT_LENGTH;
    int statusCodeId = HTTP_QUERY_STATUS_CODE;
    int statusTextId = HTTP_QUERY_STATUS_TEXT;
	// #endif
    dwSize = BUF_SIZE;
    if (QueryInfo(m_request, contextLengthId, szBuf, &dwSize)) {
        szBuf[dwSize] = 0;
		ret.contextLength=szBuf;
//        cout<<"Content length: "<<szBuf<<endl;
    }
    dwSize = BUF_SIZE;
    if (QueryInfo(m_request, statusCodeId, szBuf, &dwSize)) {
        szBuf[dwSize] = 0;
		ret.statusCode=szBuf;
//        cout<<"Status code: "<< szBuf<<endl;
    }
	
    dwSize = BUF_SIZE;
    if (QueryInfo(m_request, statusTextId, szBuf, &dwSize)) {
        szBuf[dwSize] = 0;
		ret.statusText=szBuf;
//        cout<<"Status text:"<<szBuf<<endl;
    }

	if (ret.statusCode != "200")
	{
		m_winLastError = GetLastError();
		return -3;
	}
	
	return 0;
}

int CHttpRequest::sendString(string data, ResponseHead &ret)
{
	m_winLastError=0;
	return sendData((char *)data.c_str(), data.length(), ret);
}

int CHttpRequest::readData(char *buffer, long bufferLength, long *dataLength)
{
	m_winLastError = 0;
	if (!m_request)
		return -1;

	for (;;) {
		if (!ReadData(m_request, buffer, (DWORD)bufferLength, (DWORD *)&bufferLength)) {
			break;
		}

		if (bufferLength <= 0) {
			break;
		}

		buffer[bufferLength] = 0;
		*dataLength = bufferLength;
	}

	return 0;
}

int CHttpRequest::readString(string &data)
{
	m_winLastError = 0;
	char buffer[1024];
	long len = 1024;
	int ret = readData(buffer, len, &len);
	if (ret != 0)
		return ret;

	buffer[len] = 0;
	data = buffer;

	return 0;
}

void CHttpRequest::closeExceptSession()
{
	if(m_request)
	{
		CloseInternetHandle(m_request);
		m_request=NULL;
	}
	if(m_connection)
	{
		CloseInternetHandle(m_connection);
		m_connection=NULL;
	}
}

void CHttpRequest::closeAll()
{
	closeExceptSession();

	if(m_session)
	{
		CloseInternetHandle(m_session);
		m_session=NULL;
	}
}

