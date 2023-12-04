#ifndef _LOAD_GRAPH_ACTION_H
#define _LOAD_GRAPH_ACTION_H

#include "Actions/Action.h"
class LoadGraph : public Action
{
private:
public:

	// Reads graph parameters
	virtual void ReadActionParameters();

	// Loads the graph
	virtual void Execute();
};

#endif /* Load Graph Action */

