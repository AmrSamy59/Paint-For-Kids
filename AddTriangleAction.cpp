#include "AddTriangleAction.h"
#include"CTriangle.h"
#include"ApplicationManager.h"
#include"GUI/Input.h"
#include"GUI/Output.h"
#include "DeleteAction.h"

AddTriangleAction::AddTriangleAction(ApplicationManager* pApp):Action(pApp)
{
}

void AddTriangleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New triangle: Click at first vertex");

	//Read 1st vertx and store in point P1
	pIn->GetPointForDrawing(p1.x, p1.y, pOut);

	pOut->PrintMessage("New triangle: Click at second vertex");

	//Read 2nd vertx and store in point P2
	pIn->GetPointForDrawing(p2.x, p2.y, pOut);

	pOut->PrintMessage("New triangle: Click at thrid vertex");

	//Read 3th vertx and store in point P2
	pIn->GetPointForDrawing(p3.x, p3.y, pOut);


	triangleGfxInfo.isFilled = false;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	triangleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	triangleGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}

void AddTriangleAction::Execute()
{
	ReadActionParameters();

	//Create a triangle with the parameters read from the user
	CTriangle* T = new CTriangle(p1, p2,p3, triangleGfxInfo);

	//Add the triandle to the list of figures
	pManager->AddFigure(T);

}
void AddTriangleAction::UndoAction()
{
	CFigure* LastDrawnTriangle = pManager->GetTheLastDrawnObject(ApplicationManager::DRAWN);
	LastDrawnTriangle->SetSelected(true);
	AddDeleteAction* pDelete = new AddDeleteAction(pManager);
	pDelete->Execute();
	delete LastDrawnTriangle;
	delete pDelete;
	LastDrawnTriangle = NULL;
	pDelete = NULL;
}
