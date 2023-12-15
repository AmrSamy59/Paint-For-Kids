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
/*	int	Rightcount = 0;
	int Falsecount = 0;
	Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();
	pManager->Playlistformation();
	pout->GetColorFromName("Red");
	pout->PrintMessage("start");
	//ptrfigure->get();
	
//Output::GetColorName(FigGfxInfo.isFilled ? FigGfxInfo.FillClr : false);
int randomnumber = rand() % 6;
string randomcolor= colors[randomnumber] ;
cout << randomcolor << endl;

for (int i = 0; i < 200; i++)
{
	pin->GetPointForDrawing(Ps.x, Ps.y, pout);
	pout->ClearStatusBar();
	if (pManager->GetFigure(Ps.x, Ps.y) != NULL)
	{
		ptrfigure = pManager->GetFigure(Ps.x, Ps.y);
		ptrfigure->SetSelected(true);
		ptrfigure->SetFigureAbilityToBeDrawn(false);
		pManager->UpdateInterface();
		if (randomcolor == "Red")
		{
			Rightcount++;
			cout << 1;
		}
		else
			cout << -1;//	Falsecount++;
		if(randomcolor == "Green")
			cout << 2;//Rightcount++;
		else
			cout << -2;//	Falsecount++;
		if (randomcolor == "Blue")
			cout << 3;//Rightcount++;
		else
			cout << -3;	//Falsecount++;
		if (randomcolor == "Black")
			cout << 4;//Rightcount++;
		else
			cout << -4;//Falsecount++;
		if (randomcolor == "Orange")
			cout << 5;// Rightcount++;
		else
			cout << -5;//Falsecount++;
		if (randomcolor == "Yellow")
			cout << 6;	//Rightcount++;
		else
			cout << -6;	//Falsecount++;


		

	}

}
cout << "R   " << Rightcount << endl;
cout << "F  " << Falsecount << endl;*/
}
