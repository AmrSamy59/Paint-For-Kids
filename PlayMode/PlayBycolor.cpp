#include "PlayBycolor.h"
#include<iostream>
using namespace std;
PlayBycolor::PlayBycolor(ApplicationManager* pApp):Action(pApp)
{

}

void PlayBycolor::UndoAction()
{
}

void PlayBycolor::RedoAction()
{
}

void PlayBycolor::ReadActionParameters()
{
}

void PlayBycolor::Execute()
{
	Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();
	const int c_count = UI.c_cols * UI.c_rows;
	int* ColorsCount = new int[c_count]{ 0,0,0,0,0,0,0,0 };
	int Sum_of_colors = 0;
	for (int i = 0; i < c_count; i++) {
		ColorsCount[i] = pManager->GetColoredFigsCount(UI.drawColors[i]);
		cout << UI.drawColors[i] << " " << ColorsCount[i] << endl;
		Sum_of_colors += ColorsCount[i];
	}

	if(Sum_of_colors==0)
	{
		pout->PrintMessage("There are no colored figures");
		delete[] ColorsCount;
		return;
	}
	int	Hits = 0;
	int Misses = 0;
	pManager->Playlistformation();
	const int FigsCount = pManager->GetFigsCount();
	int color_index = 0;
	CFigure* randomfig = pManager->GetRandomfigure();
	if (!randomfig) {
		pout->PrintMessage("There are no figures to play with.");
		delete[] ColorsCount;
		return;
	}
	color c = randomfig->GetFillColor();
	
	/////////////////////////////////

	for (int i = 0; i < c_count; i++)
	{
		if (UI.drawColorsEq[i] == c)
		{
			color_index = i;
			break;
		}
	}

	string randomColor = pout->GetColorName(c);
	
	pout->PrintMessage("Pick " + UI.drawColors[color_index] + " Figures");
	while(Hits < ColorsCount[color_index])
	{
		pin->GetPointForDrawing(Ps.x, Ps.y, pout);
		pout->ClearStatusBar();
		if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
		{
			ptrfigure = pManager->GetFigure(Ps.x, Ps.y);
			ptrfigure->SetSelected(true);
			ptrfigure->SetFigureAbilityToBeDrawn(false);
			pManager->UpdateInterface();
			color c = ptrfigure->GetFillColor();
			string color_name = pout->GetColorName(c);
			if (color_name == randomColor)
				Hits++;
			else
				Misses++;
		}

	}
	pout->PrintMessage("You got " + to_string(Hits) + " Correct Hit(s) [" + randomColor + " Figures] & " + to_string(Misses) + " Misses!      Click anywhere to end the game.");
	pin->GetPointClicked(Ps.x, Ps.y);
	pout->ClearStatusBar();
	pManager->ResetPlayMode(); // Reset Play Mode after the game ends

	delete[] ColorsCount;
}
