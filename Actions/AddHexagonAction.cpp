#include "AddHexagonAction.h"


AddHexagonAction::AddHexagonAction(ApplicationManager* pApp):Action(pApp)
{
	voice = "Sound\\Hexagon.wav";
}
void AddHexagonAction::RedoAction()
{
	if (!copyLastDrawnHexagon)
	{
		LastDrawnHexagon->showFigure(true);
		LastDrawnHexagon->SetDelete(false);
		pManager->RedoProcessDeletedFigures(LastDrawnHexagon);
		pManager->AddFigure(LastDrawnHexagon);
	}
	else
	{
		copyLastDrawnHexagon->showFigure(true);
		copyLastDrawnHexagon->SetDelete(false);
		pManager->RedoProcessDeletedFigures(copyLastDrawnHexagon);
		pManager->AddPlayRecordingFigure(copyLastDrawnHexagon);
	}
}
void AddHexagonAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	copyLastDrawnHexagon = NULL;

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
	copyLastDrawnHexagon = new CHexagon(center, HexagonGfxInfo);
	CHexagon::DecreaseCount();
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
	LastDrawnHexagon = new CHexagon(center,HexagonGfxInfo);

	//Add the rectangle to the list of figures
	pManager->AddFigure(LastDrawnHexagon);

}
void AddHexagonAction::UndoAction()
{
	LastDrawnHexagon->showFigure(false);
	LastDrawnHexagon->SetDelete(true);
	if (copyLastDrawnHexagon)
	{
		copyLastDrawnHexagon->showFigure(false);
		copyLastDrawnHexagon->SetDelete(true);
	}
	pManager->ProcessDeletedFigures();
}