#include "AddHexagonAction.h"


AddHexagonAction::AddHexagonAction(ApplicationManager* pApp):Action(pApp)
{
	voice = "Sound\\Hexagon.wav";
}
void AddHexagonAction::RedoAction()
{
	LastDrawnHexagon->SetFigureAbilityToBeDrawn(true);
	LastDrawnHexagon->SetDelete(false);
	pManager->AddFigure(LastDrawnHexagon);
}
void AddHexagonAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Hexagon: Click at center, right-click to cancel operation");

	//Read center and store in point center
	clicktype cType;
	cType = pIn->GetPointForDrawing(center.x, center.y, pOut);
	if (cType == RIGHT_CLICK)
	{
		isCanceled = true;
		return;
	}
	HexagonGfxInfo.isFilled = UI.FillColor != UI.DefaultFillColor;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	HexagonGfxInfo.DrawClr = pOut->getCrntDrawColor();
	HexagonGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}

void AddHexagonAction::PlayRecordingFunc()
{
	copyLastDrawnHexagon = new CHexagon(center, HexagonGfxInfo, pManager->CheckZeroID());
	if (pManager->CheckZeroID())
	{
		pManager->SetZeroID(false);
	}
	pManager->AddPlayRecordingFigure(copyLastDrawnHexagon);
}

void AddHexagonAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (isCanceled) {
		pOut->PrintMessage("Successfully canceled the operation.");
		return;
	}

	//Create a rectangle with the parameters read from the user
	LastDrawnHexagon = new CHexagon(center,HexagonGfxInfo, pManager->CheckZeroID());
	if (pManager->CheckZeroID())
	{
		pManager->SetZeroID(false);
	}

	//Add the rectangle to the list of figures
	pManager->AddFigure(LastDrawnHexagon);

}
void AddHexagonAction::UndoAction()
{
	LastDrawnHexagon->SetFigureAbilityToBeDrawn(false);
	LastDrawnHexagon->SetDelete(true);
	pManager->DeleteFigureComplete();
}