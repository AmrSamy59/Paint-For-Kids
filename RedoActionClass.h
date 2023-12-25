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
	int ActionID;
	int selectingNum;
public:
	RedoActionClass(ApplicationManager* pApp);
	virtual void UndoAction();
	virtual void RedoAction();
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();
	void SetActionID(int id);
	void SetSelectingNum(int c);
	virtual void PlayRecordingFunc();
	//Execute action (code depends on action type)
	virtual void Execute();

};

