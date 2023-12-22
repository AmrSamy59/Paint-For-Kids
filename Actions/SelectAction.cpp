#include "..\Actions\SelectAction.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
#include "..\ApplicationManager.h"

Select::Select(ApplicationManager* pApp) :Action(pApp)
{}
bool Select::wasCanceled()
{
	return cType == RIGHT_CLICK;
}
void Select::RedoAction()
{

}
void Select::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Click on a figure to select it, right-click to cancel operation.");

	cType = pIn->GetPointClicked(Ps.x, Ps.y);
	pOut->ClearStatusBar();
}

void Select::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigsCount() == 0) {
		pOut->PrintMessage("No figures to select");
		return;
	}
	ReadActionParameters();	 
	if (wasCanceled())
	{
		isCanceled = true;
		pOut->PrintMessage("Successfully canceled the operation.");
		return;
	}
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
