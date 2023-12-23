#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "Actions\Action.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Actions\AddRectAction.h"
#include"Actions\AddSquareAction.h"
#include"Actions\AddTriangleAction.h"
#include "Actions\SelectAction.h"
#include"Actions\AddHexagonAction.h"
#include"Actions\AddCircleAction.h"
#include "Actions\ClearAllAction.h"
#include "Actions\DeleteAction.h"
#include "Actions\MoveAction.h"
#include "Actions\SwitchAction.h"
#include "Actions\SaveGraphAction.h"
#include "Actions\LoadGraphAction.h"
#include"PlayMode\PlayBytype.h"
#include"PlayMode/PlayBycolor.h"
#include"PlayMode/PlayByboth.h"
#include "Actions\ExitAction.h"
#include "Actions\FillColorAction.h"
#include "Actions\DrawColorAction.h"
#include "UndoActionClass.h"
#include "RedoActionClass.h"
#include "StartRecording.h"
#include "StopRecording.h"
#include "PlayRecording.h"
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
	//int playCount;
	int deletedFigCount;
	int Action_Count_For_Recording;
	int Action_Count;
	int Redo_Action_Count;
	int Fig_Redo_Count;
	int SelectedFigNum;
	int PlayRecordingFigCount;
	int RectCount;
	int SquareCount;
	int TriangleCount;
	int HexagonCount;
	int CircleCount;
	bool ZeroID;

	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* FigListForRedoAction[MaxFigCount];
	CFigure* DeletedFigList[20];
	CFigure* PlayRecordingFigList[20];
	CFigure* SelectedFig; //Pointer to the selected figure
	CFigure* Playlist[MaxFigCount];

	bool PermissionToStartRecord;
	bool StartToRecord;

	Action* ActionListForRecording[20];
	Action* ActionList[5];
	Action* RedoActionList[5];
	Action* DeletedActions[15];
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;
	
public:	

	typedef enum
	{
		DRAWN,
		DELETED
	}Required_Task_t;
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
	CFigure* GetSelectedFigure() const;
	void DeleteFigureComplete();
	int GetSelectedFigureNumber();

	bool CheckZeroID();
	void SetZeroID(bool zeroID);

	void sortFigList();

	void sortDeleteList();

	int GetFigsCount() const;
	int GetColoredFigsCount(string c);
	
	void DrawModeOriginal();

	void PassDeletedFigureToDeleteList(CFigure* pFig);
	void SetPermissionToRecord(bool StartRecordiong);
	bool GetRecordingPermission();
	int GetRecordingsCount();
	bool CheckRecording();
	//void AddAction(Action* pAction);
	Action* GetActionForRecording();
	void AddActionForRecording(Action* pAction);
	//CFigure* ReturnLastFigureOfRedoList();
	void AddFigToRedoFigList(CFigure* pFigure);
	void AddForRedoAction(Action* pAction);
	void AddPlayRecordingFigure(CFigure* pFigure);
	CFigure* PlayRecordingSelect(int id);
	void PlayRecordingComplete();
	Action* HandleAndReturnRedoActions();
	void SetRedoActionToNull(Action *pAction);
	void AddForUndoAction(Action* pAction,bool E_Ok);
	void SetActionToNull(Action* pAction);
	void SetFigureToNull(CFigure* pFigure);
	Action* ReturnLastAction();
	CFigure* ReturnLastFigureOnScreen(Required_Task_t task);
	void ClearAll();
	void HalfClearAll();
	CFigure** GetFiguresToSave(int &count) const;

	
	string* GetGraphFiles(int& lineCount) const;
	//CFigure* Getplaylist();
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
	void UpdatePlayRecordingInterface() const;
};

#endif