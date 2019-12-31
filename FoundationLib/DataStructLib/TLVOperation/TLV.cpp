// TLV.cpp: implementation of the CTLV class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TLVOperation.h"
#include "TLV.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTLV::CTLV(short tag, int length, char *value, BOOL isUseValueNew)
: m_tag(tag), m_length(length), m_value(value), m_valueNew(NULL), m_isUseValueNew(isUseValueNew)
{
	if(length>0 && m_isUseValueNew)
	{
		m_valueNew=new char[length];
		memcpy(m_valueNew, value, length);
	}
}

CTLV::~CTLV()
{
	if(m_isUseValueNew)
		delete m_valueNew;
}

char *CTLV::getValue()
{
	if(m_isUseValueNew)
		return m_valueNew;
	else
		return m_value;
}

void CTLV::setValue(char *val,  int length, BOOL isUseValueNew)
{
	if(!val)
		return;

	if(length<=0)
		return;

	if(isUseValueNew)
	{
		m_isUseValueNew=isUseValueNew;
		if(m_valueNew)
			delete m_valueNew;

		m_valueNew=new char[length];
		memcpy(m_valueNew, val, length);
	}
	else
	{
		m_value=val;
	}

	m_length=length;
}
