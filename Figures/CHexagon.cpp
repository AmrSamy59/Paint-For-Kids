#include "CHexagon.h"
#include<cmath>

int CHexagon::Count = 0;
CHexagon::CHexagon(Point c, GfxInfo FigureGfxInfo,bool zeroID ,int l):CFigure(FigureGfxInfo, zeroID)
{
	Type = "hexagon";

	center = c;
	L = l;

	int toolBarH = UI.ToolBarHeight + 3;
	int statusBarH = UI.height - UI.StatusBarHeight - 3;

	if (abs(center.y - toolBarH) < L) {
		L = abs(center.y - toolBarH);
	}
	if (abs(statusBarH - center.y) < L) {
		L = abs(statusBarH - center.y);
	}

	CHexagon::Count++;
}

void CHexagon::ResizeByDragging(Point& P)
{

}

Point CHexagon::GetFigureCenter()
{
	return center;
}

void CHexagon::Draw(Output* pOut) const
{
	pOut->DrawHexagon(center, L, FigGfxInfo, Selected);
}

void CHexagon::Move(Point Pm)
{
	if (Pm.y + L > (UI.height - UI.StatusBarHeight))
	{
		Pm.y = UI.height - UI.StatusBarHeight - L - 1;
	}
	if (Pm.y - L < UI.ToolBarHeight)
	{
		Pm.y = UI.ToolBarHeight + L + 1;
	}
	if (Pm.x + L > UI.width)
	{
		Pm.x = UI.width - L - 1;
	}
	if (Pm.x - L < 0)
	{
		Pm.x = L + 1;
	}
	center = Pm;
}

bool CHexagon::CheckSelection(int x, int y)
{
	bool selected = false;

	Point PH[6]; // Hexagon vertices points

	PH[0].x = center.x;
	PH[0].y = center.y + L;
	PH[1].x = center.x - L;
	PH[1].y = center.y + (L / 2);
	PH[2].x = center.x - L;
	PH[2].y = center.y - (L / 2);
	PH[3].x = center.x;
	PH[3].y = center.y - L;
	PH[4].x = center.x + L;
	PH[4].y = center.y - (L / 2);
	PH[5].x = center.x + L;
	PH[5].y = center.y + (L / 2);

	int count = 0, count2 = 0;

	double slope = (double(PH[1].y) - double(PH[0].y)) / (double(PH[1].x) - double(PH[0].x));


	// x = ((y-y1)/slope) + X1;

	int _x = ((double(y) - double(PH[1].y)) / slope) + double(PH[1].x);
	int _x2 = ((double(y) - double(PH[5].y)) / -slope) + double(PH[5].x);
	int _x3 = ((double(y) - double(PH[4].y)) / slope) + double(PH[4].x);
	int _x4 = ((double(y) - double(PH[2].y)) / -slope) + double(PH[2].x);
	

	if (_x >= x)
		count++;
	if (_x2 >= x)
		count++;

	if (_x3 >= x)
		count2++;
	if (_x4 >= x)
		count2++;

	int xmin = center.x - L;
	int xmax = center.x + L;

	int ymin = center.y - L;
	int ymax = center.y + L;

	if (x >= xmin && x <= xmax && y >= ymin && y <= ymax)
		selected = true;

	return selected && count % 2 != 0 && count2 % 2 != 0;
}

void CHexagon::Save(ofstream& OutFile)
{
	string fcname = Output::GetColorName(FigGfxInfo.FillClr); // Fill color
	string dcname = Output::GetColorName(FigGfxInfo.DrawClr); // Draw color

	OutFile << "HEXAGON" << "\t" << ID << "\t" << center.x << "\t" << center.y << "\t" << L << "\t" << dcname << "\t" << fcname << endl;
}

void CHexagon::SetCount(int i)
{
	CHexagon::Count = i;
}


int CHexagon::GetCount()
{
	return CHexagon::Count;
}

CHexagon::~CHexagon()
{
	CHexagon::Count--;
}
