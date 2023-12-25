#ifndef _SELECT_H
#define _SELECT_H

#include "../Actions/Action.h"

class Select : public Action
{
private :
	Point Ps;
	clicktype cType;
	int selectedID;
	bool flag;
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