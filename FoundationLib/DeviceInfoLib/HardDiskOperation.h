// HardDiskOperation.h: interface for the CHardDiskOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HARDDISKOPERATION_H__8FF7C73D_7FCE_4E7F_8CFF_983C152D9BA2__INCLUDED_)
#define AFX_HARDDISKOPERATION_H__8FF7C73D_7FCE_4E7F_8CFF_983C152D9BA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

class CHardDiskOperation  
{
public:
	CHardDiskOperation();
	virtual ~CHardDiskOperation();

	static std::string getFysicalSn(int index=0);

	static std::string getErrMsg() { return m_errMsg; }

private:
	static std::string m_errMsg;
};

#endif // !defined(AFX_HARDDISKOPERATION_H__8FF7C73D_7FCE_4E7F_8CFF_983C152D9BA2__INCLUDED_)
