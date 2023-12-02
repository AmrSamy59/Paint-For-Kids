#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

bool CRectangle::CheckSelection(int x, int y)
{
	if (x >= Corner1.x && x <= Corner2.x && y >= Corner1.y && y <= Corner2.y)
	{
		return true;
	}
	else
		return false;
}
void CRectangle::Save(ofstream& OutFile)
{
	OutFile << "RECT" << "\t" << ID << "\t" << Corner1.x << "\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y << "\t" << endl;
}