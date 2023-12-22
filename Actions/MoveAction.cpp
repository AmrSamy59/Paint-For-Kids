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
		pOut->PrintMessage("The figure is attached to your cursor, left-click anywhere to keep the new position, right-click to cancel.");
		//pOut->PrintMessage("Please set the new center of the selected figure");
		//pIn->GetPointClicked(Pf[1].x, Pf[1].y);
		//pOut->ClearStatusBar();
	}
	else
	{
		pOut->PrintMessage("No figure is selected");
	}
}

void Move::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	fig = pManager->GetSelectedFigure();
	if (fig != NULL)
	{
		int x, y;
		while (1) {
			buttonstate leftClick = pIn->GetButtonState(LEFT_BUTTON, x, y);
			buttonstate rightClick = pIn->GetButtonState(RIGHT_BUTTON, x, y);
			if (x > 0 && x < UI.width && y > UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight) {
				Pf[1].x = x;
				Pf[1].y = y;
				fig->Move(Pf[1]);
				pManager->UpdateInterface();
			}
			if (leftClick == BUTTON_DOWN)
			{
				fig->Move(Pf[1]);
				pManager->UpdateInterface();
				pOut->PrintMessage("Successfully changed figure location.");
				break;
			}
			else if (rightClick == BUTTON_DOWN)
			{
				fig->Move(Pf[0]);
				pManager->UpdateInterface();
				pOut->PrintMessage("Successfully canceled the operation.");
				break;
			}
			Sleep(5); // 5ms delay, to avoid hogging the CPU
		}
		
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