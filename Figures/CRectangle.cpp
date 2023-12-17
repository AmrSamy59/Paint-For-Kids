#include "CRectangle.h"
static int rectcount = 0;
CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
}

Point CRectangle::GetFigureCenter()
{
	Point p;
	p.x = (Corner1.x + Corner2.x) / 2;
	p.y = (Corner1.y + Corner2.y) / 2;
	return p;
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
	rectcount++;
}
void CRectangle::Move(Point Pm)
{
	Point P1n, P2n;
	P2n.x = Pm.x + (abs(Corner2.x - Corner1.x) / 2.0);
	P1n.x = Pm.x - (abs(Corner2.x - Corner1.x) / 2.0);
	P2n.y = Pm.y + (abs(Corner2.y - Corner1.y) / 2.0);
	P1n.y = Pm.y - (abs(Corner2.y - Corner1.y) / 2.0);
	double xDiff = P2n.x - P1n.x;
	double yDiff = P2n.y - P1n.y;
	if (P1n.y <= UI.ToolBarHeight)
	{
		P1n.y = UI.ToolBarHeight + 1;
		P2n.y = P1n.y + yDiff;
	}
	if (P2n.y >= (UI.height - UI.StatusBarHeight))
	{
		P2n.y = UI.height - UI.StatusBarHeight - 1;
		P1n.y = P2n.y - yDiff;
	}
	if (P1n.x < 0)
	{
		P1n.x = 1;
		P2n.x = P1n.x + xDiff;
	}
	if (P2n.x > UI.width)
	{
		P2n.x = UI.width - 1;
		P1n.x = P2n.x - xDiff;
	}
	Corner1 = P1n;
	Corner2 = P2n;
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
	string fcname = Output::GetColorName(FigGfxInfo.isFilled ? FigGfxInfo.FillClr : false); // Fill color
	string dcname = Output::GetColorName(FigGfxInfo.DrawClr); // Draw color

	OutFile << "RECT" << "\t" << ID << "\t" << Corner1.x << "\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y << "\t" << dcname << "\t" << fcname << endl;
}