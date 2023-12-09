#include "ApplicationManager.h"



//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	UI.graphsDir = "GraphsData";
	UI.graphsFile = "graphs.txt";

	fs::create_directory(UI.graphsDir); // Create Graphs Directory if not exists

	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FigCount = 0;
	ActionsCount = 0;
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
	{
		FigList[i] = NULL;
		ActionList[i] = NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;
		case DRAW_SQUARE:
			pAct = new AddSquareAction(this);
			break;
		case DRAW_TRIANGLE:
			pAct = new AddTriangleAction(this);
			break;
		case DRAW_HEXAGON:
			pAct = new AddHexagonAction(this);
			break;
		case DRAW_CIRC :
			pAct = new AddCircleAction(this);
			break;
		case DRAW_DELETE:
			pAct = new AddDeleteAction(this);// Delete Selected Figure
			break;
		case DRAW_CLEARALL:
		//	pAct = new AddClearAllAction(this); // Delete all Figures
			break;

		case DRAW_SAVEGRAPH:
			Save_All();
			break;
		case DRAW_LOADGRAPH:
			pAct = new LoadGraph(this);
			break;
		case DRAW_SELECT:
			pAct = new Select(this);
			break;
		case DRAW_MOVE:
			pAct = new Move(this);
			break;
		case DRAW_UNDO:
			ExecuteUndoAction();
			break;

		case TO_PLAY:
			pAct = new Switch(this);
			break;
		case DRAW_ITM_DRAWMODE:
			pAct = new Switch(this);   
			break;
		
		case EXIT:
			///create ExitAction here
			
			break;
		
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		AddAction(pAct);//You may need to change this line depending to your implementation
	}
}
void ApplicationManager::AddAction(Action *pAction)
{
	if (ActionsCount < MaxActionsCount)
		ActionList[ActionsCount++] = pAction;
}
CFigure* ApplicationManager::GetTheLastDrawnObject() const
{
	static unsigned short i;
	static unsigned short PrevPassedFigCount = 0;
	if (PrevPassedFigCount != FigCount)
	{
		PrevPassedFigCount = FigCount;
		i = 1;
	}
	while (1) {
		if (ActionList[FigCount - i])
		{
			return FigList[FigCount - i++];
		}
		else
			i++;
	}
}
void ApplicationManager::ExecuteUndoAction()
{
	static unsigned short i;
	static unsigned short PrevPassedFigCount = 0;
	if (PrevPassedFigCount != FigCount)
	{
		PrevPassedFigCount = FigCount;
		i = 1;
	}
	while (1)
	{
		if (ActionList[FigCount - i])
		{
			ActionList[FigCount - i]->UndoAction();
			if (dynamic_cast<AddRectAction*>(ActionList[FigCount - i]) != NULL || dynamic_cast<AddSquareAction*>(ActionList[FigCount - i]) != NULL
				|| dynamic_cast<AddHexagonAction*>(ActionList[FigCount - i]) != NULL || dynamic_cast<AddCircleAction*>(ActionList[FigCount - i]) != NULL
				|| dynamic_cast<AddTriangleAction*>(ActionList[FigCount - i]) != NULL)
				FigList[FigCount - i] = NULL;
			ActionList[FigCount - i++] = NULL;
			break;
		}
		else
			i++;
	}
}
void ApplicationManager::Save_All() const
{
	ofstream Fout;
	if (FigCount == 0) {
		pOut->PrintMessage("There are no figures to save.");
		return;
	}
	pOut->PrintMessage("Enter file name, Use your keyboard to type (Press ESC to cancel) .");
	string fname = pIn->GetSrting(pOut);
	if (fname == "") {
		pOut->PrintMessage("Operation cancelled.");
	}
	if (!(fname.length() >= 4 && fname.substr(fname.length() - 4) == ".txt")) {
		fname += ".txt";
	}

	string fpath = UI.graphsDir + "/" + fname;

	Fout.open(fpath);
	if (Fout.is_open()) {
		for (int i = 0; i < FigCount; i++)
			FigList[i]->Save(Fout);
		
		int fcount;
		string* graphFiles = GetGraphFiles(fcount);
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
	}
}

string* ApplicationManager::GetGraphFiles(int& lineCount) const
{
	ifstream gFile;
	gFile.open(UI.graphsFile);

	if (gFile.is_open()) {
		string line;
		int lcount = 0;

		// Read the file line by line
		while (getline(gFile, line)) { // I know it's more practical to use vectors in that case, but since we it wasn't in our course scope sooo..
			lcount++;
		}

		// Reset the file position to the beginning
		gFile.clear();
		gFile.seekg(0, ios::beg);

		// Allocate memory for the array
		string* lines = new string[lcount];

		// Read the file line by line
		int lid = 0;
		for (int i = 0; i < lcount; ++i) {
			getline(gFile, line);
			if (fs::exists(UI.graphsDir + "/" + line)) // Only get real graph files
				lines[lid++] = line;
		}

		lineCount = lid;

		// Close the file when done
		gFile.close();

		return lines;
	}
	else {
		return {};
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	
	for (int i = FigCount - 1; i >= 0; i--) // Prioritize last added items
	{
		if (FigList[i] != NULL)
		{
			if (FigList[i]->CheckSelection(x, y))
			{
				int j = 0;
				while (j < FigCount)
				{
					if (FigList[j] != NULL)
						FigList[j]->SetSelected(false);
					j++;
				}
				return FigList[i];
			}
		}
	}

	for (int j = 0; j < FigCount; j++)
	{
		if (FigList[j] != NULL)
			FigList[j]->SetSelected(false);
	}

	return NULL;
}
CFigure* ApplicationManager::GetSelectedFigure() const
{
	int j = 0;
	while (j < FigCount)
	{
		if (FigList[j] != NULL && FigList[j]->IsSelected() == true && FigList[j]->GetFigureAbilityToBeDrawn() == true)
		{
			return FigList[j];
		}
		j++;
	}
	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
		if(FigList[i] != NULL && FigList[i]->GetFigureAbilityToBeDrawn() == true)
			FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}

////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
		delete ActionList[i];
	}
	delete pIn;
	delete pOut;
}
