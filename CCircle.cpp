#include "CCircle.h"
#include <cmath>
CCircle::CCircle(Point P1, int r, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	point1 = P1;

	radius = r;

	int toolBarH = UI.ToolBarHeight + 3;
	int statusBarH = UI.height - UI.StatusBarHeight - 3;

	if (abs(P1.y - toolBarH) < radius) {
		radius = abs(P1.y - toolBarH);
	}
	if (abs(statusBarH - P1.y) < radius) {
		radius = abs(statusBarH - P1.y);
	}
}

void CCircle::Draw(Output* pOut) const
{
	pOut->DrawCirc(point1, radius, FigGfxInfo, Selected);
}

bool CCircle::CheckSelection(int x, int y)
{ // point 1 is the center of circle

	return (sqrt(pow((x- point1.x), 2)+pow((y - point1.y), 2)) <= radius);
}

void CCircle::Save(ofstream& OutFile)
{
	OutFile << "CIRCLE" << "\t" << ID << "\t" << point1.x << "\t" << point1.y << "\t" << radius << "\t" << endl;
}
