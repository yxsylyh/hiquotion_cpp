// CharBuffer.h: interface for the CCharBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARBUFFER_H__2752D2AB_91A4_4974_BFE5_521C9389518E__INCLUDED_)
#define AFX_CHARBUFFER_H__2752D2AB_91A4_4974_BFE5_521C9389518E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataBufferT.h"

class CCharBuffer : public CDataBufferT<char>
{
public:
	CCharBuffer();
	virtual ~CCharBuffer();

};

#endif // !defined(AFX_CHARBUFFER_H__2752D2AB_91A4_4974_BFE5_521C9389518E__INCLUDED_)
