// LogBuilderBase.h: interface for the CLogBuilderBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGBUILDERBASE_H__8B5172F6_3D2D_4AC5_B8E3_EA1DC4BC8E27__INCLUDED_)
#define AFX_LOGBUILDERBASE_H__8B5172F6_3D2D_4AC5_B8E3_EA1DC4BC8E27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLogBuilderBase  
{
public:
	CLogBuilderBase();
	virtual ~CLogBuilderBase();

	void ignoreLogLevelinConfig();

protected:
	BOOL m_ignoreLogLevelinConfig;
};

#endif // !defined(AFX_LOGBUILDERBASE_H__8B5172F6_3D2D_4AC5_B8E3_EA1DC4BC8E27__INCLUDED_)
