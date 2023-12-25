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

void RedoActionClass::SetActionID(int id)
{
	ActionID = id;
}
void RedoActionClass::SetSelectingNum(int c)
{
	selectingNum = c;
}

void RedoActionClass::PlayRecordingFunc()
{
	pManager->PlayRecordingUndo(ActionID, selectingNum)->RedoAction();
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
