#pragma once

#include"../Actions/Action.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
#include "../Figures/CFigure.h"

class DrawColorAction : public Action {
private:
	CFigure* SelectedFigure;
	color* drawColor[2];
public:
	DrawColorAction(ApplicationManager* pApp);
	virtual void RedoAction();
	//Reads parameters required for action to execute
	void ReadActionParameters();

	//Execute action (code depends on action type)
	void Execute();

	//To undo this action (code depends on action type)
	void UndoAction();


	~DrawColorAction();

};