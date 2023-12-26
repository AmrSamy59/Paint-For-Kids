#include "PlayByboth.h"

PlayByboth::PlayByboth(ApplicationManager* pApp):Action(pApp)
{
	voice = "Sound\\Pick By Type and Color.wav"; // voice 
}

void PlayByboth::UndoAction()
{

}

void PlayByboth::RedoAction()
{
}

void PlayByboth::ReadActionParameters()
{
}

void PlayByboth::Execute()
{
	PlayActionVoice();  // function that play voice here to play voice after click icon Immediately
	//Get a Pointer to the Input / Output Interfaces
	Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();
	pManager->Playlistformation(); //  playable figures list 

	int Hits = 0; // hits for correct answer
	int Misses = 0; // Misses for wrong answer
	int Maxhits = 0; 
	CFigure* randomfig = pManager->GetRandomfigure(); //random figure
	if (!randomfig) {
		pout->PrintMessage("There are no figures to play with.");
		return;
	}  // this condition perform  when there no figures if no random so no figures in play list
	string color_name="";
	string type = randomfig->GetType();  // type of  random that be choosen figure one from five shapes 
	color_name = pout->GetColorName(randomfig->GetFillColor()); //color for the random figure
	Maxhits = pManager->GetSpecificTypeCount(type, color_name); // max number condition for whlie loop 

	pout->PrintMessage("Pick " + color_name + " " + type + "s, right-click or change mode anytime to end the game.");

	clicktype cType;
	while(Hits < Maxhits)
	{
		cType = pin->GetPointClicked(Ps.x, Ps.y);
		//////////// cancel by right click ////////////////
		if (cType == RIGHT_CLICK)
		{
			pout->PrintMessage("Operation canceled (Right Click), You got " + to_string(Hits) + " Correct Hit(s) [ " + color_name + " " + type + "s ] & " + to_string(Misses) + " Misses!");
			isCanceled = true;
			pManager->ResetPlayMode();
			pManager->UpdateInterface();

			return;
		}
		//////////// cancel by change operation by click on icons in play mode tool bar  /////////////////////
		if (Ps.x <= PLAY_ITM_COUNT * UI.MenuItemWidth && Ps.y <= UI.ToolBarHeight) //// 250 is icons size 5*50=250 //////
		{
			pout->PrintMessage("Operation canceled (Mode Changed), You got " + to_string(Hits) + " Correct Hit(s) [ " + color_name + " " + type + "s ] & " + to_string(Misses) + " Misses!");
			isCanceled = true;
			Action* pAct = NULL;
			ActionType ActType = pin->GetUserAction();
			pManager->ResetPlayMode();
			pManager->UpdateInterface();
			if (ActType != PLAYING_AREA)
				pManager->ExecuteAction(ActType);

			return;

		}
		ptrfigure = pManager->GetFigure(Ps.x, Ps.y);
		if (ptrfigure != NULL && ptrfigure->isFigureShown())
		{  // condtion --> in this point if found figure and figure not hidden 
			ptrfigure->SetSelected(true);  // make figure select 
			ptrfigure->showFigure(false);  // make figure hidden 
			pManager->UpdateInterface();

			if (ptrfigure->GetType() == type && pout->GetColorName(ptrfigure->GetFillColor())== color_name) /// condtion --> increase count for true figure that has same color and type and decrease count for wrong figure 
				Hits++;
			else
				Misses++;

		}
	
	}

	pout->PrintMessage("You got " + to_string(Hits) + " Correct Hit(s) [ " + color_name + " " + type + "s ] & " + to_string(Misses) + " Misses!      Click anywhere to end the game.");
	pin->GetPointClicked(Ps.x, Ps.y);
	pManager->ResetPlayMode(); // Reset Play Mode after the game ends
	pout->ClearStatusBar();
	
	
}
