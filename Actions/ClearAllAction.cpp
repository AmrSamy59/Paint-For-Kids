#include "ClearAllAction.h"
#include "..\ApplicationManager.h"
#include "../GUI/Output.h"

AddClearAllAction::AddClearAllAction(ApplicationManager* pApp) :Action(pApp)
{
	voice = "Sound\\Clear all.wav";
}
void AddClearAllAction::RedoAction()
{
}
void AddClearAllAction::ReadActionParameters()
{
	
}

//Add delete to the ApplicationManager
void AddClearAllAction::Execute()
{
	Output* pOut;
	pOut = pManager->GetOutput();
		ReadActionParameters();
		pManager->ClearAll();
		while (CRectangle::GetCount() > 0)
		{
			CRectangle::DecreaseCount();
		}
		while (CCircle::GetCount() > 0)
		{
			CCircle::DecreaseCount();

		}
		while (CHexagon::GetCount() > 0)
		{
			CHexagon::DecreaseCount();
		}
		while (CSquare::GetCount() > 0)
		{
			CSquare::DecreaseCount();
		}
		while (CTriangle::GetCount() > 0)
		{
			CTriangle::DecreaseCount();
		}
		CFigure::ResetIDs(); // Reset IDs to 0
		UI.FillColor = UI.drawColorsEq[7];
		UI.DrawColor = UI.DefaultDrawColor;
		pOut->CreateDrawToolBar();
		pOut->PrintMessage("Clear successful!");
}
void AddClearAllAction::UndoAction()
{
	
}
