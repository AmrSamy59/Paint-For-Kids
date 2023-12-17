#pragma once
#include "../Actions/Action.h"
class AddClearAllAction : public Action
{
public:
	AddClearAllAction(ApplicationManager* pApp);
	virtual void RedoAction();
	//Reads clear all parameters
	virtual void ReadActionParameters();
	virtual void UndoAction();
	//Add clear all to the ApplicationManager
	virtual void Execute();
};

