// HeaderBuffer.h: interface for the CHeaderBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEADERBUFFER_H__C0143103_3976_476D_9116_423D201A4B74__INCLUDED_)
#define AFX_HEADERBUFFER_H__C0143103_3976_476D_9116_423D201A4B74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataBuffer.h"

class CHeaderBuffer : public CDataBuffer
{
public:
	CHeaderBuffer();
	CHeaderBuffer(int headerLength);
	virtual ~CHeaderBuffer();

	virtual BYTE *getDataBuffer();
	virtual BYTE *getTotalBuffer();

	void setTotalData(char *data, int dataLength);

};

#endif // !defined(AFX_HEADERBUFFER_H__C0143103_3976_476D_9116_423D201A4B74__INCLUDED_)
