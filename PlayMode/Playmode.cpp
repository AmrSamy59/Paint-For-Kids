#include "Playmode.h"

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
	
	//pin->GetPointClicked(Ps.x, Ps.y);
	for (int i = 0; i < figuerscount; i++)
	{
		pin->GetPointClicked(Ps.x, Ps.y);
		if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
		{ 
			ptrfigure = pManager->GetFigure(Ps.x, Ps.y);
			ptrfigure->SetSelected(true);
			ptrfigure->SetFigureAbilityToBeDrawn(false);
			pManager->UpdateInterface();
	/*		if (dynamic_cast<CRectangle*>(ptrfigure) != NULL && figuers[figureindex] == "rectangle");
			rightcount++;
			*/
			///  need counter for right answer and false answer
			/////// need to return draws after end of game

		}

	}
	
	/*	pin->GetPointClicked(Ps.x, Ps.y);
		if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
		{
			 ptrfigure = pManager->GetFigure(Ps.x, Ps.y);

			ptrfigure->SetSelected(true);
			ptrfigure->SetFigureAbilityToBeDrawn(false);
		

		}

		pin->GetPointClicked(Ps.x, Ps.y);
		if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
		{
			 ptrfigure = pManager->GetFigure(Ps.x, Ps.y);

			ptrfigure->SetSelected(true);
			ptrfigure->SetFigureAbilityToBeDrawn(false);
		

		}
		pin->GetPointClicked(Ps.x, Ps.y);
		if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
		{
			ptrfigure = pManager->GetFigure(Ps.x, Ps.y);

			ptrfigure->SetSelected(true);
			ptrfigure->SetFigureAbilityToBeDrawn(false);
			

		}
		pin->GetPointClicked(Ps.x, Ps.y);
		if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
		{
			CFigure* ptrfigure = pManager->GetFigure(Ps.x, Ps.y);

			ptrfigure->SetSelected(true);
			ptrfigure->SetFigureAbilityToBeDrawn(false);
		

		}
		*/


}


void Playmode::play()
{
}

