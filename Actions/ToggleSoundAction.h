#pragma once
#include "Action.h"
#include"../ApplicationManager.h"
#include "../GUI/Output.h"
#include"../GUI/Input.h"
#include"../GUI/UI_Info.h"
class ToggleSoundAction :public Action
{
public:
	ToggleSoundAction(ApplicationManager* pApp);
	// virtual void slected_figure(Select*ptrselected );
	void UndoAction();
	void RedoAction();
	//Reads parameters required for action to execute (code depends on action type)
	void ReadActionParameters();
	//Execute action (code depends on action type)
	void Execute();
};

