#ifndef _ADD_CIRCLE_ACTION_H
#define _ADD_CIRCLE_ACTION_H

#include"Actions/Action.h"
#include"CCircle.h"
#include"ApplicationManager.h"
#include"GUI/Input.h"
#include"GUI/Output.h"
#include "DeleteAction.h"

class AddCircleAction :public Action
{
private:
	Point P1, P2; 
	GfxInfo CircleGfxInfo;
public:
	AddCircleAction(ApplicationManager* pApp);
	virtual void UndoAction();
	//Reads circle parameters
	virtual void ReadActionParameters();

	//Add circle to the ApplicationManager
	virtual void Execute();





};
#endif // !_ADD_CIRCLE_ACTION_H

