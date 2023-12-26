#ifndef _SELECT_H
#define _SELECT_H

#include "../Actions/Action.h"
#include "..\GUI\Output.h"
#include "..\GUI\Input.h"
#include "..\ApplicationManager.h"
class Select : public Action
{
private :
	Point Ps;
	clicktype cType;
	CFigure* selectedFigure;
	bool wasUnselected;
	int selectedID;
	bool isSelectButton; // true if the action is triggered by the select button, false if it's triggered by any other action
public :
	Select(ApplicationManager* pApp,bool flg = false);
	bool wasCanceled();
	virtual void RedoAction();
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void PlayRecordingFunc();
	virtual void UndoAction();
};
#endif 