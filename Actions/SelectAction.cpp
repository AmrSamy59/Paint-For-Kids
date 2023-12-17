#include "..\Actions\SelectAction.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
#include "..\ApplicationManager.h"

Select::Select(ApplicationManager* pApp) :Action(pApp)
{}
void Select::RedoAction()
{

}
void Select::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	pOut->PrintMessage("Click on a figure to select it.");

	pIn->GetPointClicked(Ps.x, Ps.y);
	pOut->ClearStatusBar();
}

void Select::Execute()
{
	ReadActionParameters();	 
	if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
	{
		CFigure *selectedFigure = pManager->GetFigure(Ps.x, Ps.y);
		selectedFigure->SetSelected(true);
		pManager->UpdateInterface();
	}
	else {
		pManager->GetOutput()->PrintMessage("No object was selected.");
	}
}
void Select::UndoAction()
{

}
