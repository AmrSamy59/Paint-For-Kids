#include "ToggleSoundAction.h"

ToggleSoundAction::ToggleSoundAction(ApplicationManager* pApp):Action(pApp)
{

}

void ToggleSoundAction::UndoAction()
{
}

void ToggleSoundAction::RedoAction()
{
}

void ToggleSoundAction::ReadActionParameters()
{
}

void ToggleSoundAction::Execute()
{	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (UI.SoundEnabled)
	{
		UI.SoundEnabled = false;
	}
	else
		UI.SoundEnabled = true;

	pOut->CreateDrawToolBar();
}
