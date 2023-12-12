#include "PlayBytype.h"

#include<iostream>

Playmode::Playmode(ApplicationManager* pApp) :Action(pApp)
{
}

void Playmode::UndoAction()
{
}

void Playmode::ReadActionParameters()
{

}

void Playmode::Execute()
{	
	//Get a Pointer to the Input / Output Interfaces
Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();
	pManager->playmode();
	pManager->playmodecounter();
	int rectanglecount = pManager->getrectanglecount();
	int squarecount = pManager->getsquarecount();
	int trianglecount = pManager->gettrianglecount();
	int hexagoncount = pManager->getheaxgoncount();
	int circlecount = pManager->getcirclecount();
	int figuerscount=0;
	int rightcount=0;
	int falsecount=0;
	int arrayofcount[5] = { rectanglecount,squarecount,trianglecount,hexagoncount,circlecount };
	for (int i = 0; i < 5; i++) {

		figuerscount += arrayofcount[i];
	}
	int figureindex=0;
	string radnomfig = pManager->radnomfigure();

	for (int i = 0; i < 5; i++) {
		if (radnomfig == figuers[i])
			figureindex = i;
	}
	pout->PrintMessage(" pick " + to_string(arrayofcount[figureindex]) + " " + this->figuers[figureindex] + " ");
	
	
	for (int i = 0; i < 200; i++)
	{
		if (rightcount == arrayofcount[figureindex])
			break;
		pout->PrintMessage(" pick " + to_string(arrayofcount[figureindex]) + " " + this->figuers[figureindex]  + " ");
		pin->GetPointForDrawing(Ps.x, Ps.y,pout);

		pout->ClearStatusBar();

		if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
		{
			ptrfigure = pManager->GetFigure(Ps.x, Ps.y);
			ptrfigure->SetSelected(true);
			ptrfigure->SetFigureAbilityToBeDrawn(false);
			pManager->UpdateInterface();
			if (figuers[figureindex] == "rectangle")
			{
				if (dynamic_cast<CRectangle*>(ptrfigure) != NULL)
					rightcount++;
				else
					falsecount++;
			}
			else if (figuers[figureindex] == "square") {
				if (dynamic_cast<CSquare*>(ptrfigure) != NULL)
					rightcount++;
				else
					falsecount++;
			}
			else if (figuers[figureindex] == "triangle") {
				if (dynamic_cast<CTriangle*>(ptrfigure) != NULL)
					rightcount++;
				else
					falsecount++;
			}
			else if (figuers[figureindex] == "hexagon") {
				if (dynamic_cast<CHexagon*>(ptrfigure) != NULL)
					rightcount++;
				else
					falsecount++;
			}
			else if (figuers[figureindex] == "circle") {
				if (dynamic_cast<CCircle*>(ptrfigure) != NULL)
					rightcount++;
				else
					falsecount++;
			}
		
	
		}
		
	}
	pout->PrintMessage(" You have got  " + to_string(rightcount) + " correct figuers and choose " + to_string(falsecount)+" wrong figuers "+"         "+" click any where to done");
	

	
	pin->GetPointClicked(Ps.x, Ps.y);
	pManager->drawinplaymode();
	ptrfigure->SetSelected(false);
	


}



