#include "AddHexagonAction.h"


AddHexagonAction::AddHexagonAction(ApplicationManager* pApp):Action(pApp)
{
}

void AddHexagonAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Hexagon: Click at center");

	//Read center and store in point center
	pIn->GetPointForDrawing(center.x, center.y, pOut);
	HexagonGfxInfo.isFilled = UI.FillColor != UI.ToolBarColor;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	HexagonGfxInfo.DrawClr = pOut->getCrntDrawColor();
	HexagonGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}

void AddHexagonAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a rectangle with the parameters read from the user
	CHexagon* hexa = new CHexagon(center,HexagonGfxInfo);

	//Add the rectangle to the list of figures
	pManager->AddFigure(hexa);

}
void AddHexagonAction::UndoAction()
{
	CFigure* LastDrawnHexagon = pManager->GetTheLastDrawnObject(ApplicationManager::DRAWN);
	LastDrawnHexagon->SetSelected(true);
	AddDeleteAction* pDelete = new AddDeleteAction(pManager);
	pDelete->Execute();
	delete LastDrawnHexagon;
	delete pDelete;
	LastDrawnHexagon = NULL;
	pDelete = NULL;
}