#pragma once
#include "../Actions/Action.h"
#include "../Figures/CFigure.h"

class DeleteAction : public Action
{private:
	CFigure* Selected_Figure;
public:
	DeleteAction(ApplicationManager* pApp);
	virtual void RedoAction();
	//Reads delete parameters
	virtual void ReadActionParameters();
	virtual void UndoAction();
	//Add delete to the ApplicationManager
	virtual void Execute();
	~AddDeleteAction();
};

