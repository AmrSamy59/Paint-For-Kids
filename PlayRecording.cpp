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
	pManager->ClearAll();
	pManager->UpdateInterface();
	ReadActionParameters();
	while (PassedRecordingAction)
	{
		Sleep(5000);
		PassedRecordingAction->PlayRecordingFunc();
		ReadActionParameters();
	}
}
