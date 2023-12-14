#include "FillColorAction.h"

FillColorAction::FillColorAction(ApplicationManager* pApp) : Action(pApp)
{
	SelectedFigure = NULL;
	fillColor = NULL;
}


void FillColorAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	while (1)
	{
		SelectedFigure = pManager->GetSelectedFigure();
		if (SelectedFigure == NULL)
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

	if (SelectedFigure != NULL)
	{
		pOut->PrintMessage("Please select a color");
		
		ActionType ActType = pManager->GetUserAction();
		while ((ActType < DRAW_COLOR_0) || (ActType > DRAW_COLOR_0 + (UI.c_rows * UI.c_cols) - 1)) {
			ActionType ActType = pManager->GetUserAction();
		}
		fillColor = &(UI.drawColorsEq[ActType - DRAW_COLOR_0]);
	}
	else
	{
		pOut->PrintMessage("No figure is selected");
	}
}

void FillColorAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (!SelectedFigure || !fillColor) {
		return;
	}

	UI.FillColor = *fillColor;

	SelectedFigure->ChngFillClr(*fillColor);

	string colorName = pOut->GetColorName(*fillColor);
	SelectedFigure->SetSelected(false);
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Successfully changed the filling color to: " + colorName);

}

void FillColorAction::UndoAction()
{
}


FillColorAction::~FillColorAction()
{
	SelectedFigure = NULL;
	fillColor = NULL;
}
