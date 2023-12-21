#include "AddCircleAction.h"


AddCircleAction::AddCircleAction(ApplicationManager* pApp):Action(pApp)
{
}
void AddCircleAction::PlayRecordingFunc()
{
	pManager->AddFigure(LastDrawnCircle);
}
void AddCircleAction::RedoAction()
{
	LastDrawnCircle->SetFigureAbilityToBeDrawn(true);
}
void AddCircleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at first point");

	//Read 1st point and store in point P1
	pIn->GetPointForDrawing(P1.x, P1.y, pOut);

	pOut->PrintMessage("New Circle: Click at second point");

	//Read 2nd point and store in point P2
	pIn->GetPointForDrawing(P2.x, P2.y, pOut);

	CircleGfxInfo.isFilled = UI.FillColor != UI.DefaultFillColor;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	CircleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircleGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

void AddCircleAction::Execute()
{
	ReadActionParameters();

	//Create a circle with the parameters read from the user
	int radius = int(sqrt(double((P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y))));
	LastDrawnCircle = new CCircle(P1, radius, CircleGfxInfo);
	CCircle* ptr=nullptr;
//	copyLastDrawnCircle = ptr->SaveCopyOfFigure();
	//Add the rectangle to the list of figures
	pManager->AddFigure(LastDrawnCircle);
	//pManager->AddFigureplay(copyLastDrawnCircle);
}
void AddCircleAction::UndoAction()
{
	LastDrawnCircle->SetFigureAbilityToBeDrawn(false);
}