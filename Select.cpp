#include "Select.h"
#include "GUI\Output.h"
#include "GUI/Input.h"
#include "ApplicationManager.h"

Select::Select(ApplicationManager* pApp) :Action(pApp)
{}

void Select::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Please select a figure");

	pIn->GetPointClicked(Ps.x, Ps.y);
	pOut->ClearStatusBar();
}

void Select::Execute()
{
	ReadActionParameters();	 
	if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
	{
		CFigure* selectedFigure = pManager->GetFigure(Ps.x, Ps.y);
		selectedFigure->SetSelected(true);
	}
	
}
