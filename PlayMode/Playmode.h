#pragma once
#include "../DEFS.h"
#include "../GUI/Output.h"
#include"../Actions/SelectAction.h"
#include"../Actions/Action.h"
#include"../ApplicationManager.h"
#include"../Actions/SelectAction.h"
#include"../Figures/CFigure.h"
#include"../Figures/CRectangle.h"
#include"../Figures/CHexagon.h"
#include"../Figures/CCircle.h"
#include"../Figures/CSquare.h"
#include"../Figures/CTriangle.h"
class Playmode :public Action {
private:
	Point Ps;
	string figuers[5] = { "rectangle","square","triangle","hexagon","circle" };
	//ApplicationManager* pManager;
	Select* ptrselect=new Select(pManager);
	CFigure* ptrfigure;
public:
	Playmode(ApplicationManager* pApp);
	// virtual void slected_figure(Select*ptrselected );
	void UndoAction() ;
	//Reads parameters required for action to execute (code depends on action type)
	 void ReadActionParameters() ;
	//Execute action (code depends on action type)
	 void Execute() ;
	 void play();
	 
};