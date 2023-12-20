#ifndef _ADDAQUAREACTION_H
#define _ADDAQUAREACTION_H

#include "..\Actions\Action.h"
#include"../Figures\CSquare.h"
#include"../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "..\Actions\DeleteAction.h"

class AddSquareAction :public Action {
private:
	Point CENTER; // center of square
	GfxInfo squareGfxInfo; 
	CFigure* LastDrawnSquare;
public:
	AddSquareAction(ApplicationManager* pApp);
	virtual void RedoAction();
	//Reads square parameters
	virtual void ReadActionParameters();
	virtual void PlayRecordingFunc();
	virtual void UndoAction();
	//Add square to the ApplicationManager
	virtual void Execute();

};

#endif // !1

