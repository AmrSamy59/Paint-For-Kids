#ifndef _MOVE_H
#define _MOVE_H
#include "../Actions/Action.h"
#include "../ApplicationManager.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"

#include <iostream>
using namespace std;

class Move : public Action
{
private :
	Point Pf[2];    //An array contains the initial center of the figure before moving and the final center after moving
	CFigure* fig;  //The figure that moves
	int selectedID = -1; //The ID of the figure that moves
public:
	Move(ApplicationManager* pApp); //Constructor
	virtual void RedoAction(); //Redo (Move Action)
	virtual void ReadActionParameters(); 
	virtual void Execute();
	virtual void PlayRecordingFunc(); //Play (Move Action) in the recording
	virtual void UndoAction(); //Undo (Move Action)
};

#endif // !_MOVE_H

