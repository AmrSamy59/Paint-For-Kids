#include "DrawColorAction.h"

DrawColorAction::DrawColorAction(ApplicationManager* pApp) : Action(pApp)
{
	SelectedFigure = NULL;
	drawColor[0] = NULL;
	drawColor[1] = NULL;
}

void DrawColorAction::RedoAction()
{
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
		drawColor[0] = &(SelectedFigure->GetLastFigBorderColor());
		pOut->PrintMessage("Please select a color");
		
		ActionType ActType = pManager->GetUserAction();
		while ((ActType < DRAW_COLOR_0) || (ActType > DRAW_COLOR_0 + (UI.c_rows * UI.c_cols) - 1)) {
			ActionType ActType = pManager->GetUserAction();
		}
		drawColor[1] = &(UI.drawColorsEq[ActType - DRAW_COLOR_0]);
	}
	else
	{
		pOut->PrintMessage("No figure is selected");
	}
}

void DrawColorAction::Execute()
{
	int i = 0;
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (!SelectedFigure || !drawColor[1]) {
		return;
	}

	UI.DrawColor = *drawColor[1];
	if (i++ % 2 == 1 || i == 1)
		*drawColor[0] = *drawColor[1];
	SelectedFigure->ChngDrawClr(*drawColor[1]);

	string colorName = pOut->GetColorName(*drawColor[1]);
	SelectedFigure->SetSelected(false);
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Successfully changed the drawing color to: " + colorName);

}

void DrawColorAction::UndoAction()
{
	if (drawColor[0] == false)
	{
		SelectedFigure->SetFilledStatus(false);
	}
	else
	{
		SelectedFigure->ChngFillClr(*drawColor[0]);
	}
	UI.FillColor = *drawColor[0];
}


DrawColorAction::~DrawColorAction()
{
	SelectedFigure = NULL;
	drawColor[0] = NULL;
	drawColor[1] = NULL;
}
