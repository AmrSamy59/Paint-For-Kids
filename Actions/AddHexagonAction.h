#ifndef _ADD_HEXAGON_ACTION_H
#define _ADD_HEXAGON_ACTION_H
#include "../Actions\Action.h"
#include "../Figures\CHexagon.h"
#include "../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "..\Actions\DeleteAction.h"
class AddHexagonAction:public Action 
{
private:
	Point center;
	GfxInfo HexagonGfxInfo;
	CFigure* LastDrawnHexagon;
	CFigure* copyLastDrawnHexagon;
public:
	AddHexagonAction(ApplicationManager* pApp);

	//Reads hexagon parameters
	virtual void ReadActionParameters();
	virtual void PlayRecordingFunc();
	virtual void UndoAction();
	virtual void RedoAction();
	//Add hexagon to the ApplicationManager
	virtual void Execute();


};



#endif // !1

