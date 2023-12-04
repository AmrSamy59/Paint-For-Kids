#include "CHexagon.h"
#include<cmath>
CHexagon::CHexagon(Point c, GfxInfo FigureGfxInfo, int l):CFigure(FigureGfxInfo)
{
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
}

void CHexagon::Draw(Output* pOut) const
{
	pOut->DrawHexagon(center, L, FigGfxInfo, Selected);
}

bool CHexagon::CheckSelection(int x, int y)
{
	bool selected = false;

	int xmin = center.x - L;
	int xmax = center.x + L;

	int ymin = center.y - L;
	int ymax = center.y + L;

	if (x >= xmin && x <= xmax && y >= ymin && y <= ymax)
		selected = true;

	//printf("min x: %d max x: %d min y: %d max y: %d\n", xmin, xmax, ymin, ymax);
	//printf("x: %d y: %d\n", x, y);
	return selected;
}

void CHexagon::Save(ofstream& OutFile)
{
	OutFile << "HEXAGON" << "\t" << ID << "\t" << center.x << "\t" << center.y << "\t" << L << "\t" << endl;
}
