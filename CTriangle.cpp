#include "CTriangle.h"


CTriangle::CTriangle(Point p1, Point p2, Point p3, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	c1 = p1;
	c2 = p2;
	c3 = p3;
}

void CTriangle::Draw(Output* pOut) const
{
	pOut->DrawTriangle(c1, c2, c3, FigGfxInfo, Selected);
}

bool CTriangle::CheckSelection(int x, int y)
{
	bool selected=false;

	Point v[3] = { c1, c2, c3 };

	int count = 0;

	double slope = (double(c2.y) - double(c1.y)) / (double(c2.x) - double(c1.x));
	double slope2 = (double(c2.y) - double(c3.y)) / (double(c2.x) - double(c3.x));
	double slope3 = (double(c1.y) - double(c3.y)) / (double(c1.x) - double(c3.x));

	// x = ((y-y1)/slope) + X1;

	int _x = ((double(y) - double(c2.y)) / slope) + double(c2.x);
	int _x2 = ((double(y) - double(c2.y)) / slope2) + double(c2.x);
	int _x3 = ((double(y) - double(c1.y)) / slope3) + double(c1.x);

	int xmin = c1.x;
	int xmax = c1.x;
	int ymin = c1.y;
	int ymax = c1.y;

	for (int i = 0; i < 3; i++)
	{
		if (v[i].x <= xmin)
			xmin = v[i].x;
		if (v[i].x >= xmax)
			xmax = v[i].x;

		if (v[i].y <= ymin)
			ymin = v[i].y;
		if (v[i].y >= ymax)
			ymax = v[i].y;
	}

	if (_x >= x && _x <= xmax && _x >= xmin)
		count++;
	if (_x2 >= x && _x2 <= xmax && _x2 >= xmin)
		count++;

	if (_x3 >= x && _x3 <= xmax && _x3 >= xmin)
		count++;

	if (y >= xmin && y <= xmax && y >= ymin && y <= ymax)
		selected = true;


	return selected && count % 2 != 0;

}

void CTriangle::Save(ofstream& OutFile)
{
	OutFile << "Triangle" << "\t" << ID << "\t" << c1.x << "\t" << c1.y << "\t" << c2.x << "\t" << c2.y << "\t" << c3.x << "\t" << c3.y  << endl;

}
