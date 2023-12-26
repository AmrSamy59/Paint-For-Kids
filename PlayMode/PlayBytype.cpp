#include "PlayBytype.h"

#include<iostream>

PlayByType::PlayByType(ApplicationManager* pApp) :Action(pApp)
{
	voice = "Sound\\Pick By Type.wav";  // voice 
}

void PlayByType::UndoAction()
{
}

void PlayByType::RedoAction()
{
}

void PlayByType::ReadActionParameters()
{

}

void PlayByType::Execute()
{	
	PlayActionVoice(); // function that play voice here to play voice after click icon Immediately
	//Get a Pointer to the Input / Output Interfaces
Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();
	pManager->Playlistformation(); //  playable figures list 
	//////// figures count /////////////////////// 
	int RectCount = CRectangle::GetCount(); 
	int SquareCount = CSquare::GetCount();
	int TriangleCount = CTriangle::GetCount();
	int HexagonCount = CHexagon::GetCount();
	int CircleCount = CCircle::GetCount();
	///////////////////////////////////////////////
	int Hits = 0; // hits for correct answer
	int Misses = 0; // Misses for wrong answer
	string FigNames[5] = { "rectangle", "square", "triangle", "hexagon", "circle" }; 
	int FigsCount[5] = { RectCount,SquareCount,TriangleCount,HexagonCount,CircleCount };
	int Figureindex=0; 
	CFigure* randomfig = pManager->GetRandomfigure(); // random figure
	 
	if (!randomfig) {
			pout->PrintMessage("There are no figures to play with.");
			return;
	} // this condition perform  when there no figures if no random so no figures in play list
	string randomfig_type = randomfig->GetType();  // type of  random that be choosen figure one from five shapes 
	for (int i = 0; i < 5; i++) {
		if (randomfig_type == FigNames[i]) {
			Figureindex = i;
			break;
		}
	} /// this for loop search for figure index  for determination its count by knowing its index that this index go to figscount array
	pout->PrintMessage("Pick " + FigNames[Figureindex] + "s, right-click or change mode anytime to end the game.");
	
	clicktype cType;
	while (Hits < FigsCount[Figureindex])
	{
		cType = pin->GetPointClicked(Ps.x, Ps.y);
		//////////// cancel by right click ////////////////
		
		if (cType == RIGHT_CLICK)
		{
			pout->PrintMessage("Operation canceled (Right Click), You got " + to_string(Hits) + " Correct Hit(s) [" + FigNames[Figureindex] + "(s)] & " + to_string(Misses) + " Misses! ");
			isCanceled = true;
			pManager->ResetPlayMode();
			pManager->UpdateInterface();

			return;
		} 
		//////////// cancel by change operation by click on icons in play mode tool bar  /////////////////////

		if (Ps.x <= PLAY_ITM_COUNT * UI.MenuItemWidth && Ps.y <= UI.ToolBarHeight) 
		{
			pout->PrintMessage("Operation canceled (Mode Changed), You got " + to_string(Hits) + " Correct Hit(s) [" + FigNames[Figureindex] + "(s)] & " + to_string(Misses) + " Misses! ");
			isCanceled = true;
			Action* pAct = NULL;
			ActionType ActType = pin->GetUserAction();
			pManager->ResetPlayMode();
			pManager->UpdateInterface();
			if(ActType != PLAYING_AREA)
				pManager->ExecuteAction(ActType);

			return;

		} 

		ptrfigure = pManager->GetFigure(Ps.x, Ps.y); 
		if (ptrfigure != NULL && ptrfigure->isFigureShown())
		{
			 // condtion --> in this point if found figure and figure not hidden 
			ptrfigure->SetSelected(true); // make figure select 
			ptrfigure->showFigure(false); // make figure hidden 
			pManager->UpdateInterface();

			if(ptrfigure->GetType() == FigNames[Figureindex]) /// condtion --> increase count for true figure and decrease count for wrong figure 
				Hits++;
			else
				Misses++;
	
		}

	}
	pout->PrintMessage("You got " + to_string(Hits) + " Correct Hit(s) ["+ FigNames[Figureindex]  +"(s)] & " + to_string(Misses) + " Misses!      Click anywhere to end the game.");
	pin->GetPointClicked(Ps.x, Ps.y);
	pManager->ResetPlayMode(); // Reset Play Mode after the game ends
	
	pout->ClearStatusBar();

}



