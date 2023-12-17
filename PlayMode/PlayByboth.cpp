#include "PlayByboth.h"

PlayByboth::PlayByboth(ApplicationManager* pApp):Action(pApp)
{

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
	Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();
	pManager->Playlistformation();

	int Hits = 0;
	int Misses = 0;
	int Maxhits = 0;
	CFigure* randomfig = pManager->GetRandomfigure(); //random figure
	string color_name=" ";
	//string name = " ";
	/*if ((randomfig->GetFillColor()) != nullptr)
	{
		color_name = pout->GetColorName(*randomfig->GetFillColor()); //color for the random figure
	}
	name = "NO_COLOR";
	cout << color_name;*/
	string type = randomfig->GetType();
	color_name = pout->GetColorName(*randomfig->GetFillColor()); //color for the random figure
	Maxhits =	pManager->Playmode_both(type, color_name); // max number condition for whlie loop 
	pout->PrintMessage("Pick " + type + " with " + color_name + " color ");
	//if(name!= "NO_COLOR")
	while(Hits < Maxhits)
	{
		pin->GetPointClicked(Ps.x, Ps.y);
		if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
		{
			ptrfigure = pManager->GetFigure(Ps.x, Ps.y);
			ptrfigure->SetSelected(true);
			ptrfigure->SetFigureAbilityToBeDrawn(false);
			pManager->UpdateInterface();

			if (ptrfigure->GetType() == type && pout->GetColorName(*ptrfigure->GetFillColor())== color_name)
				Hits++;
			else
				Misses++;

		}
	
	}
/*	else
		while (Hits != Maxhits)
		{
			pin->GetPointClicked(Ps.x, Ps.y);

			if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
			{
				ptrfigure = pManager->GetFigure(Ps.x, Ps.y);
				ptrfigure->SetSelected(true);
				ptrfigure->SetFigureAbilityToBeDrawn(false);
				pManager->UpdateInterface();

				if (ptrfigure->GetType() == type)
					Hits++;
				else
					Misses++;

			}
		}
		*/
	pout->PrintMessage("You got " + to_string(Hits) + " Correct Hit(s) [ Figure(s) ] & " + to_string(Misses) + " Misses!      Click anywhere to end the game.");

	pin->GetPointClicked(Ps.x, Ps.y);
	pout->ClearStatusBar();
	pManager->ResetPlayMode(); // Reset Play Mode after the game ends
	
}
