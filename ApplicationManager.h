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
#include"PlayMode/PlayBytype.h"
#include "Actions\ExitAction.h"
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
	CFigure* Playlist[MaxFigCount];
	Action* ActionList[MaxFigCount];
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;
	int rectanglecount;
	int squarecount;
	int trianglecount;
	int hexagoncount;
	int circlecount;
	
	//int arrayofcount[5] = {rectanglecount,squarecount,trianglecount,hexagoncount,circlecount};

public:	

	typedef enum
	{
		DRAWN,
		DELETED
	}Required_Task_t;
	ApplicationManager(); 
	~ApplicationManager();
	void playmode();
	int getrectanglecount();
	int getsquarecount();
	int gettrianglecount();
	int getheaxgoncount();
	int getcirclecount();
	void drawinplaymode();
	
	

	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	CFigure* GetSelectedFigure() const;
	void ExecuteUndoAction();
	int figcount();
	string radnomfigure();
	CFigure* GetTheLastDrawnObject(Required_Task_t task);

	void AddAction(Action* pAction);
	void ClearAll();
	void Save_All() const;
	void playmodecounter();
	string* GetGraphFiles(int& lineCount) const;
	//CFigure* Getplaylist();
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
};

#endif