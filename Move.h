#ifndef _MOVE_H
#define _MOVE_H
#include "Actions/Action.h"


class Move : public Action
{
private :
	Point Pf;

public:
	Move(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif // !_MOVE_H

