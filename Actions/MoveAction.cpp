#include "MoveAction.h"


Move::Move(ApplicationManager* pApp) : Action(pApp)
{
	
}



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
		Pf[0] = pManager->GetSelectedFigure()->GetFigureCenter();
		pOut->PrintMessage("Please set the new center of the selected figure");
		pIn->GetPointClicked(Pf[1].x, Pf[1].y);
		pOut->ClearStatusBar();
	}
	else
	{
		pOut->PrintMessage("No figure is selected");
	}
}

void Move::Execute()
{
	ReadActionParameters();
	fig = pManager->GetSelectedFigure();
	if (fig != NULL)
	{
		fig->Move(Pf[1]);
		fig->SetSelected(false);
	}
}
void Move::UndoAction()
{
	fig->Move(Pf[0]);
}
void Move::RedoAction()
{
	fig->Move(Pf[1]);
}