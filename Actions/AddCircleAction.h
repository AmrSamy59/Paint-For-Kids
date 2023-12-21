#ifndef _ADD_CIRCLE_ACTION_H
#define _ADD_CIRCLE_ACTION_H

#include"../Actions/Action.h"
#include"../Figures/CCircle.h"
#include"../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "../Actions/DeleteAction.h"

class AddCircleAction :public Action
{
private:
	Point P1, P2; 
	GfxInfo CircleGfxInfo;
	CFigure* LastDrawnCircle;
	CFigure* copyLastDrawnCircle;
public:
	AddCircleAction(ApplicationManager* pApp);
	virtual void PlayRecordingFunc();
	virtual void UndoAction();
	virtual void RedoAction();
	//Reads circle parameters
	virtual void ReadActionParameters();

	//Add circle to the ApplicationManager
	virtual void Execute();





};
#endif // !_ADD_CIRCLE_ACTION_H

