#include "FillColorAction.h"

FillColorAction::FillColorAction(ApplicationManager* pApp) : Action(pApp)
{
	SelectedFigure = NULL;
	isFilled[0] = false;
	isFilled[1] = false;
}
void FillColorAction::RedoAction()
{
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
		isFilled[0] = SelectedFigure->GetFilledStatus();
		fillColor[0] = &(SelectedFigure->GetLastFigFilledColor());
		pOut->PrintMessage("Please select a color");
		
		ActionType ActType = pManager->GetUserAction();
		while ((ActType < DRAW_COLOR_0) || (ActType > DRAW_COLOR_0 + (UI.c_rows * UI.c_cols) - 1)) {
			ActionType ActType = pManager->GetUserAction();
		}
		fillColor[1] = &(UI.drawColorsEq[ActType - DRAW_COLOR_0]);
		
	}
	else
	{
		pOut->PrintMessage("No figure is selected");
	};
}

void FillColorAction::Execute()
{
	int i = 0;
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	
	if (!SelectedFigure || !fillColor[1]) {
		return;
	}
	UI.FillColor = *fillColor[1];
	if (i++ % 2 == 1 || i == 1)
		*fillColor[0] = *fillColor[1];
	SelectedFigure->ChngFillClr(*fillColor[1]);

	string colorName = pOut->GetColorName(*fillColor[1]);
	SelectedFigure->SetSelected(false);
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Successfully changed the filling color to: " + colorName);
}

void FillColorAction::UndoAction()
{
	if (isFilled[0] == false)
	{
		SelectedFigure->SetFilledStatus(false);
	}
	else
	{
		SelectedFigure->ChngFillClr(*fillColor[0]);
	}
	UI.FillColor = *fillColor[0];
}


FillColorAction::~FillColorAction()
{
	//SelectedFigure = NULL;
	
}
