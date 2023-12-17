#include "RedoActionClass.h"

RedoActionClass::RedoActionClass(ApplicationManager* pApp):Action(pApp)
{

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
	cout << "Passed Action:"<< PassedAction << endl;
	if (PassedAction)
	{
		PassedAction->RedoAction();
		/*if (dynamic_cast<AddRectAction*>(PassedAction) != NULL || dynamic_cast<AddSquareAction*>(PassedAction) != NULL
			|| dynamic_cast<AddHexagonAction*>(PassedAction) != NULL || dynamic_cast<AddCircleAction*>(PassedAction) != NULL
			|| dynamic_cast<AddTriangleAction*>(PassedAction) != NULL)
		{
			pManager->AddFigure(PassedFigure);
		}*/
		pManager->AddForUndoAction(PassedAction,false);
		pManager->SetRedoActionToNull(PassedAction);
	}
}
