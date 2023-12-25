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
	FigList = pManager->GetFiguresToSave(FigCount);
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (FigCount == 0) {
		pOut->PrintMessage("There are no figures to save.");
		isCanceled = true;
		return;
	}
	pOut->PrintMessage("Enter file name, Use your keyboard to type (Press ESC to cancel) .");
	fname = pIn->GetSrting(pOut);
	if (fname == "") {
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
		ofstream Fout;

		if (!(fname.length() >= 4 && fname.substr(fname.length() - 4) == ".txt")) {
			fname += ".txt";
		}

		string fpath = UI.graphsDir + "/" + fname;

		Fout.open(fpath);
		if (Fout.is_open()) {

			string drawColor = UI.DrawColor == UI.DefaultDrawColor ? "DEFAULT_DRAW_CLR" : pOut->GetColorName(UI.DrawColor);
			Fout << "SETTINGS" << "\t" << drawColor << "\t" << pOut->GetColorName(UI.FillColor) << endl;
			Fout << "FIGCOUNT" << "\t" << FigCount << endl;

		for (int i = 0; i < FigCount; i++) {
			if (FigList[i] && FigList[i]->isFigureShown())
				FigList[i]->Save(Fout);
		}


			int fcount;
			string* graphFiles = pManager->GetGraphFiles(fcount);
			ofstream gFile;
			gFile.open(UI.graphsFile);
			if (gFile.is_open()) {
				for (int i = 0; i < fcount; i++) {
					gFile << graphFiles[i] << endl;
				}
				gFile << fname << endl;

				delete[] graphFiles;
				gFile.close();
			}

			pOut->PrintMessage("Graph has been saved succesfully to: " + fpath);
			Fout.close();
		}
		else {
			pOut->PrintMessage("Failed to save graph to: " + fpath);
			isCanceled = true;
		}
	}
	else
	{
		pOut->PrintMessage("You can't save a graph while recording!");
	}
}
