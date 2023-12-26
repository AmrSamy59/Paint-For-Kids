#ifndef _LOAD_GRAPH_ACTION_H
#define _LOAD_GRAPH_ACTION_H

#include "../Actions/Action.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "..\Actions\DeleteAction.h"
#include <iostream>
#include "../Figures\CFigure.h"
#include "..\Actions\AddRectAction.h"
#include "AddSquareAction.h"
#include "AddTriangleAction.h"
#include "AddHexagonAction.h"
#include "AddCircleAction.h"

class LoadGraph : public Action
{
private:
public:

	// Reads graph parameters
	LoadGraph(ApplicationManager* pApp);
	void Load(string fName);
	string* GetOptionParameters(string line, string option, string delimiter);
	virtual void ReadActionParameters();
	virtual void UndoAction();
	virtual void RedoAction();
	// Loads the graph
	virtual void Execute();
};

#endif /* Load Graph Action */

