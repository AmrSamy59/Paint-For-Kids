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
#include "Actions\LoadGraphAction.h"
#include"PlayMode\PlayBytype.h"
#include"PlayMode/PlayBycolor.h"
#include"PlayMode/PlayByboth.h"
#include "Actions\ExitAction.h"
#include "Actions\FillColorAction.h"
#include "Actions\DrawColorAction.h"
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
	int Action_Count;
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	CFigure* SelectedFig; //Pointer to the selected figure
	int SelectedFigNum;
	CFigure* Playlist[MaxFigCount];
	Action* ActionList[MaxFigCount];
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;
	int RectCount;
	int SquareCount;
	int TriangleCount;
	int HexagonCount;
	int CircleCount;
	
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
	void PlayModeClearSelection();
	void Playlistformation();
	void ResetPlayMode();
	CFigure* GetRandomfigure();
	void PlayByTypecounter();
	void PlayModeClear();
	int Playmode_both(string figType, string figColName);
	/////////////////////// PLAY MODE FUNCTION END ///////////////////////////////////////////
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	CFigure* GetSelectedFigure() const;
	int GetSelectedFigureNumber();
	void ExecuteUndoAction();

	int GetFigsCount() const;
	int GetColoredFigsCount(string c);
	
	void DrawModeOriginal();
	CFigure* GetTheLastDrawnObject(Required_Task_t task);

	void AddAction(Action* pAction);
	void ClearAll();
	void Save_All() const;
	
	string* GetGraphFiles(int& lineCount) const;
	//CFigure* Getplaylist();
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
};

#endif