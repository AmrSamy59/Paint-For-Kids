#include "DrawColorAction.h"

DrawColorAction::DrawColorAction(ApplicationManager* pApp) : Action(pApp)
{
	SelectedFigure = NULL;
	drawColor = NULL;
}


void DrawColorAction::ReadActionParameters()
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
		drawColor = &(UI.drawColorsEq[ActType - DRAW_COLOR_0]);
	}
	else
	{
		pOut->PrintMessage("No figure is selected");
	}
}

void DrawColorAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (!SelectedFigure || !drawColor) {
		return;
	}

	UI.DrawColor = *drawColor;

	SelectedFigure->ChngDrawClr(*drawColor);

	string colorName = pOut->GetColorName(*drawColor);
	SelectedFigure->SetSelected(false);
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Successfully changed the drawing color to: " + colorName);

}

void DrawColorAction::UndoAction()
{
}


DrawColorAction::~DrawColorAction()
{
	SelectedFigure = NULL;
	drawColor = NULL;
}
