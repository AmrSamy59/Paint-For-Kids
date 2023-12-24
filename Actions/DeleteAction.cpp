#include "..\Actions\DeleteAction.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
#include "..\ApplicationManager.h"
#include "..\Actions\SelectAction.h"


DeleteAction::DeleteAction(ApplicationManager* pApp):Action(pApp)
{
	voice = "Sound\\Shape Deleted.wav";
}

void DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	while (1)
	{
		Selected_Figure = pManager->GetSelectedFigure();
		if (Selected_Figure == NULL)
		{
			Select* Sel = new Select(pManager);
			Sel->Execute();

			if (Sel->wasCanceled())
			{
				delete Sel;
				Sel = NULL;
				return;
			}
			if (Sel) {
				delete Sel;
				Sel = NULL;
			}
		}
		else
			break;
	}
}
//Add delete to the ApplicationManager
void DeleteAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigsCount() == 0) {
		pOut->PrintMessage("No figures to delete");
		return;
	}
	ReadActionParameters();
	if (Selected_Figure == NULL)
	{
		return;
	}
	selectedID = Selected_Figure->GetID();
	Selected_Figure->setFigureHidden(false);
	Selected_Figure->SetSelected(false);
	Selected_Figure->SetDelete(true);
	pManager->ProcessDeletedFigures();

	pOut->PrintMessage("Figure has been deleted succesfully");
}
DeleteAction::~DeleteAction()
{
	pManager->SetFigureToNull(Selected_Figure);
	delete Selected_Figure;
	Selected_Figure = NULL;
}
void DeleteAction::UndoAction()
{
	if (Selected_Figure)
	{
		
		Selected_Figure->setFigureHidden(true);
		Selected_Figure->SetDelete(false);
		pManager->AddFigure(Selected_Figure);
		pManager->sortDeleteList();
		pManager->UndoProcessDeletedFigures(Selected_Figure);
	}
}
void DeleteAction::PlayRecordingFunc()
{
	pManager->PlayRecordingSelect(selectedID)->setFigureHidden(false);
	pManager->PlayRecordingSelect(selectedID)->SetSelected(false);
	pManager->PlayRecordingSelect(selectedID)->SetDelete(true);
	pManager->ProcessDeletedFigures();
}
void DeleteAction::RedoAction()
{
	if (Selected_Figure)
	{
		Selected_Figure->setFigureHidden(false);
		Selected_Figure->SetDelete(true);
		pManager->ProcessDeletedFigures();

	}
	
}