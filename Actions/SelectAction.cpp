#include "..\Actions\SelectAction.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
#include "..\ApplicationManager.h"

Select::Select(ApplicationManager* pApp) :Action(pApp)
{
	voice = "Sound\\Shape Selected.wav";
	selectedID = -1;
}
bool Select::wasCanceled()
{
	return cType == RIGHT_CLICK;
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
	CFigure* selectedFigure;
	Point P1;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (pManager->GetFigsCount() == 0) {
		isCanceled = true;
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
		selectedFigure = pManager->GetFigure(Ps.x, Ps.y);
		selectedFigure->SetSelected(true);
		selectedID = selectedFigure->GetID();
		pManager->UpdateInterface();
	}
	else {
		isCanceled = true;
		pManager->GetOutput()->PrintMessage("No object was selected.");
	}
	/*while (1)
	{
		pOut->ResizeByDraggingOutput(P1);
		if (P1.y < UI.ToolBarHeight)
			break;

		selectedFigure->ResizeByDragging(P1);
		pManager->UpdateInterface();
		Sleep(100);
	}*/
}
void Select::PlayRecordingFunc()
{
	if(!isCanceled && selectedID != -1)
		pManager->PlayRecordingSelect(selectedID)->SetSelected(true);
}
void Select::UndoAction()
{

}
void Select::RedoAction()
{

}
