#include "CCircle.h"
#include <cmath>
CCircle::CCircle(Point p1, Point p2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	point1 = p1;
	point2 = p2;
}

void CCircle::Draw(Output* pOut) const
{
	pOut->DrawCirc(point1, point2, FigGfxInfo, Selected);
}

bool CCircle::CheckSelection(int x, int y)
{ // point 1 is the center of circle

	bool xselected = false, yselected = false;
	int radius = int(sqrt(double((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y))));
	int xmin = point1.x - radius;
	int xmax= point1.x + radius;
	 int ymin= point1.y - radius;
	 int ymax= point1.y + radius;
	 if ((x >= xmin && x <= xmax) )
		 xselected = true;
	 if ((y >= ymin && y <= ymax) )
		 yselected = true;
	 if (xselected == true && yselected == true)
		 return true;
	 else
		 return false;
}

void CCircle::Save(ofstream& OutFile)
{
	OutFile << "" << "\t" << ID << "\t" << point1.x << "\t" << point1.y << "\t" << point2.x << "\t" << point2.y << "\t" << endl;
}
