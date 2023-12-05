#include "CSquare.h"

CSquare::CSquare(Point C, GfxInfo FigureGfxInfo, int l):CFigure(FigureGfxInfo)
{
	center = C;

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

void CSquare::Draw(Output* pOut) const
{ 
	pOut->DrawSquare(center, L, FigGfxInfo, Selected);
}

bool CSquare::CheckSelection(int x, int y)
{
	return (x >= center.x - L && x <= center.x + L && y >= center.y - L && y <= center.y + L);
}

void CSquare::Save(ofstream& OutFile)
{
	OutFile << "SQUARE" << "\t" << ID << "\t" << center.x << "\t" << center.y << "\t"  << L << "\t" << endl;

}
