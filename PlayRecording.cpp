#include "PlayRecording.h"

PlayRecording::PlayRecording(ApplicationManager* pApp):Action(pApp)
{
	PassedRecordingAction = NULL;
	voice = "Sound\\Playing Recording.wav";
}

void PlayRecording::UndoAction()
{
}

void PlayRecording::RedoAction()
{
}

void PlayRecording::ReadActionParameters()
{
	PassedRecordingAction = pManager->GetActionForRecording();
}

void PlayRecording::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->CheckRecording())
	{
		canPlay = false;
	}
	else
		canPlay = true;
	if (canPlay && pManager->GetRecordingsCount() > 0) {
		pManager->HalfClearAll();
		UI.FillColor = UI.DefaultFillColor;
		UI.DrawColor = UI.DefaultDrawColor;
		pOut->CreateDrawToolBar();
		pManager->UpdatePlayRecordingInterface();
		ReadActionParameters();
		while (PassedRecordingAction) 
		{
			Sleep(1000);
			PassedRecordingAction->PlayRecordingFunc();
			pManager->UpdatePlayRecordingInterface();
			ReadActionParameters();
		}
		pManager->PlayRecordingComplete();
	}
	else
	{
		pOut->PrintMessage("You can't play any recording now!");
	}
}
