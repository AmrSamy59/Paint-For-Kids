#pragma once
#include "../Actions/Action.h"
#include "../Figures/CFigure.h"

class DeleteAction : public Action
{private:
	CFigure* Selected_Figure;
	int selectedID;
public:
	DeleteAction(ApplicationManager* pApp);
	virtual void RedoAction();
	//Reads delete parameters
	virtual void ReadActionParameters();
	virtual void UndoAction();
	virtual void PlayRecordingFunc();
	//Add delete to the ApplicationManager
	virtual void Execute();
	~DeleteAction();
};

