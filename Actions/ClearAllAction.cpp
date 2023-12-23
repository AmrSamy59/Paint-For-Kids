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
	ReadActionParameters();
	pManager->ClearAll();
	UI.FillColor = UI.drawColorsEq[7];
	UI.DrawColor = UI.DefaultDrawColor;
	Output* pOut;
	pOut = pManager->GetOutput();
	pOut->CreateDrawToolBar();
	pOut->PrintMessage("Clear successful!");

}
void AddClearAllAction::UndoAction()
{
	
}
