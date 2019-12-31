#include "stdafx.h"
#include "StringExt.h"
#include <string.h>

CStringExt::CStringExt(void)
{
}

CStringExt::~CStringExt(void)
{
}

void CStringExt::Split(CString source, CStringArray& dest, CString division)
{
	dest.RemoveAll();
	int pos = 0;
	int pre_pos = 0;
	pos = source.Find(division,pos);
	while( -1 != pos )
	{
		CString splitted=source.Mid(pre_pos,(pos-pre_pos));
		dest.Add(splitted);
		pos +=division.GetLength();
		pre_pos = pos;
		pos = source.Find(division,pos);
	}

	if(pre_pos-division.GetLength()!=source.GetLength())
	{
		CString s_end=source.Mid(pre_pos,(source.GetLength()-pre_pos));
		dest.Add(s_end);
	}
}

void CStringExt::Split(CStringArray *splitStrings, CHAR *buffer, DWORD size, CHAR find)
{
	if(!buffer)
		return;

	DWORD lastPosition=0;
	for(DWORD i=0;i<size;i++)
	{
		if(buffer[i]!=find)
			continue;

		DWORD length=i-lastPosition-1;
		if(length==0)
		{
			lastPosition=i;
			continue;
		}

		CHAR *cfound=new CHAR[length+1];
		memset(cfound,0x00,length+1);
		memcpy(cfound, buffer+lastPosition+1,length);
		CString sfound=cfound;
		delete cfound;

		splitStrings->Add(sfound);

		lastPosition=i;
	}

	DWORD length=size-lastPosition-1;
	if(length==0)
		return;

	CHAR *cfound=new CHAR[length];
	memcpy(cfound, buffer+lastPosition+1,length);
	CString sfound=cfound;
	delete cfound;

	splitStrings->Add(sfound);

}

CString CStringExt::Capital( CString str )
{
	if(str.GetLength()<=0)
		return "";

	char firstChar=str[0];
	if(firstChar<97 || firstChar>122)
		return str;

	CString first=str.Left(1);
	first.MakeUpper();

	if(str.GetLength()<=1)
		return first;

	return first+str.Right(str.GetLength()-1);
}

CString CStringExt::camel( CString str )
{
	CString first=str.Left(1);
	first.MakeLower();
	return first+str.Right(str.GetLength()-1);
}

// 取 c 左边的字符串
// 如果没有 c，则返回全部字符串
// CString CStringExt::stringLeft(CString str, char c, int mode)
// {
// 	if(str=="")
// 		return "";
// 
// 	if(mode==0)
// 		mode=1;
// 
// 	CString tmp=str;
// 	if(mode<0)
// 	{
// 		tmp=tmp.MakeReverse();
// 		mode=-mode;
// 	}
// 
// 	int pos=str.Find(c);
// 	if(pos<0)
// 		return str;
// 
// 	int count=1;
// 	
// 	while(count<mode)
// 	{
// 		pos=str.Find(c,pos+1);
// 		if(pos<0)
// 			return str;
// 
// 		count++
// 	}
// 
// 	return str.Left(pos);
// }

// 取 subStr 右边的字符串
// 如果没有 subStr，则返回全部字符串
BOOL CStringExt::stringRight(CString str, CString subStr, CString &dst, int mode)
{
	// 暂时忽略 mode 参数

	if(str.GetLength()<=0)
	{
		dst="";
		return FALSE;
	}

	if(subStr.GetLength()<=0)
	{
		dst=str;
		return FALSE;
	}

	int pos=str.Find(subStr);
	if(pos<0)
	{
		dst=str;
		return FALSE;
	}
	else
	{
		dst=str.Right(str.GetLength()-pos-subStr.GetLength());
		return TRUE;
	}
}

void CStringExt::string_replace(std::string&s1,const std::string&s2,const std::string&s3)
{
	string::size_type pos=0;
	string::size_type a=s2.size();
	string::size_type b=s3.size();
	while((pos=s1.find(s2,pos))!=std::string::npos)
	{
		s1.replace(pos,a,s3);
		pos+=b;
	}
}

#if _MSC_VER  >  1200   // greater than vc6

char* CStringExt::wideChartoMultiByte(const wchar_t* wp)
{
	char *m_char; 
	int len= WideCharToMultiByte(CP_ACP,0,wp,wcslen(wp),NULL,0,NULL,NULL);   
	m_char=new char[len+1];   
	WideCharToMultiByte(CP_ACP,0,wp,wcslen(wp),m_char,len,NULL,NULL);   
	m_char[len]='\0';   
	return m_char;
}

wchar_t* CStringExt::multiBytetoWideChar(const char* c)
{
	wchar_t *m_wchar; 
	int len = MultiByteToWideChar(CP_ACP,0,c,strlen(c),NULL,0);   
	m_wchar=new wchar_t[len+1];   
	MultiByteToWideChar(CP_ACP,0,c,strlen(c),m_wchar,len);   
	m_wchar[len]='\0';   
	return m_wchar;   
}

std::wstring CStringExt::utf8toWideChar(const char* buf)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);
	vector<wchar_t> unicode(len);
	MultiByteToWideChar(CP_UTF8, 0, buf, -1, &unicode[0], len);
	return std::wstring(&unicode[0]);
}

std::string CStringExt::wideChartoUTF8(const wchar_t* buf)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, buf, -1, NULL, 0, NULL, NULL);
	vector<char> utf8(len);
	WideCharToMultiByte(CP_UTF8, 0, buf, -1, &utf8[0], len, NULL, NULL);
	return std::string(&utf8[0]);
}

#endif

