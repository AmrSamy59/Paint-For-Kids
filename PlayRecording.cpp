#include "PlayRecording.h"

PlayRecording::PlayRecording(ApplicationManager* pApp):Action(pApp)
{
	PassedRecordingAction = NULL;
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
	if (canPlay) {
		pManager->ClearAll();
		pManager->UpdateInterface();
		ReadActionParameters();
		UI.FillColor = 0;
		while (PassedRecordingAction) 
		{
			Sleep(1000);
			PassedRecordingAction->PlayRecordingFunc();
			pManager->UpdateInterface();
			ReadActionParameters();
		}
	}
	else
	{
		pOut->PrintMessage("You can't play any recording while recording!");
	}
}
