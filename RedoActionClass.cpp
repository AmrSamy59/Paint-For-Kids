#include "RedoActionClass.h"

RedoActionClass::RedoActionClass(ApplicationManager* pApp):Action(pApp)
{
	voice = "Sound\\Redo.wav";
}

void RedoActionClass::UndoAction()
{

}

void RedoActionClass::RedoAction()
{

}

void RedoActionClass::ReadActionParameters()
{
	PassedAction = pManager->HandleAndReturnRedoActions();
}

void RedoActionClass::Execute()
{
	ReadActionParameters();

	if (PassedAction)
	{
		PassedAction->RedoAction();
		pManager->AddForUndoAction(PassedAction,false);
		pManager->SetRedoActionToNull(PassedAction);
	}
}
