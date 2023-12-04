#ifndef _ADDAQUAREACTION_H
#define _ADDAQUAREACTION_H

#include "Actions/Action.h"
class AddSquareAction :public Action {
private:
	Point CENTER; // center of square
	GfxInfo squareGfxInfo; 
public:
	AddSquareAction(ApplicationManager* pApp);

	//Reads square parameters
	virtual void ReadActionParameters();

	//Add square to the ApplicationManager
	virtual void Execute();

};

#endif // !1

