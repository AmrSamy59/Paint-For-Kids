#include "AddRectAction.h"


AddRectAction::AddRectAction(ApplicationManager * pApp):Action(pApp)
{}

void AddRectAction::RedoAction()
{
	LastDrawnRect->SetFigureAbilityToBeDrawn(true);
}

void AddRectAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Rectangle: Click at first corner");
	
	//Read 1st corner and store in point P1
	pIn->GetPointForDrawing(P1.x, P1.y, pOut);

	pOut->PrintMessage("New Rectangle: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointForDrawing(P2.x, P2.y, pOut);

	RectGfxInfo.isFilled = UI.FillColor != UI.DefaultFillColor;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}
void AddRectAction::PlayRecordingFunc()
{
	pManager->AddFigure(LastDrawnRect);
}
void AddRectAction::UndoAction()
{
	LastDrawnRect->SetFigureAbilityToBeDrawn(false);
}
//Execute the action
void AddRectAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a rectangle with the parameters read from the user
	LastDrawnRect = new CRectangle(P1, P2, RectGfxInfo);
	
	//Add the rectangle to the list of figures
	pManager->AddFigure(LastDrawnRect);
}
