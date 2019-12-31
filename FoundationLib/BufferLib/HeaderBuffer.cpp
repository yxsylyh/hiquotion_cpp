// HeaderBuffer.cpp: implementation of the CHeaderBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HeaderBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHeaderBuffer::CHeaderBuffer()
{

}

CHeaderBuffer::CHeaderBuffer(int headerLength)
{

}

CHeaderBuffer::~CHeaderBuffer()
{

}

BYTE *CHeaderBuffer::getDataBuffer()
{
	return (BYTE *)m_buffer + m_headLength;
}

BYTE *CHeaderBuffer::getTotalBuffer()
{
	return (BYTE *)m_buffer;
}

void CHeaderBuffer::setTotalData(char *data, int dataLength)
{
	if(!data)
		return;
	
	if(dataLength<=0)
		return;
	
	memcpy(m_buffer, data, dataLength);
	if(dataLength<=getHeadLength())
		m_dataLength=0;
	else
		m_dataLength=dataLength-getHeadLength();
}
