#include "FillColorAction.h"

FillColorAction::FillColorAction(ApplicationManager* pApp) : Action(pApp)
{
	SelectedFigure = NULL;
	isFilled = false;
	c_isFilled = false;
	voice = "Sound\\Fill Color Changed.wav";
}

void FillColorAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	while (1) // loop until a figure is selected, or the user cancels the operation
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
		c_isFilled = SelectedFigure->GetFilledStatus();
		c_fillColor = SelectedFigure->GetFillColor();
		pOut->PrintMessage("Please select a color, right-click to cancel operation.");
		
		ActionType ActType = pManager->GetUserAction();
		if(ActType == OPERATION_CANCELED)
			isCanceled = true;

		while (!isCanceled && ((ActType < DRAW_COLOR_0) || (ActType > DRAW_COLOR_0 + (UI.c_rows * UI.c_cols) - 1))) {
			ActType = pManager->GetUserAction();
			if (ActType == OPERATION_CANCELED)
				isCanceled = true;
		}
		fillColor = (UI.drawColorsEq[ActType - DRAW_COLOR_0]);
		if (fillColor != UI.DefaultFillColor) // if the user selected a color other than the default one, then the figure is filled
			isFilled = true;
		else
			isFilled = false;
	}

}

void FillColorAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigsCount() == 0) {
		pOut->PrintMessage("No figures to change their fill color");
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
	
	if (!SelectedFigure) {
		return;
	}


	UI.FillColor = fillColor; // change the fill color in the UI

	SelectedFigure->ChngFillClr(fillColor);

	string colorName = pOut->GetColorName(fillColor);
	SelectedFigure->SetSelected(false);
	pOut->CreateDrawToolBar(); // create the draw toolbar again to update the fill color button
	pOut->PrintMessage("Successfully changed the filling color to: " + colorName);
}

void FillColorAction::PlayRecordingFunc()
{
	Output* pOut = pManager->GetOutput();
	UI.FillColor = fillColor;
	pOut->CreateDrawToolBar();
	pManager->PlayRecordingSelect(selectedID)->ChngFillClr(fillColor);
	pManager->PlayRecordingSelect(selectedID)->SetSelected(false);
}

void FillColorAction::UndoAction()
{
	if (!pManager->PlayRecordingSelect(selectedID)) {
		SelectedFigure->ChngFillClr(c_fillColor);

		if (c_isFilled == false)
		{
			SelectedFigure->SetFilledStatus(false);
	
		}
	}
	else
	{
		pManager->PlayRecordingSelect(selectedID)->ChngFillClr(c_fillColor);
		if (c_isFilled == false)
		{
			pManager->PlayRecordingSelect(selectedID)->SetFilledStatus(false);
		}
	}
	UI.FillColor = c_fillColor;
	pManager->GetOutput()->CreateDrawToolBar();
}
void FillColorAction::RedoAction()
{
	if (!pManager->PlayRecordingSelect(selectedID)) {
		SelectedFigure->ChngFillClr(fillColor);

		if (isFilled == false)
		{
			SelectedFigure->SetFilledStatus(false);
		}
	}
	else
	{
		pManager->PlayRecordingSelect(selectedID)->ChngFillClr(fillColor);
		if (isFilled == false)
		{
			pManager->PlayRecordingSelect(selectedID)->SetFilledStatus(false);
		}

	}
	UI.FillColor = fillColor;
	pManager->GetOutput()->CreateDrawToolBar();
}
