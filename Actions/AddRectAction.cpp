#include "AddRectAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "../Figures/CRectangle.h"
#include "../DeleteAction.h"
#include "../Figures/CFigure.h"

AddRectAction::AddRectAction(ApplicationManager * pApp):Action(pApp)
{}

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

	RectGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}
void AddRectAction::UndoAction()
{
	CFigure* LastDrawnRect = pManager->GetTheLastDrawnObject();
	LastDrawnRect->SetSelected(true);
	AddDeleteAction* pDelete = new AddDeleteAction(pManager);
	pDelete->Execute();
	delete LastDrawnRect;
	delete pDelete;
	LastDrawnRect = NULL;
	pDelete = NULL;
}
//Execute the action
void AddRectAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a rectangle with the parameters read from the user
	CRectangle* R = new CRectangle(P1, P2, RectGfxInfo);
	
	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
}
