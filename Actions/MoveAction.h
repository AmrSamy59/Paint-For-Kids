#ifndef _MOVE_H
#define _MOVE_H
#include "../Actions/Action.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"

class Move : public Action
{
private :
	Point Pf;

public:
	Move(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void UndoAction();
};

#endif // !_MOVE_H

