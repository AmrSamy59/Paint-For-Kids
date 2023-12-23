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
void UndoActionClass::RedoAction()
{

}
void UndoActionClass::ReadActionParameters()
{
	PassedAction = pManager->ReturnLastAction();
	/*if (dynamic_cast<DeleteAction*>(PassedAction))
		PassedFigure = pManager->ReturnLastFigureOnScreen(ApplicationManager::DELETED);
	else
		PassedFigure = pManager->ReturnLastFigureOnScreen(ApplicationManager::DRAWN);*/
}

void UndoActionClass::Execute()
{
	ReadActionParameters();
	if (PassedAction)
	{
		PassedAction->UndoAction();
		/*if (dynamic_cast<AddRectAction*>(PassedAction) != NULL || dynamic_cast<AddSquareAction*>(PassedAction) != NULL
			|| dynamic_cast<AddHexagonAction*>(PassedAction) != NULL || dynamic_cast<AddCircleAction*>(PassedAction) != NULL
			|| dynamic_cast<AddTriangleAction*>(PassedAction) != NULL)
		{
			cout << "Passed figure in undo passing to redo : " << PassedFigure << endl;
			pManager->AddFigToRedoFigList(PassedFigure);
			//pManager->SetFigureToNull(PassedFigure);
		}*/
		pManager->AddForRedoAction(PassedAction);
		pManager->SetActionToNull(PassedAction);
	}
}
