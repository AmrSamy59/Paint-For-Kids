#pragma once
#include "../Actions/Action.h"
#include "../Figures/CFigure.h"

class AddDeleteAction : public Action
{private:
	CFigure* Selected_Figure;
public:
	AddDeleteAction(ApplicationManager* pApp);
	//Reads delete parameters
	virtual void ReadActionParameters();
	virtual void UndoAction();
	//Add delete to the ApplicationManager
	virtual void Execute();
};

