#ifndef _SAVE_GRAPH_ACTION_H
#define _SAVE_GRAPH_ACTION_H

#include "../Actions/Action.h"
#include"../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "..\Actions\DeleteAction.h"
#include <iostream>
#include "../Figures\CFigure.h"


class SaveGraph : public Action
{
private:
	string fname;
	int FigCount;
	CFigure** FigList;
public:

	// Reads graph parameters
	SaveGraph(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void UndoAction();
	virtual void RedoAction();
	// Loads the graph
	virtual void Execute();
};

#endif /* Load Graph Action */

