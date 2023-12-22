#include "AddSquareAction.h"


AddSquareAction::AddSquareAction(ApplicationManager* pApp) :Action(pApp)
{}
void AddSquareAction::RedoAction()
{
	LastDrawnSquare->SetFigureAbilityToBeDrawn(true);
}
void AddSquareAction::ReadActionParameters()
{
	// two pointer one to output and another for input
	Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();
	pout->PrintMessage("New Square: Click for center, right-click to cancel operation");
	///////////// read center for square //////////////////
	clicktype cType;
	cType = pin->GetPointForDrawing(CENTER.x, CENTER.y, pout);
	if (cType == RIGHT_CLICK)
	{
		isCanceled = true;
		return;
	}
	

	squareGfxInfo.isFilled = UI.FillColor != UI.DefaultFillColor;  //default is not filled

	squareGfxInfo.DrawClr = pout->getCrntDrawColor();
	squareGfxInfo.FillClr = pout->getCrntFillColor();

	pout->ClearStatusBar();

}

void AddSquareAction::PlayRecordingFunc()
{
	pManager->AddFigure(LastDrawnSquare);
}

void AddSquareAction::Execute()
{ //This action needs to read some parameters first
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (isCanceled) {
		pOut->PrintMessage("Successfully canceled the operation.");
		return;
	}
	//create new square
	LastDrawnSquare = new CSquare(CENTER, squareGfxInfo);
	// add square to list of figures 
	pManager->AddFigure(LastDrawnSquare);
}
void AddSquareAction::UndoAction()
{
	LastDrawnSquare->SetFigureAbilityToBeDrawn(false);
}
