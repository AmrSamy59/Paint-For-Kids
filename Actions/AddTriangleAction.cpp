#include "AddTriangleAction.h"


AddTriangleAction::AddTriangleAction(ApplicationManager* pApp):Action(pApp)
{
	voice = "Sound\\Triangle.wav";
}
void AddTriangleAction::RedoAction()
{
	LastDrawnTriangle->SetFigureAbilityToBeDrawn(true);
	LastDrawnTriangle->SetDelete(false);
	pManager->AddFigure(LastDrawnTriangle);
}
void AddTriangleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New triangle: Click at first vertex, right-click to cancel operation");

	clicktype cType;
	cType = pIn->GetPointForDrawing(p1.x, p1.y, pOut);
	if (cType == RIGHT_CLICK)
	{
		isCanceled = true;
		return;
	}
	//Read 1st vertx and store in point P1
	

	pOut->PrintMessage("New triangle: Click at second vertex, right-click to cancel operation");

	//Read 2nd vertx and store in point P2
	
	cType = pIn->GetPointForDrawing(p2.x, p2.y, pOut);
	if (cType == RIGHT_CLICK)
	{
		isCanceled = true;
		return;
	}

	pOut->PrintMessage("New triangle: Click at thrid vertex, right-click to cancel operation");

	//Read 3th vertx and store in point P2
	
	cType = pIn->GetPointForDrawing(p3.x, p3.y, pOut);
	if (cType == RIGHT_CLICK)
	{
		isCanceled = true;
		return;
	}

	triangleGfxInfo.isFilled = UI.FillColor != UI.DefaultFillColor;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	triangleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	triangleGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}

void AddTriangleAction::PlayRecordingFunc()
{
	copyLastDrawnTriangle = new CTriangle(p1, p2, p3, triangleGfxInfo, pManager->CheckZeroID());
	if (pManager->CheckZeroID())
	{
		pManager->SetZeroID(false);
	}
	pManager->AddPlayRecordingFigure(copyLastDrawnTriangle);
}

void AddTriangleAction::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (isCanceled) {
		pOut->PrintMessage("Successfully canceled the operation.");
		return;
	}

	//Create a triangle with the parameters read from the user
	LastDrawnTriangle = new CTriangle(p1, p2,p3, triangleGfxInfo, pManager->CheckZeroID());
	if (pManager->CheckZeroID())
	{
		pManager->SetZeroID(false);
	}

	//Add the triandle to the list of figures
	pManager->AddFigure(LastDrawnTriangle);

}
void AddTriangleAction::UndoAction()
{
	LastDrawnTriangle->SetFigureAbilityToBeDrawn(false);
	LastDrawnTriangle->SetDelete(true);
	pManager->DeleteFigureComplete();
}
