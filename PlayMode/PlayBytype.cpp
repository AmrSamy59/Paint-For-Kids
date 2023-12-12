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
	pManager->Playlistformation();
	pManager->Playmodecounter();
	int Rectanglecount = pManager->Getrectanglecount();
	int Squarecount = pManager->Getsquarecount();
	int Trianglecount = pManager->Gettrianglecount();
	int Hexagoncount = pManager->Getheaxgoncount();
	int Circlecount = pManager->Getcirclecount();
	int Figuerscount=0;
	int Rightcount=0;
	int Falsecount=0;
	int arrayofcount[5] = { Rectanglecount,Squarecount,Trianglecount,Hexagoncount,Circlecount };
	for (int i = 0; i < 5; i++) {

		Figuerscount += arrayofcount[i];
	}
	int Figureindex=0;
	string randomfig = pManager->Randomfigure();
	for (int i = 0; i < 5; i++) {
		if (randomfig == figuers[i])
			Figureindex = i;
	}
	pout->PrintMessage(" pick " + to_string(arrayofcount[Figureindex]) + " " + this->figuers[Figureindex] + " ");
	
	
	for (int i = 0; i < 200; i++)
	{
		if (Rightcount == arrayofcount[Figureindex])
			break;
		pout->PrintMessage(" pick " + to_string(arrayofcount[Figureindex]) + " " + this->figuers[Figureindex]  + " ");
		pin->GetPointForDrawing(Ps.x, Ps.y,pout);

		pout->ClearStatusBar();

		if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
		{
			ptrfigure = pManager->GetFigure(Ps.x, Ps.y);
			ptrfigure->SetSelected(true);
			ptrfigure->SetFigureAbilityToBeDrawn(false);
			pManager->UpdateInterface();
			if (figuers[Figureindex] == "rectangle")
			{
				if (dynamic_cast<CRectangle*>(ptrfigure) != NULL)
					Rightcount++;
				else
					Falsecount++;
			}
			else if (figuers[Figureindex] == "square") {
				if (dynamic_cast<CSquare*>(ptrfigure) != NULL)
					Rightcount++;
				else
					Falsecount++;
			}
			else if (figuers[Figureindex] == "triangle") {
				if (dynamic_cast<CTriangle*>(ptrfigure) != NULL)
					Rightcount++;
				else
					Falsecount++;
			}
			else if (figuers[Figureindex] == "hexagon") {
				if (dynamic_cast<CHexagon*>(ptrfigure) != NULL)
					Rightcount++;
				else
					Falsecount++;
			}
			else if (figuers[Figureindex] == "circle") {
				if (dynamic_cast<CCircle*>(ptrfigure) != NULL)
					Rightcount++;
				else
					Falsecount++;
			}
		
	
		}
		
	}
	pout->PrintMessage(" You have got  " + to_string(Rightcount) + " correct figuers and choose " + to_string(Falsecount)+" wrong figuers "+"         "+" click any where to done");

	pin->GetPointClicked(Ps.x, Ps.y);
	pout->ClearStatusBar();
	pManager->Drawinplaymode();
	
	


}



