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
	while (1) //Selecting a figure to delete
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
void DeleteAction::setPlayRec(bool rec)
{
	playRec = rec;
}
//Add delete to the ApplicationManager
void DeleteAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->GetFigsCount() == 0) { //Checking if the count of the figures is zero
		pOut->PrintMessage("No figures to delete");
		Selected_Figure = NULL;
		return;
	}
	ReadActionParameters();
	if (Selected_Figure == NULL)
	{
		return;
	}
	selectedID = Selected_Figure->GetID(); //Getting the ID of the deleted ID and assigning it to selectedID
	Selected_Figure->showFigure(false); //Hiding the selected figure
	Selected_Figure->SetSelected(false); //Unselecting the selected figure
	Selected_Figure->SetDelete(true); //Setting the (deleted) variable in the figure to true
	pManager->ProcessDeletedFigures(); //Adding the deleted figure to (DeletedFigList) array

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
		Selected_Figure->showFigure(true); //Showing the deleted figure
		Selected_Figure->SetDelete(false); //Undeleting the deleted figure
		if (!playRec) {
			pManager->AddFigure(Selected_Figure); //Readding the figure to (FigList) array
		}
		if (playRec)
		{
			pManager->AddPlayRecordingFigure(Selected_Figure); //When playing the record, readding the deleted figure to (PlayRecordingFigList) array
		}
		pManager->sortDeleteList(); //Sorting (DeletedFigList) array
		pManager->RedoProcessDeletedFigures(Selected_Figure); //Removing the deleted figure from (DeletedFigList) array
	}
}
void DeleteAction::PlayRecordingFunc()
{
	pManager->PlayRecordingSelect(selectedID)->showFigure(false); //Hiding the selected figure
	pManager->PlayRecordingSelect(selectedID)->SetSelected(false); //Unselecting the selected figure
	pManager->PlayRecordingSelect(selectedID)->SetDelete(true); //Setting the (deleted) variable in the figure to true
	Selected_Figure = pManager->PlayRecordingSelect(selectedID);
	pManager->ProcessDeletedFigures(); //Adding the deleted figure to (DeletedFigList) array
}
void DeleteAction::RedoAction() //Redoing the (Delete action)
{
	if (Selected_Figure)
	{
		Selected_Figure->showFigure(false); 
		Selected_Figure->SetDelete(true);
		pManager->ProcessDeletedFigures();

	}
	
}