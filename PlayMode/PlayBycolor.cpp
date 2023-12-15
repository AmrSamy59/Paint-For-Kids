#include "PlayBycolor.h"
#include<iostream>
using namespace std;
PlayBycolor::PlayBycolor(ApplicationManager* pApp):Action(pApp)
{

}

void PlayBycolor::UndoAction()
{
}

void PlayBycolor::ReadActionParameters()
{
}

void PlayBycolor::Execute()
{
	int	Hits = 0;
	int Misses = 0;
	Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();
	pManager->Playlistformation();

	int FigsCount = pManager->GetFigsCount();
	
	int color_index = rand() % 6;

	CFigure* randomfig = pManager->GetRandomfigure();
	color* c = randomfig->GetFillColor();

	string randomColor = pout->GetColorName(*c);
	
	int ColorsCount[6] = {0,0,0,0,0,0};

	for (int i = 0; i < 6; i++) {
		ColorsCount[i] = pManager->GetColoredFigsCount(UI.drawColors[i]);
	}
	pout->PrintMessage("Pick " + UI.drawColors[color_index] + " Figures");
	while(Hits != ColorsCount[color_index])
	{
		pin->GetPointForDrawing(Ps.x, Ps.y, pout);
		pout->ClearStatusBar();
		if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
		{
			ptrfigure = pManager->GetFigure(Ps.x, Ps.y);
			ptrfigure->SetSelected(true);
			ptrfigure->SetFigureAbilityToBeDrawn(false);
			pManager->UpdateInterface();
			color* c = ptrfigure->GetFillColor();
			if (c) {
				string color_name = pout->GetColorName(*c);
				if (color_name == randomColor)
					Hits++;
				else
					Misses++;
			}
			else
				Misses++;

		}

	}
	pout->PrintMessage("You got " + to_string(Hits) + " Correct Hit(s) [" + randomColor + " Figures(s)] & " + to_string(Misses) + " Misses!      Click anywhere to end the game.");
	pin->GetPointClicked(Ps.x, Ps.y);
	pout->ClearStatusBar();
	pManager->ResetPlayMode(); // Reset Play Mode after the game ends
}
