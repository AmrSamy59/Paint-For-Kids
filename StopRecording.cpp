#include "StopRecording.h"

StopRecording::StopRecording(ApplicationManager* pApp):Action(pApp)
{
}

void StopRecording::UndoAction()
{
}

void StopRecording::RedoAction()
{
}

void StopRecording::ReadActionParameters()
{
}

void StopRecording::Execute()
{
	Output* pOut = pManager->GetOutput();
	pManager->SetPermissionToRecord(false);
	pOut->PrintMessage("Recording has been stopped");
}
