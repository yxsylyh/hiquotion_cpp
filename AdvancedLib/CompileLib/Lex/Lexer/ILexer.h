// ILexer.h: interface for the ILexer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILEXER_H__0EC3FDCA_BED5_41F4_82FF_E2656E043F46__INCLUDED_)
#define AFX_ILEXER_H__0EC3FDCA_BED5_41F4_82FF_E2656E043F46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <sstream>
#include <string>
#include <C++\FoundationLib\DataStructLib\PointerList.h>

using namespace std;

/*
Token Type & Subtype
	id,                          // 标识符或关键字（关键字由外部定义）
	number(integer,hex,double),  // 数字（整型，十六进制，双精度）
	comment(line,block),         // 注释（行注释，块注释）
	alt_meaning,                 // 转义字符
	var,                         // 变量（两个%中间的token）
	其他可打印字符，类型与字符名称相同
*/

enum
{
	CheckToken4Statute,
	CheckType4Statute,
};

struct MachineToken
{
	std::string token;
	std::string type;  // 状态机给出的类型
	std::string subtype;  // 状态机给出的子类型
	int startPosition;  // 状态机中的开始位置（状态机只分析字符串，所以该位置表示字符的索引）
	int endPosition;    // 状态机中的结束位置

	int check4Statute;  // 规约时是检查token还是检查类型（及子类型），默认是检查token
	bool isCheckSubtype; // 在检查类型的情况下，决定是否检查子类型

	MachineToken()
	{
		startPosition=-1;
		endPosition=-1;
		check4Statute=CheckToken4Statute;
		isCheckSubtype=false;
	}
	
	std::string toString()
	{
		std::stringstream ss;
		ss << "token[" << token << "], type[" << type << "], startPos[" << startPosition << "], endPos[" << endPosition << "]";
		//		std::string msg=ss.str();
		return ss.str();
	}
};

// struct LexToken
// {
// 	MachineToken token;
// 	
// 	BOOL isKeyword;
// 	BOOL isNumeric;
// 	BOOL isInteger;
// 	BOOL isHex;
// 	
// 	std::string grammerType;  // 对于状态机的id类型，经语法分析后得到的类型，除id类型外，该值与 machine_type 相同
// 	int startRow;  // 根据状态机的开始位置，得到的开始行
// 	int startCol;  // 根据状态机的开始位置，得到的开始列
// 	int endRow;    // 根据状态机的结束位置，得到的结束行
// 	int endCol;    // 根据状态机的结束位置，得到的结束列
// };

class ILexer  
{
public:
	ILexer(){};
	virtual ~ILexer(){};

	virtual int analyze(string text, CPointerList<MachineToken *> &tokenList, CValueList<string> &errList){ return 0; };
};

#endif // !defined(AFX_ILEXER_H__0EC3FDCA_BED5_41F4_82FF_E2656E043F46__INCLUDED_)
