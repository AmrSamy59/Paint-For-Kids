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
		pManager->PlayRecordingClearAll();
		UI.FillColor = UI.DefaultFillColor;
		UI.DrawColor = UI.DefaultDrawColor;
		pOut->CreateDrawToolBar();
		pManager->UpdatePlayRecordingInterface();
		ReadActionParameters();
		int n = 1;
		int c = 0;
		while (PassedRecordingAction) 
		{
			Sleep(1000);
			if (dynamic_cast<UndoActionClass*>(PassedRecordingAction))
			{
				c+=2;
				UndoActionClass* undo = (UndoActionClass*)PassedRecordingAction;
				undo->SetActionID(n);
				undo->SetSelectingNum(c);
			}
			else if(dynamic_cast<RedoActionClass*>(PassedRecordingAction))
			{
				RedoActionClass* redo = (RedoActionClass*)PassedRecordingAction;
				redo->SetActionID(n - 1);
				redo->SetSelectingNum(c);
			}
			else
			{
				c = 0;
			}
			PassedRecordingAction->PlayRecordingFunc();
			pManager->UpdatePlayRecordingInterface();
			ReadActionParameters();
			n++;
		}
		Sleep(1500);
		pManager->PlayRecordingComplete();
	}
	else
	{
		isCanceled = true;
		pOut->PrintMessage("You can't play any recording now!");
	}
}
