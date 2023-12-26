#pragma once
#include "../Actions/Action.h"
#include "../Figures/CFigure.h"

class DeleteAction : public Action
{private:
	CFigure* Selected_Figure;  //A pointer to the selected figure
	int selectedID = -1;   //shows the ID of the deleted figure
	bool playRec = false;  //Checking whether the program is playing the record or not
public:
	DeleteAction(ApplicationManager* pApp);
	virtual void RedoAction();
	//Reads delete parameters
	virtual void ReadActionParameters();
	virtual void UndoAction();
	virtual void PlayRecordingFunc();
	//Add delete to the ApplicationManager
	void setPlayRec(bool rec);
	virtual void Execute();
	~DeleteAction();
};

