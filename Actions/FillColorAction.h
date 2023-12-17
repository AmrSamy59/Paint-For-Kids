#pragma once

#include"../Actions/Action.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
#include "../Figures/CFigure.h"

class FillColorAction : public Action {
private:
	CFigure* SelectedFigure;
	color* fillColor[2];
	bool isFilled[2];
public:
	FillColorAction(ApplicationManager* pApp);
	virtual void RedoAction();
	//Reads parameters required for action to execute
	void ReadActionParameters();

	//Execute action (code depends on action type)
	void Execute();

	//To undo this action (code depends on action type)
	virtual void UndoAction();


	~FillColorAction();

};