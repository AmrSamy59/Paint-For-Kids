#pragma once

#include"../Actions/Action.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
#include "../Figures/CFigure.h"

class FillColorAction : public Action {
private:
	CFigure* SelectedFigure;
	color c_fillColor;
	bool c_isFilled;
	color fillColor;
	bool isFilled;
	int selectedID = -1;
public:
	FillColorAction(ApplicationManager* pApp);
	virtual void RedoAction();
	//Reads parameters required for action to execute
	void ReadActionParameters();

	//Execute action (code depends on action type)
	void Execute();

	//Playing the recording of filling color action
	virtual void PlayRecordingFunc();

	//To undo this action (code depends on action type)
	virtual void UndoAction();


	~FillColorAction();

};