#include "stdafx.h"
#include "StringConverter.h"

std::string CStringConverter::UnicodeToUtf8(const wchar_t* unicode)
{
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
	char* szUtf8 = (char*)malloc(len + 1);
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, unicode, -1, szUtf8, len, NULL, NULL);
	std::string strTemp = szUtf8;
	free(szUtf8);
	return strTemp;
}

std::string CStringConverter::MultibyteToUtf8(std::string strData)
{
	//把GB2312编码的中文字串转换为UTF-8编码的中文字串  
	int iLen = strData.length();
	CHAR* pMb = new CHAR[iLen + 1];
	int iMbLen = iLen + 1;
	ZeroMemory(pMb, iMbLen);
	memcpy_s(pMb, iMbLen, strData.c_str(), strData.length());

	//将多字节字符串编码转换成宽字符串  
	iLen = ::MultiByteToWideChar(CP_ACP, 0, pMb, iMbLen, NULL, 0);
	WCHAR* lpszW = NULL;
	lpszW = new WCHAR[iLen];
	::wmemset(lpszW, 0, iLen);

	int iRtn = ::MultiByteToWideChar(CP_ACP, 0, pMb, iMbLen, lpszW, iLen);
	if (iRtn != iLen)
	{
		delete[] pMb; pMb = NULL;
		delete[] lpszW; lpszW = NULL;
		return NULL;
	}
	//转换一个宽字符串到UTF8字符串  
	int iUTF8Len = ::WideCharToMultiByte(CP_UTF8, 0, lpszW, iLen, NULL, 0, NULL, NULL);
	if (0 == iUTF8Len)
	{
		delete[] pMb; pMb = NULL;
		delete[] lpszW; lpszW = NULL;

		return NULL;
	}

	char* pUTF8 = new char[iUTF8Len];
	::memset(pUTF8, 0, iUTF8Len);
	::WideCharToMultiByte(CP_UTF8, 0, lpszW, iLen, pUTF8, iUTF8Len, NULL, NULL);

	std::string strTemp = pUTF8;

	delete[] pMb; pMb = NULL;
	delete[] lpszW; lpszW = NULL;
	delete[] pUTF8; pUTF8 = NULL;

	return strTemp;
}

std::string CStringConverter::UnicodeToAnsi(const wchar_t* szStr)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);

	std::string result = pResult;
	delete pResult;
	return result;
}