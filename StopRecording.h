#pragma once
#include "Actions/Action.h"

#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include "Figures/CRectangle.h"
#include "Actions/DeleteAction.h"
#include "Figures/CFigure.h"
class StopRecording :	public Action
{
private:
	
public:
	StopRecording(ApplicationManager* pApp);	//constructor
	void UndoAction();
	void RedoAction();
	//Reads parameters required for action to execute (code depends on action type)
	void ReadActionParameters();
	//Execute action (code depends on action type)
	void Execute();
};

