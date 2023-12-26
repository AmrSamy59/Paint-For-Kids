#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "Actions\Action.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddSquareAction.h"
#include "Actions\AddTriangleAction.h"
#include "Actions\SelectAction.h"
#include "Actions\AddHexagonAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\ClearAllAction.h"
#include "Actions\DeleteAction.h"
#include "Actions\MoveAction.h"
#include "Actions\SwitchToDrawModeAction.h"
#include "Actions/SwitchToPlayModeAction.h"
#include "Actions\SaveGraphAction.h"
#include "Actions\LoadGraphAction.h"
#include "PlayMode\PlayBytype.h"
#include "PlayMode/PlayBycolor.h"
#include "PlayMode/PlayByboth.h"
#include "Actions\ExitAction.h"
#include "Actions\FillColorAction.h"
#include "Actions\DrawColorAction.h"
#include "Actions/UndoActionClass.h"
#include "Actions/RedoActionClass.h"
#include "Actions/StartRecording.h"
#include "Actions/StopRecording.h"
#include "Actions/PlayRecording.h"
#include "Actions/ToggleSoundAction.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem; // in < C++14, #include <expermintal/filesystem>
								// namespace fs = std::expermintal::filesystem;
								// Note that <expermintal/filesystem> was deperecated, Make sure to handle it by using a flag or something if neccessary.

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	int deletedFigCount;
	int Action_Count_For_Recording;
	int Fig_Redo_Count;
	int SelectedFigNum;
	int PlayRecordingFigCount;
	int RectCount;
	int SquareCount;
	int TriangleCount;
	int HexagonCount;
	int CircleCount;

	unsigned short Deleted_Action_Count; //Deleted Action Counter
	short HandleCounter; //Counter To Handle relation between Undo&Redo and Recording

	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* FigListForRedoAction[MaxFigCount];
	CFigure* DeletedFigList[20];
	CFigure* PlayRecordingFigList[20];
	CFigure* CopyFigList[20];
	CFigure* SelectedFig; //Pointer to the selected figure
	CFigure* Playlist[MaxFigCount];

	bool PermissionToStartRecord;
	bool StartToRecord;

	Action* ActionListForRecording[20]; //List for Recording Actions
	Action* ActionList[5]; //List for Undo Actions
	Action* RedoActionList[5]; //List for Redo Actions
	Action* RedoRecordedActionList[5]; 
	Action* DeletedActions[10]; //List for Deleted Actions
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;
	
public:	
	ApplicationManager(); 
	~ApplicationManager();
	/// 
	/// PLAY MODE FUNCTIONS////////////////////////////////////////////////////////////////////////
	//void AddFigureplay(CFigure* pFig);
	void PlayModeClearSelection();
	void Playlistformation();
	void ResetPlayMode();
	CFigure* GetRandomfigure();
	void PlayModeClear();
	int GetSpecificTypeCount(string figType, string figColName);
	/////////////////////// PLAY MODE FUNCTION END ///////////////////////////////////////////
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	CFigure* UnselectAll();
	CFigure* GetSelectedFigure() const;
	void ProcessDeletedFigures();
	void RedoProcessDeletedFigures(CFigure* figure);
	void RedoProcessRecordedDeletedFigures(CFigure* figure);
	int GetSelectedFigureNumber();

	void sortFigList();

	void sortDeleteList();

	void sortPlayRecordingFigList();

	int GetFigsCount() const;
	int GetColoredFigsCount(string c);
	
	void DrawModeOriginal();

	/******************************Undo And Redo Functions*********************************/
	void AddForRedoAction(Action* pAction); //Add redo action to redo List
	Action* ReturnLastAction(); //returning last undo action if available
	Action* HandleAndReturnRedoActions(); //returning last redo action if available
	void SetRedoActionToNull(Action *pAction); //setting redo action to null in redo list
	void AddForUndoAction(Action* pAction,bool E_Ok); //Add undo action to undo List
	void SetActionToNull(Action* pAction); //setting undo Action To Null
	////////////////////////////////////////////////////////////////////////////////////
	
	/******************************Starting To Record Functions*******************************/
	void SetPermissionToRecord(bool StartRecordiong); //Able and Disable recording
	bool GetRecordingPermission(); //getting recording permission to start
	void AddActionForRecording(Action* pAction); //Add recording action to recording list
	///////////////////////////////////////////////////////////////////////////////////////////

//	void PassDeletedFigureToDeleteList(CFigure* pFig);
	int GetRecordingsCount();
	bool CheckRecording();
	Action* GetActionForRecording();
	
	Action* PlayRecordingUndo(int actID, int c);
	void AddPlayRecordingFigure(CFigure* pFigure);
	CFigure* PlayRecordingSelect(int id);
	void PlayRecordingComplete();
	void SetFigureToNull(CFigure* pFigure); // setting figure to null
	void ClearAll();
	void PlayRecordingClearAll();
	int GetFigsCountToSave() const;

	
	void SaveAll(string fname) const;

	string* GetGraphFiles(int& lineCount) const;
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
	void UpdatePlayRecordingInterface() const;
	void ExitProgram();
};

#endif