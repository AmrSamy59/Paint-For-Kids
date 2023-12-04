#include "CSquare.h"

CSquare::CSquare(Point C, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	center = C;

}

void CSquare::Draw(Output* pOut) const
{ 
	pOut->DrawSquare(center, FigGfxInfo, Selected);
}

bool CSquare::CheckSelection(int x, int y)
{
	int half_lengthof_square = 100;
	if (x >= center.x- half_lengthof_square && x <= center.x+ half_lengthof_square && y >= center.y- half_lengthof_square && y <= center.y+ half_lengthof_square)
	{
		return true;
	}
	else
	return false;
}

void CSquare::Save(ofstream& OutFile)
{
	OutFile << "SQUARE" << "\t" << ID << "\t" << center.x << "\t" << center.y << "\t"  << endl;



}
