// ICommandManager.cpp: implementation of the ICommandManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UndoTest.h"
#include "ICommandManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ICommandManager::ICommandManager()
{

}

ICommandManager::~ICommandManager()
{

}

void ICommandManager::execute(ICommand *command)
{
	command->execute();
	m_undoStack.push(command);
	clear(m_redoStack);
}

void ICommandManager::redo()
{
	if(m_redoStack.empty())
		return;

	ICommand *command=m_redoStack.top();
	m_redoStack.pop();
	command->redo();
	m_undoStack.push(command);
}

void ICommandManager::undo()
{
	if(m_undoStack.empty())
		return;

	ICommand *command=m_undoStack.top();
	m_undoStack.pop();
	command->undo();
	m_redoStack.push(command);
}

void ICommandManager::redoList(unsigned int count)
{
	if(count==0)
		return;

	if(m_redoStack.empty())
		return;

	if(count>=m_redoStack.size())
		count=m_redoStack.size()-1;

	for(int i=0;i<count;i++)
		redo();
}

void ICommandManager::undoList(unsigned int count)
{
	if(count==0)
		return;

	if(m_undoStack.empty())
		return;
	
	if(count>=m_undoStack.size())
		count=m_undoStack.size()-1;

	for(int i=0;i<m_undoStack.size();i++)
		undo();
}

void ICommandManager::clearAllCommands()
{
	clear(m_redoStack);
	clear(m_undoStack);
}

void ICommandManager::clear(std::stack<ICommand *> &s)
{
	for(int i=0;i<s.size();i++)
	{
		ICommand *command=s.top();
		delete command;
		s.pop();
	}
}
