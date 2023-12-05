#pragma once
#include "Actions/Action.h"
class AddDeleteAction : public Action
{
public:
	AddDeleteAction();
	//Reads delete parameters
	virtual void ReadActionParameters();

	//Add delete to the ApplicationManager
	virtual void Execute();
};

