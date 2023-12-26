#include "..\Actions\SelectAction.h"


Select::Select(ApplicationManager* pApp,bool flg ) :Action(pApp)
{
	isSelectButton = flg;
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
			selectedID = selectedFigure->GetID();
			wasUnselected = true;
			return;
		}
		pManager->UnselectAll();
		
		selectedFigure->SetSelected(true);
		pManager->UpdateInterface();
		if (isSelectButton)
		{
			selectedFigure->PrintInfo(pOut);

			
			pIn->GetButtonState(LEFT_BUTTON, P0.x, P0.y); // Resize by dragging
			bool0 = pOut->ResizeByDraggingOutput0(P0); // First Point clicked, returns true if the point is in the drawing area, so the user can resize the shape
			if (P0.y < UI.ToolBarHeight)
				return;
			while (bool0 && bool1)
			{
				pOut->PrintMessage("Resizing the shape.");
				bool1 = pOut->ResizeByDraggingOutput1(P1); // Second Point clicked, that's the point that moves while resizing, returns true if the point is in the drawing area, so the user can resize the shape
				selectedFigure->ResizeByDragging(P1);
				pManager->UpdateInterface();
				Sleep(75);
			}
			selectedFigure->SetSelected(false);
			pManager->UpdateInterface();
		}
		selectedID = selectedFigure->GetID();
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
