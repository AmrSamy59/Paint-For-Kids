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
void AddDeleteAction::Execute()
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
	Selected_Figure->SetFigureAbilityToBeDrawn(false);
	Selected_Figure->SetSelected(false);
	Selected_Figure->SetDelete(true);
	pManager->DeleteFigureComplete();

	pOut->PrintMessage("Figure has been deleted succesfully");
}
AddDeleteAction::~AddDeleteAction()
{
	delete Selected_Figure;
	Selected_Figure = NULL;
}
void AddDeleteAction::UndoAction()
{
	if (Selected_Figure)
	{
		
		Selected_Figure->SetFigureAbilityToBeDrawn(true);
		Selected_Figure->SetDelete(false);
		pManager->AddFigure(Selected_Figure);
		pManager->sortDeleteList();

		if (dynamic_cast<CRectangle*>(Selected_Figure))
		{
			CRectangle::SetCount(CRectangle::GetCount() + 1);
		}
		else if (dynamic_cast<CSquare*>(Selected_Figure))
		{
			CSquare::SetCount(CSquare::GetCount() + 1);
		}
		else if (dynamic_cast<CTriangle*>(Selected_Figure))
		{
			CTriangle::SetCount(CTriangle::GetCount() + 1);
		}
		else if (dynamic_cast<CCircle*>(Selected_Figure))
		{
			CCircle::SetCount(CCircle::GetCount() + 1);
		}
		else if (dynamic_cast<CHexagon*>(Selected_Figure))
		{
			CHexagon::SetCount(CHexagon::GetCount() + 1);
		}
	}
}
void AddDeleteAction::RedoAction()
{
	if (Selected_Figure)
	{
		Selected_Figure->SetFigureAbilityToBeDrawn(false);
		Selected_Figure->SetDelete(true);
		Selected_Figure = NULL;
		pManager->DeleteFigureComplete();

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
	}
	
}