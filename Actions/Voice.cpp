#include "Voice.h"

Voice::Voice(ApplicationManager* pApp):Action(pApp)
{

}

void Voice::UndoAction()
{
}

void Voice::RedoAction()
{
}

void Voice::ReadActionParameters()
{
}

void Voice::Execute()
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
