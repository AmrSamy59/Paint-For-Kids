#pragma once
#include "Actions/Action.h"

#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include "Figures/CRectangle.h"
#include "Actions/DeleteAction.h"
#include "Figures/CFigure.h"

class PlayRecording : public Action
{
private:
	Action* PassedRecordingAction;
	bool canPlay = true;
public:
	PlayRecording(ApplicationManager* pApp);	//constructor
	void UndoAction();
	void RedoAction();
	//Reads parameters required for action to execute (code depends on action type)
	void ReadActionParameters();
	//Execute action (code depends on action type)
	void Execute();
};

