#include "MoveAction.h"


Move::Move(ApplicationManager* pApp) : Action(pApp)
{}

void Move::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	while (1)
	{
		if (pManager->GetSelectedFigure() == NULL)
		{
			Select* Sel = new Select(pManager);
			Sel->Execute();
			delete Sel;
			Sel = NULL;
			pOut->ClearStatusBar();
		}
		else
			break;
	}
	if (pManager->GetSelectedFigure() != NULL)
	{
		pOut->PrintMessage("Please set the new center of the selected figure");
		pIn->GetPointForDrawing(Pf.x, Pf.y, pOut);
		pOut->ClearStatusBar();
	}
	else
	{
		pOut->PrintMessage("No figure is selected");
	}
}

void Move::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (pManager->GetSelectedFigure() != NULL) {
		pManager->GetSelectedFigure()->Move(pOut, Pf);
		pManager->GetSelectedFigure()->SetSelected(false);
	}
	
	
}
void Move::UndoAction()
{

}