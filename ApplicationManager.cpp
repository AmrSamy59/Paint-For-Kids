#include "ApplicationManager.h"
#include <iostream>
using namespace std;

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	UI.graphsDir = "GraphsData";
	UI.graphsFile = "graphs.txt";

	fs::create_directory(UI.graphsDir); // Create Graphs Directory if not exists

	pOut = new Output;
	pIn = pOut->CreateInput();
	
	PermissionToStartRecord = true;
	StartToRecord = false;

	FigCount = 0;
	//playCount = 0;
	Action_Count = 0;
	Redo_Action_Count = 0;
	Fig_Redo_Count = 0;
	Action_Count_For_Recording = 0;

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
	{
		FigList[i] = NULL;
		ActionList[i] = NULL;
		RedoActionList[i] = NULL;
		FigListForRedoAction[i] = NULL;
		ActionListForRecording[i] = NULL;
		Playlist[i] = NULL;
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
		case DRAW_UNDO:
			pAct = new UndoActionClass(this);
			break;
		case DRAW_REDO:
			pAct = new RedoActionClass(this);
			break;
		case DRAW_CLEARALL:
			pAct = new AddClearAllAction(this); // Delete all Figures
			break;
		case DRAW_FILL_COLOR:
			pAct = new FillColorAction(this);
			break;
		case DRAW_OUTLINE_COLOR:
			pAct = new DrawColorAction(this);
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
		case DRAW_RECORDING:
			pAct = new StartRecording(this);
			break;
		case DRAW_PLAYRECORDING:
			pAct = new PlayRecording(this);
			break;
		case DRAW_PAUSERECORING:
			pAct = new StopRecording(this);
			break;
		case DRAW_MOVE:
			pAct = new Move(this);
			break;
		case TO_PLAY:
			pAct = new Switch(this);
			break;
		case DRAW_ITM_DRAWMODE:
			pAct = new Switch(this);   
			break;
		case DRAW_ITM_BYTYPE:
			pAct = new PlayByType(this);
			break;
		case DRAW_ITM_BYCOLOR:
				pAct = new PlayBycolor(this);
			break;
		case DRAW_ITM_BYBOTH:
			pAct = new PlayByboth(this);
			break;
		case EXIT:
			///create ExitAction here
			pAct = new Exit(this);
			break;
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	//Execute the created action with recording
	if(pAct != NULL)
	{
		pAct->Execute();		//Execute
		if (dynamic_cast<AddRectAction*>(pAct) || dynamic_cast<AddSquareAction*>(pAct)
			|| dynamic_cast<AddHexagonAction*>(pAct) || dynamic_cast<AddCircleAction*>(pAct)
			|| dynamic_cast<AddTriangleAction*>(pAct) || dynamic_cast<Move*>(pAct)
			|| dynamic_cast<DrawColorAction*>(pAct) || dynamic_cast<FillColorAction*>(pAct))
		{
			AddForUndoAction(pAct, true);
			if (StartToRecord)
			{
				AddActionForRecording(pAct);
				cout << "Action is added to record with recording count " << Action_Count_For_Recording << endl;
			}
		}
		else if (StartToRecord && (dynamic_cast<Select*>(pAct) || dynamic_cast<AddClearAllAction*>(pAct)))
			AddActionForRecording(pAct);
		PermissionToStartRecord = (dynamic_cast<AddClearAllAction*>(pAct)) ? true : false;
		if (dynamic_cast<Exit*>(pAct))
			delete pAct;
	}
}
Action* ApplicationManager::GetActionForRecording()
{
	static unsigned short i = 0;
	if (ActionListForRecording[i] && i < 20)
		return ActionListForRecording[i++];
	else
	{
		i = 0;
		Action_Count_For_Recording = 0;
		pOut->PrintMessage("Nothing to be recorded");
		return NULL;
	}
}
void ApplicationManager::SetPermissionToRecord(bool StartRecordiong)
{
	StartToRecord = StartRecordiong;
	if(StartToRecord)
		for (unsigned short i = 0;i < 20;i++)
			ActionListForRecording[i] = NULL;
}
bool ApplicationManager::GetRecordingPermission()
{
	return PermissionToStartRecord;
}
bool ApplicationManager::CheckRecording()
{
	return StartToRecord;
}
void ApplicationManager::AddActionForRecording(Action* pAction)
{
	if (Action_Count_For_Recording < 20)
		ActionListForRecording[Action_Count_For_Recording++] = pAction;
	else
	{
		pOut->PrintMessage("Recording is over");
		SetPermissionToRecord(false);
	}
}
CFigure* ApplicationManager::ReturnLastFigureOfRedoList()
{
	static unsigned short k;
	static unsigned short PrevPassedFigCount = 0;
	if (PrevPassedFigCount != Fig_Redo_Count)
	{
		PrevPassedFigCount = Fig_Redo_Count;
		k = 1;
	}
	cout << "fig redo count = " << Fig_Redo_Count << endl;
	cout << "prev passed fig in redo var = " << PrevPassedFigCount << "  " << "k = " << k << endl;
	while (1)
	{
		if (FigListForRedoAction[Fig_Redo_Count - k])
			return FigListForRedoAction[Fig_Redo_Count - k++];
		else
			k++;
	}
}
CFigure* ApplicationManager::ReturnLastFigureOnScreen(Required_Task_t task)
{
	static unsigned short k;
	static unsigned short PrevPassedFigCount = 0;
	if (PrevPassedFigCount != FigCount)
	{
		PrevPassedFigCount = FigCount;
		k = 1;
	}
	if (task == DRAWN)
	{
		while (1)
		{
			if (FigList[FigCount - k])
			{
				if (FigList[FigCount - k]->GetFigureAbilityToBeDrawn())
					return FigList[FigCount - k++];
			}
			else
				k++;
		}
	}
	if (task == DELETED)
	{
		while (1)
		{
			if (FigList[FigCount - k])
			{
				if (FigList[FigCount - k]->GetFigureAbilityToBeDrawn() == false)
					return FigList[FigCount - k++];
			}
			else
				k++;
		}
	}
}
Action* ApplicationManager::ReturnLastAction()
{
	static unsigned short count;
	static unsigned short PrevPassedActionCount = 0;
	bool flag = true;
	if (PrevPassedActionCount != Action_Count)
	{
		PrevPassedActionCount = Action_Count;
		count = 1;
	}
	for (unsigned short i = 0;i < 200;i++)
	{
		flag &= (ActionList[i] == NULL) ? true : false;
	}
	cout << flag << endl;
	while (1)
	{
		if (flag)
		{
			pOut->PrintMessage("No more actions to be undoed");
			ActionType ActType = GetUserAction();
			ExecuteAction(ActType);
			return NULL;
		}
		else if (ActionList[Action_Count - count])
			return ActionList[Action_Count - count++];
		else
			count++;
	}
}
void ApplicationManager::AddFigToRedoFigList(CFigure* pFigure)
{
	if (Fig_Redo_Count < 200)
		FigListForRedoAction[Fig_Redo_Count++] = pFigure;
	cout << "added fig in redo fig list" << FigListForRedoAction[Fig_Redo_Count - 1] << endl;
}
void ApplicationManager::AddForRedoAction(Action* pAction)
{
	if (Redo_Action_Count < 200)
		RedoActionList[Redo_Action_Count++] = pAction;
	cout << "Added Action to redo list : " << RedoActionList[Redo_Action_Count - 1] << endl;
}

void ApplicationManager::AddPlayRecordingFigure(CFigure* pFigure)
{
	if (PlayRecordingFigCount < 20)
	{
		PlayRecordingFigList[PlayRecordingFigCount++] = pFigure;
	}
}

void ApplicationManager::AddForUndoAction(Action* pAction, bool E_Ok)
{
	if (Action_Count < MaxFigCount)
		ActionList[Action_Count++] = pAction;
	//Setting Redo List To NULL
	if (E_Ok)
	{
		for (unsigned int i = 0;i < 200;i++)
		{
			RedoActionList[i] = NULL;
		}
		Redo_Action_Count = 0;
	}
}
Action* ApplicationManager::HandleAndReturnRedoActions()
{
	static unsigned short j;
	static unsigned short PrevPassedRedoActionCount = 0;
	bool flag = true;
	if (PrevPassedRedoActionCount != Redo_Action_Count && flag)
	{
		PrevPassedRedoActionCount = Redo_Action_Count;
		j = 1;
	}
	for (unsigned short i = 0;i < 200;i++)
	{
		flag &= (RedoActionList[i] == NULL) ? true : false;
	}
	cout << "Redo Flag:" << flag << endl;
	cout << "Redo Action Count:" << Redo_Action_Count << endl;
	cout << "j:" << j << endl;
	while(1)
	{
		if (flag)
		{
			pOut->PrintMessage("No more actions to be redoed");
			ActionType ActType = GetUserAction();
			ExecuteAction(ActType);
			return NULL;
		}
		else if (RedoActionList[Redo_Action_Count - j])
			return RedoActionList[Redo_Action_Count - j++];
		else
			j++;
	}
}
void ApplicationManager::SetRedoActionToNull(Action* pAction)
{
	for (unsigned short i = 0;i < Redo_Action_Count;i++)
	{
		if (RedoActionList[i] == pAction)
		{
			RedoActionList[i] = NULL;
			break;
		}
	}
}
void ApplicationManager::SetActionToNull(Action* pAction)
{
	for(unsigned short i = 0;i < Action_Count;i++)
	{
		if (ActionList[i] == pAction)
		{
			ActionList[i] = NULL;
			break;
		}
	}
}
void ApplicationManager::ClearAll() {
	for (int i = 0; i <MaxFigCount; i++)
	{
		if (FigList[i] != NULL) {
			delete FigList[i];
			FigList[i] = NULL;
		}
		if (ActionList[i] != NULL) {
			delete ActionList[i];
			ActionList[i] = NULL;
		}
	}
	FigCount = 0;
	Action_Count = 0;
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

		Fout << "SETTINGS" << "\t" << pOut->GetColorName(UI.DrawColor) << "\t" << pOut->GetColorName(UI.FillColor) << endl;
		Fout << "FIGCOUNT" << "\t" << FigCount << endl;

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
//Add an Action to the list of Actions
void ApplicationManager::AddAction(Action* pAction)
{
	if (Action_Count < MaxFigCount)
		ActionList[Action_Count++] = pAction;
}
//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;

}
/*void ApplicationManager::AddFigureplay(CFigure* pFig)
{
	if (playCount < MaxFigCount)
		Playlist[playCount++] = pFig;
	cout << 1<<endl;
}*/
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	
	for (int i = FigCount - 1; i >= 0; i--) // Prioritize last added items
	{
		
		if (FigList[i] != NULL && FigList[i]->CheckSelection(x, y))
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
int ApplicationManager::GetSelectedFigureNumber()
{
	int j = 0;
	while (j < FigCount)
	{
		if (FigList[j] != NULL && FigList[j]->IsSelected() == true && FigList[j]->GetFigureAbilityToBeDrawn() == true)
		{
			return j;
		}
		j++;
	}
	return -1;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//
//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut->ClearDrawArea();
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i] != NULL && FigList[i]->GetFigureAbilityToBeDrawn())
			FigList[i]->Draw(pOut);	//Call Draw function (virtual member fn)
	}
		
}
void ApplicationManager::PlayModeClearSelection()
{
	SelectedFigNum = GetSelectedFigureNumber();
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] != NULL)
			FigList[i]->SetSelected(false);
	}
	
}
void ApplicationManager::DrawModeOriginal()
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] != NULL && i == SelectedFigNum)
			FigList[i]->SetSelected(true);
	}
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
void ApplicationManager::Playlistformation() {
	for (int i = 0; i < FigCount; i++) {
		if(FigList[i]->GetFigureAbilityToBeDrawn())
			Playlist[i] = FigList[i];
	}
}
void ApplicationManager::PlayByTypecounter()
{
	RectCount = 0;
	TriangleCount = 0;
	SquareCount = 0;
	HexagonCount = 0;
	CircleCount = 0;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetFigureAbilityToBeDrawn()) {
			if (dynamic_cast<CRectangle*>(Playlist[i]) != NULL)
				RectCount++;
			else if (dynamic_cast<CTriangle*>(Playlist[i]) != NULL)
				TriangleCount++;
			else if (dynamic_cast<CSquare*>(Playlist[i]) != NULL)
				SquareCount++;
			else if (dynamic_cast<CHexagon*>(Playlist[i]) != NULL)
				HexagonCount++;
			else if (dynamic_cast<CCircle*>(Playlist[i]) != NULL)
				CircleCount++;
		}
	}
	
}
void ApplicationManager::PlayModeClear()
{
	for (int i = 0; i < FigCount; i++)
	{
		if (Playlist[i] != NULL)
		{
			Playlist[i] = NULL;
		}
	}
}
CFigure* ApplicationManager::GetRandomfigure()
{
	int randomnumber;
	if (FigCount == 0)
		return nullptr;
	do
	{
	    randomnumber = rand() % FigCount;
	} while (FigList[randomnumber]->CheckDelete());
	return FigList[randomnumber];
}
void ApplicationManager::ResetPlayMode()
{
	this->Playlistformation();

	for (int i = 0; i < FigCount; i++)
	{
		if (Playlist[i]->CheckDelete() == false)
		{
			Playlist[i]->SetFigureAbilityToBeDrawn(true);
			Playlist[i]->SetSelected(false);
		}
	}
		

}
int ApplicationManager::GetFigsCount() const
{
	return FigCount;
}

int ApplicationManager::GetColoredFigsCount(string c)
{
	int count = 0;
	Output* pOut = GetOutput();
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->GetFillColor() && *FigList[i]->GetFillColor() == pOut->GetColorFromName(c))
			count++;
	}
	return count;
}
int ApplicationManager::Playmode_both(string figType, string figColName)
{
	int typeColorCounter = 0;
	//CFigure* randomFig =  this->GetRandomfigure();
	
	
		//cout << pOut->GetColorName(*figCol) << endl;
		color figCol = pOut->GetColorFromName(figColName);
		for (int i = 0; i < FigCount; i++)
		{
	//		cout << "figure " << i + 1 << Playlist[i]->GetType() << pOut->GetColorName(*Playlist[i]->GetFillColor()) << endl;
			if (Playlist[i]->GetType() == figType && *Playlist[i]->GetFillColor() == figCol)
				typeColorCounter++;
		}

	
	return typeColorCounter;

	}
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
	{
		delete FigList[i];
		delete ActionList[i];
		delete RedoActionList[i];
		if(i < 20)
			delete ActionListForRecording[i];
	}
	delete pIn;
	delete pOut;
}
