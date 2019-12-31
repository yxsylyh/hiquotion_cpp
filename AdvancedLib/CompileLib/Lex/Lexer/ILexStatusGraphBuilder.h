// ILexStatusGraphBuilder.h: interface for the ILexStatusGraphBuilder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ILEXSTATUSGRAPHBUILDER_H__07D15C4E_28A7_41EB_86AF_48059AB1D53B__INCLUDED_)
#define AFX_ILEXSTATUSGRAPHBUILDER_H__07D15C4E_28A7_41EB_86AF_48059AB1D53B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\LexStatusGraph\LexStatusGraph.h"

class ILexStatusGraphBuilder  
{
public:
	ILexStatusGraphBuilder(){};
	virtual ~ILexStatusGraphBuilder(){};

	virtual BOOL build()=0;

protected:
	CLexStatusGraph *m_graph;
};

#endif // !defined(AFX_ILEXSTATUSGRAPHBUILDER_H__07D15C4E_28A7_41EB_86AF_48059AB1D53B__INCLUDED_)
