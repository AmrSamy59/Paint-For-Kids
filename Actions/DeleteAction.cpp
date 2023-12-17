#include "..\Actions\DeleteAction.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
#include "..\ApplicationManager.h"
#include "..\Actions\SelectAction.h"


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
	Selected_Figure->SetSelected(false);
	Selected_Figure->SetDelete(true);

	if (dynamic_cast<CRectangle*>(Selected_Figure))
	{
		CRectangle::SetCount(CRectangle::GetCount() - 1);
	}
	else if (dynamic_cast<CSquare*>(Selected_Figure))
	{
		CSquare::SetCount(CSquare::GetCount() - 1);
	}
	else if (dynamic_cast<CTriangle*>(Selected_Figure))
	{
		CTriangle::SetCount(CTriangle::GetCount() - 1);
	}
	else if (dynamic_cast<CCircle*>(Selected_Figure))
	{
		CCircle::SetCount(CCircle::GetCount() - 1);
	}
	else if (dynamic_cast<CHexagon*>(Selected_Figure))
	{
		CHexagon::SetCount(CHexagon::GetCount() - 1);
	}

	pOut->PrintMessage("Figure has been deleted succesfully");
}
void AddDeleteAction::UndoAction()
{
	/*Selected_Figure = pManager->GetTheLastDrawnObject(ApplicationManager::DELETED);*/
	cout<<"selected one:" << Selected_Figure << endl;
	if (Selected_Figure)
	{
		Selected_Figure->SetFigureAbilityToBeDrawn(true);
		//Selected_Figure->SetDelete(false);
	}
}
void AddDeleteAction::RedoAction()
{
	Selected_Figure->SetFigureAbilityToBeDrawn(false);
	//Selected_Figure->SetDelete(true);
}