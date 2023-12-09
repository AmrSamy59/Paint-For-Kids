#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "Actions/Action.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Actions\AddRectAction.h"
#include"AddSquareAction.h"
#include"AddTriangleAction.h"
#include "SelectAction.h"
#include"AddHexagonAction.h"
#include"AddCircleAction.h"
#include "ClearAllAction.h"
#include "DeleteAction.h"
#include "MoveAction.h"
#include "UndoAction.h"
#include "SwitchAction.h"
#include "LoadGraphAction.h"

#include <fstream>
#include <filesystem>

namespace fs = std::filesystem; // in < C++14, #include <expermintal/filesystem>
								// namespace fs = std::expermintal::filesystem;
								// Note that <expermintal/filesystem> was deperecated, Make sure to handle it by using a flag or something if neccessary.

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxActionsCount = 10, MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	int ActionsCount;
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)

	CFigure* SelectedFig; //Pointer to the selected figure

	Action* ActionList[MaxActionsCount];
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	CFigure* GetSelectedFigure() const;
	void ExecuteUndoAction();

	CFigure* GetTheLastDrawnObject() const;

	void AddAction(Action* pAction);
	void Save_All() const;

	string* GetGraphFiles(int& lineCount) const;
		
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
};

#endif