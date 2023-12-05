#pragma once
#include "Actions/Action.h"
class AddClearAllAction : public Action
{
public:
	AddClearAllAction();
	//Reads clear all parameters
	virtual void ReadActionParameters();

	//Add clear all to the ApplicationManager
	virtual void Execute();
};

