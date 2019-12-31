// IniOperation.h: interface for the CIniOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIOPERATION_H__89A5C8C5_6023_480B_AD8D_B66E181C22C0__INCLUDED_)
#define AFX_INIOPERATION_H__89A5C8C5_6023_480B_AD8D_B66E181C22C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;

class CIniOperation  
{
public:
 	CIniOperation();
	CIniOperation(std::string path);
 	virtual ~CIniOperation();

// 	string className;
// 	string classCode;

	char m_fileName[MAX_PATH*10];
	// 读取指定节指定键的字符串值
	char *getSectionValueString(char *sectionName,char *sectionKey,char *defaultValue="");
	// 读取指定节指定键的数值
	int getSectionValueInt(char *sectionName,char *sectionKey,int defaultValue=0);
	
	// 设置指定节指定键的指定字符串值
	void setSectionValueString(char *sectionName,char *sectionKey,char *keyValue);
	// 设置指定节指定键的指定数值
	void setSectionValueInt(char *sectionName,char *sectionKey,int keyValue);

	void setFileName(char *fileName)
	{
		memset(m_fileName, 0x00, MAX_PATH*10);
		int length=strlen(fileName);
		memcpy(m_fileName,fileName,length);
		//m_fileName=fileName;
	}

private:
	char* result;
};

#endif // !defined(AFX_INIOPERATION_H__89A5C8C5_6023_480B_AD8D_B66E181C22C0__INCLUDED_)
