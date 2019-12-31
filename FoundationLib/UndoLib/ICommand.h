// ICommand.h: interface for the ICommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICOMMAND_H__EBD2389E_BD4E_499A_88B9_5A2D85CBE299__INCLUDED_)
#define AFX_ICOMMAND_H__EBD2389E_BD4E_499A_88B9_5A2D85CBE299__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ICommand  
{
public:
	ICommand();
	virtual ~ICommand();

	virtual void execute();
	virtual void redo();
	virtual void undo();

};

#endif // !defined(AFX_ICOMMAND_H__EBD2389E_BD4E_499A_88B9_5A2D85CBE299__INCLUDED_)
