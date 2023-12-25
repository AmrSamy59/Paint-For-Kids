#pragma once

#include "Actions\Action.h"

#include "ApplicationManager.h"
#include "GUI\input.h"
#include "GUI\Output.h"
#include "Figures/CRectangle.h"
#include "Actions/DeleteAction.h"
#include "Figures/CFigure.h"



class UndoActionClass :	public Action
{
private:
	Action* PassedAction;
	CFigure* PassedFigure;
	int ActionID;
	int selectingNum = 2;
public:
	UndoActionClass(ApplicationManager* pApp);
	virtual void RedoAction();
	virtual void ReadActionParameters();
	virtual void UndoAction();
	virtual void PlayRecordingFunc();
	int GetActionID();
	void SetActionID(int id);
	void SetSelectingNum(int c);
	virtual void Execute();

};

