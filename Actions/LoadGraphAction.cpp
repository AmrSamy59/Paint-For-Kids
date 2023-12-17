#include "LoadGraphAction.h"

LoadGraph::LoadGraph(ApplicationManager* pApp) : Action(pApp)
{
}
void LoadGraph::RedoAction()
{
}
void LoadGraph::Load(string fName)
{
	ifstream graphFile(UI.graphsDir + "/" + fName);
	if (graphFile.is_open()) {
		string line;
		pManager->ClearAll();
		int fCount = 0;
		while (getline(graphFile, line)) { // I know it's more practical to use vectors in that case, but since we it wasn't in our course scope sooo..
			string delimiter = "\t";
			string option = line.substr(0, line.find(delimiter));

			string* parmList = GetOptionParameters(line, option, delimiter);
			GfxInfo gfx;

			if (option == "SETTINGS") {
				UI.DrawColor = pManager->GetOutput()->GetColorFromName(parmList[0]);
				UI.FillColor = pManager->GetOutput()->GetColorFromName(parmList[1]);
			}
			if (option == "FIGCOUNT") {
				fCount = stoi(parmList[0]);
			}

			if (option == "TRIANGLE") {
				Point p1, p2, p3;
				p1.x = stoi(parmList[1]);
				p1.y = stoi(parmList[2]);
				p2.x = stoi(parmList[3]);
				p2.y = stoi(parmList[4]);
				p3.x = stoi(parmList[5]);
				p3.y = stoi(parmList[6]);

				
				gfx.DrawClr = pManager->GetOutput()->GetColorFromName(parmList[7]);
				gfx.FillClr = pManager->GetOutput()->GetColorFromName(parmList[8]);
				gfx.isFilled = gfx.FillClr != false;
				CTriangle* Tri = new CTriangle(p1 , p2, p3, gfx);
				pManager->AddFigure(Tri);
			}
			if (option == "HEXAGON") {
				Point c;
				c.x = stoi(parmList[1]);
				c.y = stoi(parmList[2]);
				int L = stoi(parmList[3]);

				gfx.DrawClr = pManager->GetOutput()->GetColorFromName(parmList[4]);
				gfx.FillClr = pManager->GetOutput()->GetColorFromName(parmList[5]);
				gfx.isFilled = gfx.FillClr != false;
				CHexagon* Hex = new CHexagon(c, gfx, L);
				pManager->AddFigure(Hex);
			}
			if (option == "SQUARE") {
				Point c;
				c.x = stoi(parmList[1]);
				c.y = stoi(parmList[2]);
				int L = stoi(parmList[3]);

				gfx.DrawClr = pManager->GetOutput()->GetColorFromName(parmList[4]);
				gfx.FillClr = pManager->GetOutput()->GetColorFromName(parmList[5]);
				gfx.isFilled = gfx.FillClr != false;
				CSquare* Sq = new CSquare(c, gfx, L);
				pManager->AddFigure(Sq);
			}
			if (option == "RECTANGLE") {
				Point p1, p2;
				p1.x = stoi(parmList[1]);
				p1.y = stoi(parmList[2]);
				p2.x = stoi(parmList[3]);
				p2.y = stoi(parmList[4]);


				gfx.DrawClr = pManager->GetOutput()->GetColorFromName(parmList[5]);
				gfx.FillClr = pManager->GetOutput()->GetColorFromName(parmList[6]);
				gfx.isFilled = gfx.FillClr != false;
				CRectangle* Rect = new CRectangle(p1, p2, gfx);
				pManager->AddFigure(Rect);
			}
			if (option == "CIRCLE") {
				Point c;
				c.x = stoi(parmList[1]);
				c.y = stoi(parmList[2]);

				gfx.DrawClr = pManager->GetOutput()->GetColorFromName(parmList[4]);
				gfx.FillClr = pManager->GetOutput()->GetColorFromName(parmList[5]);
				gfx.isFilled = gfx.FillClr != false;
				CCircle* Circ = new CCircle(c, stoi(parmList[3]), gfx);
				pManager->AddFigure(Circ);
			}
		}
		pManager->GetOutput()->PrintMessage("Successfully Loaded graph: " + fName);
		graphFile.close();
		return;
	}
	pManager->GetOutput()->PrintMessage("Failed to load graph: " + fName);
}
string* LoadGraph::GetOptionParameters(string line, string option, string delimiter) {
	int pSize = 0;
	if (option == "SETTINGS")
		pSize = 2;
	if (option == "FIGCOUNT")
		pSize = 1;
	if (option == "TRIANGLE")
		pSize = 9;
	if (option == "HEXAGON")
		pSize = 6;
	if (option == "RECT")
		pSize = 7;
	if (option == "SQUARE")
		pSize = 6;
	if (option == "CIRCLE")
		pSize = 6;

	string* parmList = new string[pSize];

	size_t pos = 0;
	int index = 0;
	while ((pos = line.find(delimiter)) != string::npos) {
		string v = line.substr(0, pos);
		line.erase(0, pos + delimiter.length());
		if (index >= 1) {
			parmList[index - 1] = v;
		}
		index++;
	}
	string last_parm = line; // last parameter
	parmList[pSize - 1] = last_parm;
	return parmList;
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

	window* lWind = new window(UI.width / 3, gRowHeight * (gCount+1) +10, UI.wx, UI.wy);


	//Change the title
	lWind->ChangeTitle("Paint for Kids - Select Graph To Load");
	
	for (int i = 0; i < gCount; i++) {
		string title = gFiles[i].substr(0, gFiles[i].length() - 4);
		lWind->SetBrush(UI.StatusBarColor);
		lWind->SetPen(UI.StatusBarColor, 1);
		lWind->DrawRectangle(0, gRowHeight*i, UI.width / 3, gRowHeight * i+gRowHeight);
		
		lWind->SetBrush(BLACK);
		lWind->SetPen(BLACK, 2);
		lWind->DrawLine(0, gRowHeight * (i+1), UI.width / 3, gRowHeight * (i + 1));
		
		lWind->SetPen(WHITE, gRowHeight/2);
		lWind->SetFont(gRowHeight/2, BOLD, BY_NAME, "Arial"); // Keep that default font
		int tw, th; // Text Width, Height
		lWind->GetStringSize(tw, th, title);
		lWind->DrawString((UI.width / 6) - (tw / 2), (gRowHeight * i) + (gRowHeight / 2) - (th / 2), title); // Center the text
	}
	// close button
	lWind->SetBrush(DARKRED);
	lWind->SetPen(DARKRED, 1);
	lWind->DrawRectangle(0, gRowHeight * (gCount), UI.width / 3, gRowHeight * (gCount + 1));


	lWind->SetPen(WHITE, gRowHeight / 2);
	lWind->SetFont(gRowHeight / 2, BOLD, BY_NAME, "Arial"); // Keep that default font
	int tw, th; // Text Width, Height
	lWind->GetStringSize(tw, th, "Cancel");
	lWind->DrawString((UI.width / 6) - (tw / 2), gRowHeight * (gCount) + (gRowHeight / 2) - (th / 2) - 2, "Cancel"); // Center the text
	//
	int cx, cy;

	lWind->FlushMouseQueue();
	lWind->WaitMouseClick(cx, cy);
	int row_clicked = gCount - ((gCount * gRowHeight) / cy);

	if(row_clicked == gCount)
		return delete lWind;

	Load(gFiles[row_clicked]);
	
	delete lWind;

}

void LoadGraph::UndoAction()
{
}



void LoadGraph::Execute()
{
	ReadActionParameters();
}
