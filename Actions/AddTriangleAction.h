#ifndef ADD_TRIANGLE_ACTION_H
#define ADD_TRIANGLE_ACTION_H
#include"../Actions/Action.h"
#include"../Figures\CTriangle.h"
#include"../ApplicationManager.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"
#include "..\Actions\DeleteAction.h"
class AddTriangleAction :public Action
{
private:
	Point p1, p2, p3;
	GfxInfo triangleGfxInfo;
public:
	AddTriangleAction(ApplicationManager* pApp);

	//Reads triangle parameters
	virtual void ReadActionParameters();
	virtual void UndoAction();
	//Add triangle to the ApplicationManager
	virtual void Execute();





};

#endif // !1

