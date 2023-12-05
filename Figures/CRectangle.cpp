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
	int xmin = min(Corner1.x, Corner2.x);
	int xmax = max(Corner1.x, Corner2.x);

	int ymin = min(Corner1.y, Corner2.y);
	int ymax = max(Corner1.y, Corner2.y);

	return (x >= xmin && x <= xmax && y >= ymin && y <= ymax);
}
void CRectangle::Save(ofstream& OutFile)
{
	OutFile << "RECT" << "\t" << ID << "\t" << Corner1.x << "\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y << "\t" << endl;
}