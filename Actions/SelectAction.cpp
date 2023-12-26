#include "..\Actions\SelectAction.h"


Select::Select(ApplicationManager* pApp,bool flg ) :Action(pApp)
{
	flag = flg;
	voice = "Sound\\Shape Selected.wav";
	selectedID = -1;
	wasUnselected = false;
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
	Point P0;
	Point P1;
	bool bool0;
	bool bool1 = true;
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
	selectedFigure = pManager->GetFigure(Ps.x, Ps.y);
	if (selectedFigure != NULL)
	{
		if (pManager->GetSelectedFigure() == selectedFigure) {
			selectedFigure->SetSelected(false);
			pOut->PrintMessage("Successfully unselected the figure.");
			wasUnselected = true;
			return;
		}
		pManager->UnselectAll();
		
		// mo
		selectedFigure->SetSelected(true);
		selectedID = selectedFigure->GetID();
		pManager->UpdateInterface();
		if (flag)
		{
			selectedFigure->PrintInfo(pOut);
			bool0 = pOut->ResizeByDraggingOutput0(P0);
			if (P0.y < UI.ToolBarHeight)
				return;
			Sleep(4);
			pOut->ResizeByDraggingOutput1(P1);
			if (P1.x == P0.x && P1.y == P0.y)
			{
				selectedFigure->SetSelected(false);
				pManager->UpdateInterface();
				return;
			}
			while (bool0 && bool1)
			{
				bool1 = pOut->ResizeByDraggingOutput1(P1);
				selectedFigure->ResizeByDragging(P0, P1);
				pManager->UpdateInterface();
				Sleep(75);
			}
			selectedFigure->SetSelected(false);
			pManager->UpdateInterface();
		}
	}
	else {
		isCanceled = true;
		pManager->GetOutput()->PrintMessage("No object was selected.");
	}
}
void Select::PlayRecordingFunc()
{
	if (!isCanceled && selectedID != -1) {
		pManager->PlayRecordingSelect(selectedID)->SetSelected(!wasUnselected);
	}
		
}
void Select::UndoAction()
{

}
void Select::RedoAction()
{

}
