#include "PlayBycolor.h"
#include<iostream>
using namespace std;
PlayBycolor::PlayBycolor(ApplicationManager* pApp):Action(pApp)
{
	voice = "Sound\\Pick By Color.wav";
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
	PlayActionVoice();
	Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();
	const int c_count = UI.c_cols * UI.c_rows;
	int* ColorsCount = new int[c_count];
	for (int i = 0; i < c_count; i++) {
		ColorsCount[i] = 0;
	}
	
	int Sum_of_colors = 0;
	for (int i = 0; i < c_count; i++) {
		ColorsCount[i] = pManager->GetColoredFigsCount(UI.drawColors[i]);
		Sum_of_colors += ColorsCount[i];
	}

	if(Sum_of_colors== ColorsCount[c_count-1])
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
	cout << "color " << endl;
	color c = randomfig->GetFillColor();
	
	/////////////////////////////////

	for (int i = 0; i < c_count; i++)
	{
		if (UI.drawColorsEq[i] == c)
		{
			color_index = i;
			if (color_index == 7)
				
			break;
		}
	} /// search for color index in array of color in UI

	string randomColor = pout->GetColorName(c);
	
	while (randomColor == "Transparent")
	{
		randomfig = pManager->GetRandomfigure();
		c = randomfig->GetFillColor();
		randomColor= pout->GetColorName(c);

	}

	for (int i = 0; i < c_count; i++)
	{
		if (UI.drawColorsEq[i] == c)
		{
			color_index = i;
			if (color_index == 7)
				
				break;
		}
	}   /// search for color index in array of color in UI after neglected transparent color 
	
	pout->PrintMessage("Pick " + UI.drawColors[color_index] + " Figures, right-click or change mode anytime to end the game.");
	
	clicktype cType;
	while(Hits < ColorsCount[color_index])
	{
		cType = pin->GetPointClicked(Ps.x, Ps.y);
		
		if (cType == RIGHT_CLICK)
		{
			pout->PrintMessage("Operation canceled (Right Click), You got " + to_string(Hits) + " Correct Hit(s) [" + randomColor + " Figures] & " + to_string(Misses) + " Misses!");
			isCanceled = true;
			pManager->ResetPlayMode();
			pManager->UpdateInterface();

			return;
		}
		if (Ps.x <= PLAY_ITM_COUNT * UI.MenuItemWidth && Ps.y <= UI.ToolBarHeight) //// 250 is icons size 5*50=250 //////
		{
			pout->PrintMessage("Operation canceled (Mode Changed), You got " + to_string(Hits) + " Correct Hit(s) [" + randomColor + " Figures] & " + to_string(Misses) + " Misses!");
			isCanceled = true;
			Action* pAct = NULL;
			ActionType ActType = pin->GetUserAction();
			pManager->ResetPlayMode();
			pManager->UpdateInterface();
			if (ActType != PLAYING_AREA)
				pManager->ExecuteAction(ActType);

			return;

		}
		
		pout->ClearStatusBar();
		ptrfigure = pManager->GetFigure(Ps.x, Ps.y);
		if (ptrfigure != NULL && ptrfigure->isFigureShown())
		{
			ptrfigure->SetSelected(true);
			ptrfigure->showFigure(false);
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
	pManager->ResetPlayMode(); // Reset Play Mode after the game ends
	pout->ClearStatusBar();
	

	delete[] ColorsCount;
}
