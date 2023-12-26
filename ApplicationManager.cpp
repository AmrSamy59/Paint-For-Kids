#include "ApplicationManager.h"
#include <iostream>
using namespace std;

//Constructor
//Test3
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
	deletedFigCount = 0;
	Fig_Redo_Count = 0;
	PlayRecordingFigCount = 0;
	Action_Count_For_Recording = 0;

	Deleted_Action_Count = 0;
	HandleCounter = 0;

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
	{
		FigList[i] = NULL;
		FigListForRedoAction[i] = NULL;
		Playlist[i] = NULL;
	}
	for (int i = 0; i < 20; i++)
	{
		ActionListForRecording[i] = NULL;
		PlayRecordingFigList[i] = NULL;
		DeletedFigList[i] = NULL;
		CopyFigList[i] = NULL;
	}
	for (int i = 0; i < 5; i++)
	{
		ActionList[i] = NULL;
		RedoActionList[i] = NULL;
	}
	for (int i = 0; i < 10; i++)
	{
		DeletedActions[i] = NULL;
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
	bool isPlayMode = false;
	bool canBeUndone = false;
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			canBeUndone = true;
			pAct = new AddRectAction(this);
			break;
		case DRAW_SQUARE:
			canBeUndone = true;
			pAct = new AddSquareAction(this);
			break;
		case DRAW_TRIANGLE:
			canBeUndone = true;
			pAct = new AddTriangleAction(this);
			break;
		case DRAW_HEXAGON:
			canBeUndone = true;
			pAct = new AddHexagonAction(this);
			break;
		case DRAW_CIRC :
			canBeUndone = true;
			pAct = new AddCircleAction(this);
			break;
		case DRAW_DELETE:
			canBeUndone = true;
			pAct = new DeleteAction(this);// Delete Selected Figure
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
		case DRAW_CHNG_FILL_COLOR:
			canBeUndone = true;
			pAct = new FillColorAction(this);
			break;
		case DRAW_CHNG_OUTLINE_COLOR:
			canBeUndone = true;
			pAct = new DrawColorAction(this);
			break;
		case DRAW_SAVEGRAPH:
			pAct = new SaveGraph(this);
			break;
		case DRAW_LOADGRAPH:
			pAct = new LoadGraph(this);
			break;
		case DRAW_SELECT:
			pAct = new Select(this,true);
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
			canBeUndone = true;
			pAct = new Move(this);
			break;
		case DRAW_SOUNDTOGGLE:
			pAct = new ToggleSoundAction(this);
			break;
		case TO_PLAY:
			pAct = new SwitchToPlayMode(this);
			break;
		case TO_DRAW:
			pAct = new SwitchToDrawMode(this);   
			break;
		case PLAYMODE_BYTYPE:
			isPlayMode = true;
			pAct = new PlayByType(this);
			break;
		case PLAYMODE_BYCOLOR:
			isPlayMode = true;
			pAct = new PlayBycolor(this);
			break;
		case PLAYMODE_BYBOTH:
			isPlayMode = true;
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
		if (!pAct->IsCanceled()) {
			if (canBeUndone)
			{
				AddForUndoAction(pAct, true);
				if (StartToRecord)
				{
					AddActionForRecording(pAct);
				}
			}
			else if (StartToRecord && (dynamic_cast<Select*>(pAct) || dynamic_cast<AddClearAllAction*>(pAct) 
				|| dynamic_cast<UndoActionClass*>(pAct) || dynamic_cast<RedoActionClass*>(pAct)))
				AddActionForRecording(pAct);
			PermissionToStartRecord = (dynamic_cast<AddClearAllAction*>(pAct) || dynamic_cast<ToggleSoundAction*>(pAct)) ? true : false;
			if(!isPlayMode)
				pAct->PlayActionVoice();
		}
		if (dynamic_cast<Exit*>(pAct))
			delete pAct;
	}
}
Action* ApplicationManager::GetActionForRecording()
{
	static unsigned short i = 0;
	if (ActionListForRecording[i] != NULL && i < 20) {
		return ActionListForRecording[i++];
		if (dynamic_cast<UndoActionClass*>(ActionListForRecording[i]))
		{

		}
	}
	else
	{
		i = 0;
	//	Action_Count_For_Recording = 0;
		return NULL;
	}
}
void ApplicationManager::SetPermissionToRecord(bool StartRecordiong)
{
	StartToRecord = StartRecordiong; //true if recording is on 
	if(StartToRecord)
		for (unsigned short i = 0;i < 20;i++)
			ActionListForRecording[i] = NULL; //resetiing Recording actionss
}
bool ApplicationManager::GetRecordingPermission()
{
	return PermissionToStartRecord; //getting permission to record
}
int ApplicationManager::GetRecordingsCount()
{
	return Action_Count_For_Recording;
}
bool ApplicationManager::CheckRecording()
{
	return StartToRecord;
}

void ApplicationManager::AddActionForRecording(Action* pAction)
{
	if (Action_Count_For_Recording < 20)
	{
		ActionListForRecording[Action_Count_For_Recording++] = pAction; //Adding action to recording list
	}
	else
	{
		pOut->PrintMessage("Recording is over");
		SetPermissionToRecord(false);
		StartToRecord = false;
		Action_Count_For_Recording = 0;
	}
}
Action* ApplicationManager::ReturnLastAction()
{
	bool flag = true;
	for (unsigned short i = 0;i < 5;i++)
	{
		flag &= (ActionList[i] == NULL) ? true : false; //flag = true if no more actions to be undoed
	}
	if (flag)
	{
		pOut->PrintMessage("No more actions to be undoed");
		ActionType ActType = GetUserAction();
		ExecuteAction(ActType);
		return NULL;
	}
	else
	{
		short i = 4;
		while (i >= 0)
		{
			if (ActionList[i])
			{				
				return ActionList[i]; //Returning Last Undo Action if available
			}
			i--;
		}
	}
}

void ApplicationManager::AddForRedoAction(Action* pAction)
{
	for (unsigned short i = 0;i < 4;i++)
	{
		RedoActionList[i] = RedoActionList[i + 1]; //Adding Action to Redo List
	}
	RedoActionList[4] = pAction;
}

Action* ApplicationManager::PlayRecordingUndo(int actID, int c)
{
	if (actID > 1)
	{
		return ActionListForRecording[actID - c];
	}
}
void ApplicationManager::AddPlayRecordingFigure(CFigure* pFigure)
{
	if (PlayRecordingFigCount < 20)
	{
		PlayRecordingFigList[PlayRecordingFigCount++] = pFigure;
	}
}

CFigure* ApplicationManager::PlayRecordingSelect(int id)
{
	int i = 0;
	while(i < PlayRecordingFigCount)
	{
		if (PlayRecordingFigList[i] != NULL)
		{
			cout << PlayRecordingFigList[i]->GetID();
			if (PlayRecordingFigList[i]->IsSelected() && PlayRecordingFigList[i]->GetID() != id)
				PlayRecordingFigList[i]->SetSelected(false);
		}
		if (PlayRecordingFigList[i]->GetID() == id)
		{
			return PlayRecordingFigList[i];
		}
		i++;
	}
	return nullptr;
}

void ApplicationManager::PlayRecordingComplete()
{
	for (int i = 0; i < 20; i++)
	{
		if (CopyFigList[i] != NULL) {
			FigList[i] = CopyFigList[i];
			CopyFigList[i] = NULL;
		}

		if (PlayRecordingFigList[i] != NULL)
		{
			delete PlayRecordingFigList[i];
			PlayRecordingFigList[i] = NULL;
		}
	}
}

void ApplicationManager::SetFigureToNull(CFigure* pFigure)
{
	for (unsigned short i = 0;i < 200;i++)
	{
		if (FigList[i] == pFigure)
		{
			FigList[i] = NULL;
			break;
		}
	}
}
void ApplicationManager::AddForUndoAction(Action* pAction, bool E_Ok)
{
	Action* PtrToOutcastDeletedAction;
	PtrToOutcastDeletedAction = ActionList[0];
	for (unsigned short i = 0;i < 4;i++)
	{
		ActionList[i] = ActionList[i + 1]; //Shofting Array one index left
	}
	ActionList[4] = pAction; //Adding Action to Undo list
	/**************************Handling Deleted Actions between recoeding and Undo&Redo***********************************/
	if (StartToRecord)
	{
		if (HandleCounter++ == 5)
		{
			HandleCounter = 5;
		}
	}
	if (HandleCounter > 0)
	{
		if (PtrToOutcastDeletedAction && dynamic_cast<DeleteAction*>(PtrToOutcastDeletedAction))
		{
			DeletedActions[Deleted_Action_Count++] = PtrToOutcastDeletedAction;
			HandleCounter--;
		}
	}
	else if (HandleCounter == 0 && !StartToRecord)
	{
		if (PtrToOutcastDeletedAction && dynamic_cast<DeleteAction*>(PtrToOutcastDeletedAction))
		{
			delete PtrToOutcastDeletedAction;
			PtrToOutcastDeletedAction = NULL;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////
	if (E_Ok)
	{
		for (unsigned int i = 0;i < 5;i++)
		{
			RedoActionList[i] = NULL;
		}
	}
}
Action* ApplicationManager::HandleAndReturnRedoActions()
{
	bool flag = true;
	for (unsigned short i = 0;i < 5;i++)
	{
		flag &= (RedoActionList[i] == NULL) ? true : false; //flag = true if no more actions to be redoed
	}
	if (flag)
	{
		pOut->PrintMessage("No more actions to be redoed");
		ActionType ActType = GetUserAction();
		ExecuteAction(ActType);
		return NULL;
	}
	else
	{
		unsigned short i = 4;
		while (i >= 0)
		{
			if (RedoActionList[i])
			{			
				return RedoActionList[i]; //returning last redo action if available
			}
			i--;
		}
	}
}
void ApplicationManager::SetRedoActionToNull(Action* pAction)
{
	for (unsigned short i = 0;i < 5;i++)
	{
		if (RedoActionList[i] == pAction)
		{
			RedoActionList[i] = NULL; //setting redo action to NUll
			break;
		}
	}
}
void ApplicationManager::SetActionToNull(Action* pAction)
{
	for(unsigned short i = 0;i < 5;i++)
	{
		if (ActionList[i] == pAction)
		{
			ActionList[i] = NULL; //Setting Undo action to null
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
		if (i < 5)
		{
			if (ActionList[i] != NULL) {
				//delete ActionList[i];
				ActionList[i] = NULL;
			}
			if (RedoActionList[i] != NULL) {
				//delete RedoActionList[i];
				RedoActionList[i] = NULL;
			} 
		}
		if (i < 20)
		{
			/*if (DeletedFigList[i] != NULL)
			{
				delete DeletedFigList[i];
				DeletedFigList[i] = NULL;
			}*/
			if (ActionListForRecording[i] != NULL) {
				delete ActionListForRecording[i];
				ActionListForRecording[i] = NULL;
			}
			if (PlayRecordingFigList[i] != NULL) {
				delete PlayRecordingFigList[i];
				PlayRecordingFigList[i] = NULL;
			}
		}
		if (i < 10)
		{
			if (DeletedActions[i] != NULL)
			{
				delete DeletedActions[i];
				DeletedActions[i] = NULL;
			}
		}
	}
	SetPermissionToRecord(false);
	StartToRecord = false;
	FigCount = 0;
	PlayRecordingFigCount = 0;
	Action_Count_For_Recording = 0;
	Deleted_Action_Count = 0;
	HandleCounter = 0;
}

void ApplicationManager::PlayRecordingClearAll()
{
	for (int i = 0; i < 20; i++)
	{
		if (FigList[i] != NULL) {
			CopyFigList[i] = FigList[i];
			FigList[i] = NULL;
		}
	}
/*	FigCount = 0;
	while (CRectangle::GetCount() > 0)
	{
		CRectangle::DecreaseCount();
	}
	while (CCircle::GetCount() > 0)
	{
		CCircle::DecreaseCount();

	}
	while (CHexagon::GetCount() > 0)
	{
		CHexagon::DecreaseCount();
	}
	while (CSquare::GetCount() > 0)
	{
		CSquare::DecreaseCount();
	}
	while (CTriangle::GetCount() > 0)
	{
		CTriangle::DecreaseCount();
	}*/
	CFigure::ResetIDs(); // Reset IDs to 0 
}

int ApplicationManager::GetFigsCountToSave() const
{
	int count = 0;
	for (int i = 0; i < FigCount; i++)
	{
		if(FigList[i] && FigList[i]->isFigureShown() && !FigList[i]->isDeleted())
		{
			count++;
		}
	}
	return count;
}

void ApplicationManager::SaveAll(string fname) const {
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
			if (FigList[i] && FigList[i]->isFigureShown() && !FigList[i]->isDeleted())
				FigList[i]->Save(Fout);
		}


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
		
		if (FigList[i] != NULL && FigList[i]->CheckSelection(x, y))
		{
			return FigList[i];
		}
	}

	return NULL;
}
CFigure* ApplicationManager::UnselectAll() {
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] != NULL)
		{
			FigList[i]->SetSelected(false);
		}
	}
	return NULL;

}
CFigure* ApplicationManager::GetSelectedFigure() const
{
	int j = 0;
	while (j < FigCount)
	{
		if (FigList[j] != NULL && FigList[j]->IsSelected() == true && FigList[j]->isFigureShown() == true)
		{
			return FigList[j];
		}
		j++;
	}
	return NULL;
}
void ApplicationManager::ProcessDeletedFigures()
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] != NULL) {
			if (FigList[i]->isDeleted())
			{
				if (dynamic_cast<CRectangle*>(FigList[i]))
				{
					CRectangle::DecreaseCount();
				}
				else if (dynamic_cast<CSquare*>(FigList[i]))
				{
					CSquare::DecreaseCount();
				}
				else if (dynamic_cast<CTriangle*>(FigList[i]))
				{
					CTriangle::DecreaseCount();
				}
				else if (dynamic_cast<CCircle*>(FigList[i]))
				{
					CCircle::DecreaseCount();
				}
				else if (dynamic_cast<CHexagon*>(FigList[i]))
				{
					CHexagon::DecreaseCount();
				}
				DeletedFigList[deletedFigCount++] = FigList[i];
				FigList[i] = NULL;
				sortFigList();
				FigCount--;
			}
		}
	}

	for (int i = 0; i < PlayRecordingFigCount; i++)
	{
		if (PlayRecordingFigList[i] != NULL) {
			if (PlayRecordingFigList[i]->isDeleted())
			{
				if (dynamic_cast<CRectangle*>(PlayRecordingFigList[i]))
				{
					CRectangle::DecreaseCount();
				}
				else if (dynamic_cast<CSquare*>(PlayRecordingFigList[i]))
				{
					CSquare::DecreaseCount();
				}
				else if (dynamic_cast<CTriangle*>(PlayRecordingFigList[i]))
				{
					CTriangle::DecreaseCount();
				}
				else if (dynamic_cast<CCircle*>(PlayRecordingFigList[i]))
				{
					CCircle::DecreaseCount();
				}
				else if (dynamic_cast<CHexagon*>(PlayRecordingFigList[i]))
				{
					CHexagon::DecreaseCount();
				}
				DeletedFigList[deletedFigCount++] = PlayRecordingFigList[i];
				PlayRecordingFigList[i] = NULL;
				sortPlayRecordingFigList();
				PlayRecordingFigCount--;
			}
		}
	}

	for (int i = 0; i < deletedFigCount; i++)
	{

		if (DeletedFigList[i] != NULL)
		{
			DeletedFigList[i]->SetDeletedID(DeletedFigList[i]->GetDeletedID() + 1);
			if (DeletedFigList[i]->GetDeletedID() > 20)
			{
				delete DeletedFigList[i];
			}
		}
		
	}
}

void ApplicationManager::RedoProcessDeletedFigures(CFigure* figure)
{
	for (int i = 0; i < deletedFigCount; i++)
	{
		if (DeletedFigList[i] == figure)
		{
			DeletedFigList[i]->SetDeletedID(DeletedFigList[i]->GetDeletedID() - 1);
			if (dynamic_cast<CRectangle*>(DeletedFigList[i]))
			{
				CRectangle::IncreaseCount();
			}
			else if (dynamic_cast<CSquare*>(DeletedFigList[i]))
			{
				CSquare::IncreaseCount();
			}
			else if (dynamic_cast<CTriangle*>(DeletedFigList[i]))
			{
				CTriangle::IncreaseCount();
			}
			else if (dynamic_cast<CCircle*>(DeletedFigList[i]))
			{
				CCircle::IncreaseCount();
			}
			else if (dynamic_cast<CHexagon*>(DeletedFigList[i]))
			{
				CHexagon::IncreaseCount();
			}
			deletedFigCount--;
			FigCount++;
			DeletedFigList[i] = NULL;
			sortDeleteList();
		}
		if (DeletedFigList[i] != NULL)
		{
			DeletedFigList[i]->SetDeletedID(DeletedFigList[i]->GetDeletedID() - 1);
		}
	}
}

void ApplicationManager::RedoProcessRecordedDeletedFigures(CFigure* figure)
{
	for (int i = 0; i < deletedFigCount; i++)
	{
		if (DeletedFigList[i] == figure)
		{
			DeletedFigList[i]->SetDeletedID(DeletedFigList[i]->GetDeletedID() - 1);
			if (dynamic_cast<CRectangle*>(DeletedFigList[i]))
			{
				CRectangle::IncreaseCount();
			}
			else if (dynamic_cast<CSquare*>(DeletedFigList[i]))
			{
				CSquare::IncreaseCount();
			}
			else if (dynamic_cast<CTriangle*>(DeletedFigList[i]))
			{
				CTriangle::IncreaseCount();
			}
			else if (dynamic_cast<CCircle*>(DeletedFigList[i]))
			{
				CCircle::IncreaseCount();
			}
			else if (dynamic_cast<CHexagon*>(DeletedFigList[i]))
			{
				CHexagon::IncreaseCount();
			}
			deletedFigCount--;
			PlayRecordingFigCount++;
			DeletedFigList[i] = NULL;
			sortDeleteList();
		}
		if (DeletedFigList[i] != NULL)
		{
			DeletedFigList[i]->SetDeletedID(DeletedFigList[i]->GetDeletedID() - 1);
		}
	}
}


int ApplicationManager::GetSelectedFigureNumber()
{
	int j = 0;
	while (j < FigCount)
	{
		if (FigList[j] != NULL && FigList[j]->IsSelected() == true && FigList[j]->isFigureShown() == true)
		{
			return j;
		}
		j++;
	}
	return -1;
}


void ApplicationManager::sortFigList() {
	for (int i = 0; i < FigCount - 1; ++i) {
		for (int j = 0; j < FigCount - i - 1; ++j) {
			if (!FigList[j] && FigList[j + 1]) {
				// Swap pointers if they need to be reordered
				CFigure* temp = FigList[j];
				FigList[j] = FigList[j + 1];
				FigList[j + 1] = temp;
			}
		}
	}
}
void ApplicationManager::sortDeleteList() {
	for (int i = 0; i < deletedFigCount - 1; ++i) {
		for (int j = 0; j < deletedFigCount - i - 1; ++j) {
			if ((!DeletedFigList[j] || !DeletedFigList[j]->isDeleted()) && DeletedFigList[j + 1]) {
				// Swap pointers if they need to be reordered
				CFigure* temp = DeletedFigList[j];
				DeletedFigList[j] = DeletedFigList[j + 1];
				DeletedFigList[j + 1] = temp;
				deletedFigCount--;
			}
		}
	}
}
void ApplicationManager::sortPlayRecordingFigList()
{
	for (int i = 0; i < PlayRecordingFigCount - 1; ++i) {
		for (int j = 0; j < PlayRecordingFigCount - i - 1; ++j) {
			if (!PlayRecordingFigList[j] && PlayRecordingFigList[j + 1]) {
				// Swap pointers if they need to be reordered
				CFigure* temp = PlayRecordingFigList[j];
				PlayRecordingFigList[j] = PlayRecordingFigList[j + 1];
				PlayRecordingFigList[j + 1] = temp;
			}
		}
	}
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//
//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut->ClearDrawArea();
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i] != NULL)
		  if(FigList[i]->isFigureShown())
			FigList[i]->Draw(pOut);	//Call Draw function (virtual member fn)
	}
}

void ApplicationManager::UpdatePlayRecordingInterface() const {
	pOut->ClearDrawArea();
	for (int i = 0; i < 20; i++) {
		if (PlayRecordingFigList[i] != NULL)
			if(PlayRecordingFigList[i]->isFigureShown())
			PlayRecordingFigList[i]->Draw(pOut);	//Call Draw function (virtual member fn)
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
		if(FigList[i] && FigList[i]->isFigureShown() && !FigList[i]->isDeleted())
			Playlist[i] = FigList[i];
		
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
	
	if (CRectangle::GetCount() == 0 && CSquare::GetCount() == 0 && CCircle::GetCount() == 0 && CTriangle::GetCount() == 0 && CHexagon::GetCount() == 0)
		return nullptr;
	do
	{
	    randomnumber = rand() % FigCount;
	} while (FigList[randomnumber] == NULL);
	return FigList[randomnumber];
}
void ApplicationManager::ResetPlayMode()
{

	for (int i = 0; i < FigCount; i++)
	{
		if (Playlist[i] != NULL)
		{
			Playlist[i]->showFigure(true);
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
			if (FigList[i] && FigList[i]->GetFillColor() == pOut->GetColorFromName(c))
				count++;
	}
	return count;
}

int ApplicationManager::GetSpecificTypeCount(string figType, string figColName)
{
	int typeColorCounter = 0;

		color figCol = pOut->GetColorFromName(figColName);   // get color from name send by class play by both
	/*	 in this for loop i search for figures with same type and color for that I selected by random way in play by both
		 if figure for one itreation equal random figure color and type count increases one and so on 
		*/
		for (int i = 0; i < FigCount; i++)
		{
			if (Playlist[i] != NULL) {
				if (Playlist[i]->GetType() == figType && Playlist[i]->GetFillColor() == figCol)
					typeColorCounter++;
			}
		}

	
	return typeColorCounter;

	}

void ApplicationManager::ExitProgram()
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] != NULL) {
			delete FigList[i];
		}
		if (i < 20) {
			if(ActionListForRecording[i] != NULL)
			  delete ActionListForRecording[i];
		}
	}
	delete pIn;
	delete pOut;
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
