// TlvMap.h: interface for the CTlvMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TLVMAP_H__C2D483F6_6F64_4076_9F9C_780A3F665890__INCLUDED_)
#define AFX_TLVMAP_H__C2D483F6_6F64_4076_9F9C_780A3F665890__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <C++\FoudationLib\DataStructLib\PointerMap.h>
#include "TLV.h"

class CTlvMap : public CPointerMap<short, CTLV *>
{
public:
	CTlvMap();
	virtual ~CTlvMap();

};

#endif // !defined(AFX_TLVMAP_H__C2D483F6_6F64_4076_9F9C_780A3F665890__INCLUDED_)
