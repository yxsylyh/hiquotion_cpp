// DelegationGen.h: interface for the CDelegationGen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DELEGATIONGEN_H__B6026EC2_CED6_4A8E_8823_161C8CFD4380__INCLUDED_)
#define AFX_DELEGATIONGEN_H__B6026EC2_CED6_4A8E_8823_161C8CFD4380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDelegationGen  
{
public:
	CDelegationGen(CString path);
	virtual ~CDelegationGen();

	void genDelegatorInterface(CString dname, CString dreg, CString dmethod);
	void genAgentInterface(CString aname, CString amethod);
	void genParameterInterface(CString pname);

	void genDelegator(CString dname, CString dreg, CString dmethod);
private:
	CString m_path;
};

#endif // !defined(AFX_DELEGATIONGEN_H__B6026EC2_CED6_4A8E_8823_161C8CFD4380__INCLUDED_)
