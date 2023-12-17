#pragma once
#include "Actions\Action.h"

#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include "Figures/CRectangle.h"
#include "Actions/DeleteAction.h"
#include "Figures/CFigure.h"

class RedoActionClass :	public Action
{
private:
	Action* PassedAction;
	//CFigure* PassedFigure;
public:
	RedoActionClass(ApplicationManager* pApp);
	virtual void UndoAction();
	virtual void RedoAction();
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

};

