// RE2SGConverter.h: interface for the CRE2SGConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RE2SGCONVERTER_H__72482B0D_D256_4EB6_9F48_E834D8D4FA9E__INCLUDED_)
#define AFX_RE2SGCONVERTER_H__72482B0D_D256_4EB6_9F48_E834D8D4FA9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <C++\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\EmptyRegularExpression.h>
#include <C++\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\RangeRegularExpression.h>
#include <C++\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\SymbolRegularExpression.h>
#include <C++\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\ConcatRegularExpression.h>
#include <C++\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\OrRegularExpression.h>
#include <C++\FoudationLib\RegularExpressionLib\RegularExpressionProj\RegularExpression\KleenStarRegularExpression.h>

class CRE2SGConverter  
{
public:
	CRE2SGConverter();
	virtual ~CRE2SGConverter();

	static CStatusGraphic *genFromEmptyRE(CEmptyRegularExpression *re);
	static CStatusGraphic *genFromRangeRE(CRangeRegularExpression *re);
	static CStatusGraphic *genFromSymbolRE(CSymbolRegularExpression *re);
	static CStatusGraphic *genFromConcatRE(CConcatRegularExpression *re);
	static CStatusGraphic *genFromOrRE(COrRegularExpression *re);
	static CStatusGraphic *genFromKleenStarRE(CKleenStarRegularExpression *re);

};

#endif // !defined(AFX_RE2SGCONVERTER_H__72482B0D_D256_4EB6_9F48_E834D8D4FA9E__INCLUDED_)
