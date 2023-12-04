#ifndef _ADD_HEXAGON_ACTION_H
#define _ADD_HEXAGON_ACTION_H
#include"Actions/Action.h"
class AddHexagonAction:public Action 
{
private:
	Point center;
	GfxInfo HexagonGfxInfo;
public:
	AddHexagonAction(ApplicationManager* pApp);

	//Reads hexagon parameters
	virtual void ReadActionParameters();

	//Add hexagon to the ApplicationManager
	virtual void Execute();


};



#endif // !1

