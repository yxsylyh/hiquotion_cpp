// DelegationGen.cpp: implementation of the CDelegationGen class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DelegationCodeGen.h"
#include "DelegationGen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDelegationGen::CDelegationGen(CString path)
: m_path(path)
{

}

CDelegationGen::~CDelegationGen()
{

}

void CDelegationGen::genDelegatorInterface(CString dname, CString dreg, CString dmethod)
{
	CString content="";
	
	CString fname=m_path+"\\"+dname+".h";
	CFile file;
	file.Open(fname,CFile::modeWrite | CFile::shareDenyWrite);

}

void CDelegationGen::genAgentInterface(CString aname, CString amethod)
{

}

void CDelegationGen::genParameterInterface(CString pname)
{

}

void CDelegationGen::genDelegator(CString dname, CString dreg, CString dmethod)
{

}
