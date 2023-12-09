#ifndef _LOAD_GRAPH_ACTION_H
#define _LOAD_GRAPH_ACTION_H

#include "Actions/Action.h"
#include"ApplicationManager.h"
#include"GUI/Input.h"
#include"GUI/Output.h"
#include "DeleteAction.h"

class LoadGraph : public Action
{
private:
public:

	// Reads graph parameters
	LoadGraph(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void UndoAction();
	// Loads the graph
	virtual void Execute();
};

#endif /* Load Graph Action */

