#include "LoadGraphAction.h"


LoadGraph::LoadGraph(ApplicationManager* pApp) : Action(pApp)
{
}

void LoadGraph::ReadActionParameters()
{
	//Create the output window
	Output* pOut = pManager->GetOutput();
	int gCount = 0;
	string* gFiles = pManager->GetGraphFiles(gCount);
	if (gCount == 0) {
		pOut->PrintMessage("There are no saved graphs.");
		return;
	}

	int gRowHeight = 30; // px

	window* lWind = new window(UI.width / 3, gRowHeight*gCount, UI.wx, UI.wy);

	//Change the title
	lWind->ChangeTitle("Paint for Kids - Select Graph To Load");
	
	for (int i = 0; i < gCount; i++) {
		lWind->SetBrush(UI.StatusBarColor);
		lWind->SetPen(UI.StatusBarColor, 1);
		lWind->DrawRectangle(0, gRowHeight*i, UI.width / 3, gRowHeight);

		lWind->SetPen(WHITE, gRowHeight);
		lWind->SetFont(gRowHeight, BOLD, BY_NAME, "Arial"); // Keep that default font
		int tw, th; // Text Width, Height
		lWind->GetStringSize(tw, th, gFiles[i]);
		lWind->DrawString((UI.width / 6) - (tw / 2), (gRowHeight * i) + (gRowHeight / 2) - (th / 2), gFiles[i]); // Center the text
	}
}

void LoadGraph::UndoAction()
{
}



void LoadGraph::Execute()
{
	ReadActionParameters();
}
