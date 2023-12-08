#include "AddDeleteAction.h"
#include "GUI\Output.h"
#include "GUI/Input.h"
#include "ApplicationManager.h"
#include "Select.h"

AddDeleteAction::AddDeleteAction(ApplicationManager* pApp):Action(pApp)
{

}
void AddDeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	while (1)
	{
		Selected_Figure = pManager->GetSelectedFigure();
		if (Selected_Figure == NULL)
		{
			Select* Sel = new Select(pManager);
			Sel->Execute();
			delete Sel;
			Sel = NULL;
			pOut->ClearStatusBar();
		}
		else
			break;
	}

}
//Add delete to the ApplicationManager
void AddDeleteAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	Selected_Figure->SetFigureAbilityToBeDrawn(false);
	pOut->PrintMessage("Figure has been deleted succesfully");
}
void AddDeleteAction::UndoAction()
{

}