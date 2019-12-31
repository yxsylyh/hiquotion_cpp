// KernelLexStatusGraphBuilder.h: interface for the CKernelLexStatusGraphBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KERNELLEXSTATUSGRAPHBUILDER_H__53013692_385E_4132_89E0_B57E06628CE1__INCLUDED_)
#define AFX_KERNELLEXSTATUSGRAPHBUILDER_H__53013692_385E_4132_89E0_B57E06628CE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\Lex\Lexer\ILexStatusGraphBuilder.h"

#include <C++\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\SymbolRegularExpression.h>
#include <C++\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\RangeRegularExpression.h>
#include <C++\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\OrRegularExpression.h>
#include <C++\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\DigitRegularExpression.h>
#include <C++\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\LowerRegularExpression.h>
#include <C++\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\UpperRegularExpression.h>
#include <C++\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\NotRegularExpression.h>
#include <C++\FoundationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\ConcatRegularExpression.h>

class CKernelLexStatusGraphBuilder : ILexStatusGraphBuilder
{
public:
	CKernelLexStatusGraphBuilder();
	virtual ~CKernelLexStatusGraphBuilder();

	BOOL build();
	CLexStatusGraph * getGraph() const { return m_graph; }

private:
	BOOL m_isBuilt;

	// 正则表达式
	// 数字用
	CSymbolRegularExpression dot;
	CSymbolRegularExpression zero;
	CSymbolRegularExpression x;
	CSymbolRegularExpression X;
	CRangeRegularExpression range19;
	CRangeRegularExpression rangeaf;
	CRangeRegularExpression rangeAF;
	COrRegularExpression xX;
	CDigitRegularExpression number;
	COrRegularExpression afAF;
	COrRegularExpression hex;

	// 标识符用
	CSymbolRegularExpression underline;
	CRangeRegularExpression rangeaz;
	CRangeRegularExpression rangeAZ;
	COrRegularExpression az_AZ;
	COrRegularExpression digit_az_AZ;
	COrRegularExpression underline_az_AZ;
	COrRegularExpression underline_digit_az_AZ;

	// 其他可打印字符用（除“_”之外）
	// sn 表示的字符
	//  1 `
	// 	2 ~
	// 	3 !
	// 	4 @
	// 	5 #
	// 	6 $
	// 	7 %
	// 	8 ^
	// 	9 &
	// 	10 *
	// 	11 (
	// 	12 )
	// 	13 -
	// 	14 =
	// 	15 +
	// 	16 [
	// 	17 ]
	// 	18 {
	// 	19 }
	// 	20 "\"
	// 	21 |
	// 	22 ;
	// 	23 :
	// 	24 '
	// 	25 "
	// 	26 ,
	// 	27 .
	// 	28 <
	// 	29 >
	// 	30 /
	// 	31 ?
	CSymbolRegularExpression s1;
	CSymbolRegularExpression s2;
	CSymbolRegularExpression s3;
	CSymbolRegularExpression s4;
	CSymbolRegularExpression s5;
	CSymbolRegularExpression s6;
	CSymbolRegularExpression s7;
	CSymbolRegularExpression s8;
	CSymbolRegularExpression s9;
	CSymbolRegularExpression s10;
	CSymbolRegularExpression s11;
	CSymbolRegularExpression s12;
	CSymbolRegularExpression s13;
	CSymbolRegularExpression s14;
	CSymbolRegularExpression s15;
	CSymbolRegularExpression s16;
	CSymbolRegularExpression s17;
	CSymbolRegularExpression s18;
	CSymbolRegularExpression s19;
	CSymbolRegularExpression s20;
	CSymbolRegularExpression s21;
	CSymbolRegularExpression s22;
	CSymbolRegularExpression s23;
	CSymbolRegularExpression s24;
	CSymbolRegularExpression s25;
	CSymbolRegularExpression s26;
	CSymbolRegularExpression s27;
	CSymbolRegularExpression s28;
	CSymbolRegularExpression s29;
	CSymbolRegularExpression s30;
	CSymbolRegularExpression s31;
	CSymbolRegularExpression s32;
	CSymbolRegularExpression s33;
	CSymbolRegularExpression s34;
	CSymbolRegularExpression s35;

	CSymbolRegularExpression sCR;   // 字符 CR
	CSymbolRegularExpression sLF;   // 字符 LF
// 	CSymbolRegularExpression sStar; // 字符 * = s10
// 	CSymbolRegularExpression sGang; // 字符 / = s30

	CNotRegularExpression notCR;    // not CR  \r
	CNotRegularExpression notLF;    // not LF  \n
	COrRegularExpression CRLF;  // CR or LF
	CNotRegularExpression notCRLF;  // not CR and not LF
	CNotRegularExpression notStar;  // not *
	CNotRegularExpression notGang;  // not /
};

#endif // !defined(AFX_KERNELLEXSTATUSGRAPHBUILDER_H__53013692_385E_4132_89E0_B57E06628CE1__INCLUDED_)
