#ifndef _SELECT_H
#define _SELECT_H

#include "Actions/Action.h"

class Select : public Action
{
private :
	Point Ps;
public :
	Select(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void UndoAction();
};
#endif 