#include "SaveGraphAction.h"

SaveGraph::SaveGraph(ApplicationManager* pApp) : Action(pApp)
{
	voice = "Sound\\Graph Saved.wav";
}
void SaveGraph::RedoAction()
{
}


void SaveGraph::ReadActionParameters()
{
	FigCount = pManager->GetFigsCountToSave();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (FigCount == 0) {
		pOut->PrintMessage("There are no figures to save.");
		isCanceled = true;
		return;
	}
	pOut->PrintMessage("Enter file name, Use your keyboard to type (Press ESC to cancel) .");
	fname = pIn->GetSrting(pOut);
	if (fname == "") { // Cancel operation
		pOut->PrintMessage("Operation canceled.");
		isCanceled = true;
		return;
	}
}

void SaveGraph::UndoAction()
{
}



void SaveGraph::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (!pManager->CheckRecording())
	{
		ReadActionParameters();
		if (isCanceled) {
			return;
		}
		pManager->SaveAll(fname);
	}
	else
	{
		pOut->PrintMessage("You can't save a graph while recording!");
	}
}
