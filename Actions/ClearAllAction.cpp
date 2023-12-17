#include "ClearAllAction.h"
#include "..\ApplicationManager.h"
#include "../GUI/Output.h"

AddClearAllAction::AddClearAllAction(ApplicationManager* pApp) :Action(pApp)
{

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
	Output* pOut;
	pOut = pManager->GetOutput();
	pOut->PrintMessage("Clear successful!");

}
void AddClearAllAction::UndoAction()
{
	
}
