#include "PlayByboth.h"

PlayByboth::PlayByboth(ApplicationManager* pApp):Action(pApp)
{

}

void PlayByboth::UndoAction()
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
	int both = 0;
	CFigure* randomfig = pManager->GetRandomfigure();
	string c = pout->GetColorName(*randomfig->GetFillColor());
	cout << "test: " << c << endl;
	string type = randomfig->GetType();
	cout << type << endl;
	both =	pManager->Playmode_both(type, c);
	cout << both << endl;
/*int RectCount = CRectangle::GetCount();
	int SquareCount = CSquare::GetCount();
	int TriangleCount = CTriangle::GetCount();
	int HexagonCount = CHexagon::GetCount();
	int CircleCount = CCircle::GetCount();
	int FigsCount[5] = { RectCount,SquareCount,TriangleCount,HexagonCount,CircleCount };
	*/
	/*int typeColorCounter = 0;
	Cfigure* randomFig = getRandomFig();
	color* figCol = randomFig->getFillColor();
	string figType = randomFig->getType();
	for (int i = 0; i < figCount; i++)
	{
		if (figList[i]->getType() == figType && figList[i]->getFillColor() == figCol)
			typeColorCounter++;
	}
	*/
}
