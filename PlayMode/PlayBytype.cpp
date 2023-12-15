#include "PlayBytype.h"

#include<iostream>

PlayByType::PlayByType(ApplicationManager* pApp) :Action(pApp)
{
}

void PlayByType::UndoAction()
{
}

void PlayByType::ReadActionParameters()
{

}

void PlayByType::Execute()
{	
	//Get a Pointer to the Input / Output Interfaces
Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();
	pManager->Playlistformation();

	int RectCount = CRectangle::GetCount();
	int SquareCount = CSquare::GetCount();
	int TriangleCount = CTriangle::GetCount();
	int HexagonCount = CHexagon::GetCount();
	int CircleCount = CCircle::GetCount();

	int Hits = 0;
	int Misses = 0;
	string FigNames[5] = { "rectangle", "square", "triangle", "hexagon", "circle" };
	int FigsCount[5] = { RectCount,SquareCount,TriangleCount,HexagonCount,CircleCount };

	int Figureindex=0;
	string randomfig = pManager->GetRandomfigure()->GetType();
	for (int i = 0; i < 5; i++) {
		if (randomfig == FigNames[i]) {
			Figureindex = i;
			break;
		}
	}
	pout->PrintMessage("Pick " + FigNames[Figureindex] + "(s)");
	
	
	while (Hits != FigsCount[Figureindex])
	{
		pin->GetPointClicked(Ps.x, Ps.y);

		if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
		{
			ptrfigure = pManager->GetFigure(Ps.x, Ps.y);
			ptrfigure->SetSelected(true);
			ptrfigure->SetFigureAbilityToBeDrawn(false);
			pManager->UpdateInterface();

			if(ptrfigure->GetType() == FigNames[Figureindex])
				Hits++;
			else
				Misses++;
	
		}
	}
	pout->PrintMessage("You got " + to_string(Hits) + " Correct Hit(s) ["+ FigNames[Figureindex]  +"(s)] & " + to_string(Misses) + " Misses!      Click anywhere to end the game.");

	pin->GetPointClicked(Ps.x, Ps.y);
	pout->ClearStatusBar();
	pManager->ResetPlayMode(); // Reset Play Mode after the game ends
	
	

}



