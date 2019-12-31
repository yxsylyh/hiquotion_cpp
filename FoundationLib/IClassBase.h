// IClassBase.h: interface for the IClassBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICLASSBASE_H__FEA36483_D517_410B_BF17_8AA436BB9C81__INCLUDED_)
#define AFX_ICLASSBASE_H__FEA36483_D517_410B_BF17_8AA436BB9C81__INCLUDED_

#include <string>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class IClassBase  
{
public:
	IClassBase(){};
	virtual ~IClassBase(){};

	std::string getErrMessage() { return m_errMessage; };
	virtual std::string toString() { return ""; };

protected:
	std::string m_errMessage;

};

#endif // !defined(AFX_ICLASSBASE_H__FEA36483_D517_410B_BF17_8AA436BB9C81__INCLUDED_)
