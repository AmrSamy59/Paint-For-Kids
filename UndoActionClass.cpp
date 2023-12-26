#include "UndoActionClass.h"

#include <iostream>
using namespace std;

UndoActionClass::UndoActionClass(ApplicationManager* pApp):Action(pApp)
{
	PassedAction = NULL;
	voice = "Sound\\Undo.wav";
}

void UndoActionClass::UndoAction()
{

}
void UndoActionClass::PlayRecordingFunc()
{
	if (dynamic_cast<DeleteAction*>(pManager->PlayRecordingUndo(ActionID, selectingNum)))
	{
		DeleteAction* temp = (DeleteAction*)pManager->PlayRecordingUndo(ActionID, selectingNum);
		temp->setPlayRec(true);
	}
	pManager->PlayRecordingUndo(ActionID, selectingNum)->UndoAction();
}
int UndoActionClass::GetActionID()
{
	return ActionID;
}
void UndoActionClass::SetActionID(int id)
{
	ActionID = id;
}
void UndoActionClass::SetSelectingNum(int c)
{
	selectingNum = c;
}
void UndoActionClass::RedoAction()
{

}
void UndoActionClass::ReadActionParameters()
{
	PassedAction = pManager->ReturnLastAction();
}

void UndoActionClass::Execute()
{
	ReadActionParameters();
	if (PassedAction)
	{
		PassedAction->UndoAction();
		pManager->AddForRedoAction(PassedAction);
		pManager->SetActionToNull(PassedAction);
	}
}
