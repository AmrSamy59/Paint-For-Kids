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
	bool xselected=false,yselected=false;
	////////////xselect//////////////
	int arrx[3] = { c1.x,c2.x,c3.x };
	
	int xmin = arrx[0];
	int xmax = arrx[0];
	for (int i = 0; i < 3; i++)
	{
		if (xmin > arrx[i])
			xmin = arrx[i];
		if (xmax < arrx[i])
			xmax = arrx[i];
	}
	if (x >= xmin && x <= xmax)
		xselected = true;
	///////////yselect /////////////
	int arry[3] = { c1.y,c2.y,c3.y };

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

void CTriangle::Save(ofstream& OutFile)
{
	OutFile << "Triangle" << "\t" << ID << "\t" << c1.x << "\t" << c1.y << "\t" << c2.x << "\t" << c2.y << "\t" << c3.x << "\t" << c3.y  << endl;

}
