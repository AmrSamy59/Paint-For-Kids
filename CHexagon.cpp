#include "CHexagon.h"
#include<cmath>
CHexagon::CHexagon(Point c, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	center = c;
}

void CHexagon::Draw(Output* pOut) const
{
	pOut->DrawHexagon(center, FigGfxInfo, Selected);
}

bool CHexagon::CheckSelection(int x, int y)
{
	bool xselected = false, yselected = false;
	int l = 100;
	int arrx[4]={center.x+l,center.x -l,center.x+(sqrt(3)/2)*l,center.x - (sqrt(3) / 2) * l } ;
	int arry[3] = { center.y,center.y + 0.5 * l,center.y - 0.5 * l };
	int xmin = arrx[0];
	int xmax = arrx[0];
	for (int i = 0; i < 4; i++)
	{
		if (xmin > arrx[i])
			xmin = arrx[i];
		if (xmax < arrx[i])
			xmax = arrx[i];
	}
	if (x >= xmin && x <= xmax)
		xselected = true;

	//////////////  y select /////////////////


	int ymin = arry[0];
	int ymax = arry[0];
	for (int i = 0; i < 3; i++)
	{
		if (ymin > arry[i])
			ymin = arry[i];
		if (ymax < arry[i])
			ymax = arry[i];
	}
	if (y >= ymin && y <= ymax)
		yselected = true;
	if (xselected == true && yselected == true)
		return true;
	else
		return false;


}

void CHexagon::Save(ofstream& OutFile)
{
	OutFile << "HEXAGON" << "\t" << ID << "\t" << center.x << "\t" << center.y << "\t"  << endl;
}
