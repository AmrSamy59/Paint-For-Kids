#pragma once
#include "Actions/Action.h"
#include "Select.h"

class AddDeleteAction : public Action
{private:
public:
	AddDeleteAction(ApplicationManager* pApp);
	//Reads delete parameters
	virtual void ReadActionParameters();

	//Add delete to the ApplicationManager
	virtual void Execute();
};

