#include "CFigure.h"

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ //constractor
	static int Previous_ID = 0; // for all class
	ID = Previous_ID++;
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const   // get function for selection
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr) // oulinr color
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr) /// fill color
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}


