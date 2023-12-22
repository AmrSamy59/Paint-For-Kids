#ifndef _SELECT_H
#define _SELECT_H

#include "../Actions/Action.h"

class Select : public Action
{
private :
	Point Ps;
	clicktype cType;
public :
	Select(ApplicationManager* pApp);
	bool wasCanceled();
	virtual void RedoAction();
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void UndoAction();
};
#endif 