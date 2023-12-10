#include "AddSquareAction.h"


AddSquareAction::AddSquareAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddSquareAction::ReadActionParameters()
{
	// two pointer one to output and another for input
	Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();
	pout->PrintMessage("New Square: Click for center");
	///////////// read center for square //////////////////
	pin->GetPointForDrawing(CENTER.x, CENTER.y, pout);

	squareGfxInfo.isFilled = false;  //default is not filled

	squareGfxInfo.DrawClr = pout->getCrntDrawColor();
	squareGfxInfo.FillClr = pout->getCrntFillColor();

	pout->ClearStatusBar();

}

void AddSquareAction::Execute()
{ //This action needs to read some parameters first
	ReadActionParameters();
	//create new square
	CSquare* sq = new CSquare(CENTER, squareGfxInfo);
	// add square to list of figures 
	pManager->AddFigure(sq);
}
void AddSquareAction::UndoAction()
{
	CFigure* LastDrawnSquare = pManager->GetTheLastDrawnObject(ApplicationManager::DRAWN);
	LastDrawnSquare->SetSelected(true);
	AddDeleteAction* pDelete = new AddDeleteAction(pManager);
	pDelete->Execute();
	delete LastDrawnSquare;
	delete pDelete;
	LastDrawnSquare = NULL;
	pDelete = NULL;
}
