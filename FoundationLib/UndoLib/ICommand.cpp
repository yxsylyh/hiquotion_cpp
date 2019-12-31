// ICommand.cpp: implementation of the ICommand class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UndoTest.h"
#include "ICommand.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ICommand::ICommand()
{

}

ICommand::~ICommand()
{

}

void ICommand::execute()
{

}

void ICommand::redo()
{
	execute();
}

void ICommand::undo()
{

}
