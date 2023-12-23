#include "DrawColorAction.h"

DrawColorAction::DrawColorAction(ApplicationManager* pApp) : Action(pApp)
{
	SelectedFigure = NULL;
	voice = "Sound\\Draw Color Changed.wav";
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

			if (Sel->wasCanceled())
			{
				delete Sel;
				Sel = NULL;
				return;
			}
			if (Sel) {
				delete Sel;
				Sel = NULL;
			}
		}
		else
			break;
	}
	if (SelectedFigure != NULL)
	{
		selectedID = SelectedFigure->GetID();
		c_drawColor = SelectedFigure->GetDrawColor();
		pOut->PrintMessage("Please select a color, right-click to cancel operation.");
		
		ActionType ActType = pManager->GetUserAction();
		if (ActType == OPERATION_CANCELED)
			isCanceled = true;

		while (!isCanceled && ((ActType < DRAW_COLOR_0) || (ActType > DRAW_COLOR_0 + (UI.c_rows * UI.c_cols) - 1))) {
			ActType = pManager->GetUserAction();
		}
		drawColor = (UI.drawColorsEq[ActType - DRAW_COLOR_0]);
	}

}

void DrawColorAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigsCount() == 0) {
		pOut->PrintMessage("No figures to change their drawing color");
		return;
	}
	ReadActionParameters();
	if (isCanceled) {
		pOut->PrintMessage("Successfully canceled the operation.");
		if (SelectedFigure) {
			SelectedFigure->SetSelected(false);
		}
		return;
	}
	if (!SelectedFigure || !&drawColor) {
		return;
	}

	UI.DrawColor = drawColor != UI.DefaultFillColor ? drawColor : UI.DefaultDrawColor;

	SelectedFigure->ChngDrawClr(drawColor);

	string colorName = pOut->GetColorName(drawColor);
	SelectedFigure->SetSelected(false);
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Successfully changed the drawing color to: " + colorName);

}

void DrawColorAction::PlayRecordingFunc()
{
	Output* pOut = pManager->GetOutput();
	UI.DrawColor = drawColor != UI.DefaultFillColor ? drawColor : UI.DefaultDrawColor;
	pOut->CreateDrawToolBar();
	pManager->PlayRecordingSelect(selectedID)->ChngDrawClr(drawColor);
	pManager->PlayRecordingSelect(selectedID)->SetSelected(false);
}

void DrawColorAction::UndoAction()
{
	if (c_drawColor == false)
	{
		SelectedFigure->SetFilledStatus(false);
	}
	else
	{
		SelectedFigure->ChngDrawClr(c_drawColor);
	}
	UI.DrawColor = c_drawColor;
	pManager->GetOutput()->CreateDrawToolBar();
}

void DrawColorAction::RedoAction()
{
	if (drawColor == false)
	{
		SelectedFigure->SetFilledStatus(false);
	}
	else
	{
		SelectedFigure->ChngDrawClr(drawColor);
	}
	UI.DrawColor = drawColor;
	pManager->GetOutput()->CreateDrawToolBar();
}

DrawColorAction::~DrawColorAction()
{
	SelectedFigure = NULL;
}
