// ICommandManager.h: interface for the ICommandManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICOMMANDMANAGER_H__8E7185C2_1A04_416B_9669_899DAF1A747C__INCLUDED_)
#define AFX_ICOMMANDMANAGER_H__8E7185C2_1A04_416B_9669_899DAF1A747C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stack>
#include "ICommand.h"

class ICommandManager  
{
public:
	ICommandManager();
	virtual ~ICommandManager();

	virtual void execute(ICommand *command);
	virtual void redo();
	virtual void undo();
	virtual void redoList(unsigned int count);
	virtual void undoList(unsigned int count);
	virtual void clearAllCommands();

protected:
	virtual void clear(std::stack<ICommand *> &s);

protected:
	std::stack<ICommand *> m_redoStack;
	std::stack<ICommand *> m_undoStack;
	BOOL m_canUndo;
	BOOL m_canRedo;

};

#endif // !defined(AFX_ICOMMANDMANAGER_H__8E7185C2_1A04_416B_9669_899DAF1A747C__INCLUDED_)
