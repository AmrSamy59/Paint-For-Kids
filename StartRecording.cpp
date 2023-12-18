#include "StartRecording.h"

StartRecording::StartRecording(ApplicationManager* pApp):Action(pApp)
{

}

void StartRecording::UndoAction()
{

}

void StartRecording::RedoAction()
{

}

void StartRecording::ReadActionParameters()
{
	PermissionToStartRecord = pManager->GetRecordingPermission();
}

void StartRecording::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (PermissionToStartRecord)
	{
		pOut->PrintMessage("Recording has been started");
		pManager->SetPermissionToRecord(true);
	}
	else
		pOut->PrintMessage("You Cannot Record Now motherf***,focus");
}

