// IStatuteStatusGraphBuilder.h: interface for the IStatuteStatusGraphBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISTATUTESTATUSGRAPHBUILDER_H__3B7BEDAB_F9B2_43CD_901F_3409FAFDE665__INCLUDED_)
#define AFX_ISTATUTESTATUSGRAPHBUILDER_H__3B7BEDAB_F9B2_43CD_901F_3409FAFDE665__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;

class IStatuteStatusGraphBuilder  
{
public:
	IStatuteStatusGraphBuilder(){};
	IStatuteStatusGraphBuilder(std::string text, std::string statuteSymbol="=>", std::string lineSplitter="\r\n")
		: m_text(""), m_statuteSymbol("=>"), m_lineSplitter("\r\n"){};
	virtual ~IStatuteStatusGraphBuilder(){};

	virtual int build()=0;

protected:
	std::string m_text;
	std::string m_statuteSymbol;
	std::string m_lineSplitter;
};

#endif // !defined(AFX_ISTATUTESTATUSGRAPHBUILDER_H__3B7BEDAB_F9B2_43CD_901F_3409FAFDE665__INCLUDED_)
