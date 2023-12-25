#include "AddRectAction.h"


AddRectAction::AddRectAction(ApplicationManager * pApp):Action(pApp)
{
	voice = "Sound\\Rectangle.wav";
}

void AddRectAction::RedoAction()
{
	if (!copyLastDrawnRect)
	{
		LastDrawnRect->showFigure(true);
		LastDrawnRect->SetDelete(false);
		pManager->RedoProcessDeletedFigures(LastDrawnRect);
		pManager->AddFigure(LastDrawnRect);
	}
	else
	{
		copyLastDrawnRect->showFigure(true);
		copyLastDrawnRect->SetDelete(false);
		pManager->RedoProcessDeletedFigures(copyLastDrawnRect);
		pManager->AddPlayRecordingFigure(copyLastDrawnRect);
	}
}

void AddRectAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	copyLastDrawnRect = NULL;

	pOut->PrintMessage("New Rectangle: Click at first corner, right-click to cancel operation");
	
	//Read 1st corner and store in point P1
	clicktype cType;
	cType = pIn->GetPointForDrawing(P1.x, P1.y, pOut);
	if (cType == RIGHT_CLICK)
	{
		isCanceled = true;
		return;
	}

	pOut->PrintMessage("New Rectangle: Click at second corner, right-click to cancel operation");

	//Read 2nd corner and store in point P2
	cType = pIn->GetPointForDrawing(P2.x, P2.y, pOut);
	if (cType == RIGHT_CLICK)
	{
		isCanceled = true;
		return;
	}
	RectGfxInfo.isFilled = UI.FillColor != UI.DefaultFillColor;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}
void AddRectAction::PlayRecordingFunc()
{
	copyLastDrawnRect = new CRectangle(P1, P2, RectGfxInfo);

	pManager->AddPlayRecordingFigure(copyLastDrawnRect);
}
void AddRectAction::UndoAction()
{
	LastDrawnRect->showFigure(false);
	LastDrawnRect->SetDelete(true);
	if (copyLastDrawnRect)
	{
		copyLastDrawnRect->showFigure(false);
		copyLastDrawnRect->SetDelete(true);
	}
	pManager->ProcessDeletedFigures();
}
//Execute the action
void AddRectAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (isCanceled) {
		pOut->PrintMessage("Successfully canceled the operation.");
		return;
	}
	//Create a rectangle with the parameters read from the user
	LastDrawnRect = new CRectangle(P1, P2, RectGfxInfo);

	//Add the rectangle to the list of figures
	pManager->AddFigure(LastDrawnRect);
}
