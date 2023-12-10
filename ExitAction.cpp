#include "ExitAction.h"
#include "ApplicationManager.h"


Exit::Exit(ApplicationManager* pApp) : Action(pApp)
{}

void Exit::ReadActionParameters() {}

void Exit::Execute()
{
	exit(0);
}

void Exit::UndoAction()
{}
