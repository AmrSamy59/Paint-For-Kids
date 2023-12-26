#include "CCircle.h"
#include <cmath>

int CCircle::Count = 0;
CCircle::CCircle(Point P1, int r, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Type = "circle";
	pointForResizing.x = 0;
	pointForResizing.y = 0;

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
	CCircle::Count++;
}

void CCircle::ResizeByDragging(Point& P0, Point& P1)
{
	Point PCircle = GetFigureCenter();
	int DifferenceX = (P1.x - PCircle.x);
	int DifferenceY = (P1.y - PCircle.y);
	radius = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
}

Point CCircle::GetFigureCenter()
{
	return point1;
}

void CCircle::Draw(Output* pOut) const
{
	pOut->DrawCirc(point1, radius, FigGfxInfo, Selected);
}

void CCircle::Move(Point Pm)
{
	if (Pm.y + radius > (UI.height - UI.StatusBarHeight))
	{
		Pm.y = UI.height - UI.StatusBarHeight - radius - 1;
	}
	if (Pm.y - radius < (UI.ToolBarHeight))
	{
		Pm.y = UI.ToolBarHeight + radius + 1;
	}
	if (Pm.x - radius < 0)
	{
		Pm.x = radius + 1;
	}
	if (Pm.x + radius > (UI.width))
	{
		Pm.x = UI.width - radius - 1;
	}
	point1 = Pm;
}

bool CCircle::CheckSelection(int x, int y)
{ // point 1 is the center of circle

	return (sqrt(pow((x- point1.x), 2)+pow((y - point1.y), 2)) <= radius);
}

void CCircle::Save(ofstream& OutFile)
{
	string fcname =  Output::GetColorName(FigGfxInfo.FillClr); // Fill color
	string dcname = Output::GetColorName(FigGfxInfo.DrawClr); // Draw color
	
	OutFile << "CIRCLE" << "\t" << ID << "\t" << point1.x << "\t" << point1.y << "\t" << radius << "\t" << dcname << "\t" << fcname << endl;
}

/*CCircle* CCircle::SaveCopyOfFigure()
{
	CCircle* x = new CCircle(*this);
	return x;

}
*/

void CCircle::DecreaseCount() {

	Count--;

}

void CCircle::IncreaseCount()
{
	Count++;
}

int CCircle::GetCount()
{
	return CCircle::Count;
}

void CCircle::PrintInfo(Output* pOut) {
	string s = "Circle ID: " + to_string(ID) + ", Fill Color: " + pOut->GetColorName(FigGfxInfo.FillClr) + ", Draw Color: " + pOut->GetColorName(FigGfxInfo.DrawClr) + ", Radius: " + to_string(radius);
	pOut->PrintMessage(s);
}

CCircle::~CCircle()
{
	//CCircle::Count--;
}
