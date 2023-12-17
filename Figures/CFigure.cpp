#include "CFigure.h"
#include <iostream>

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ //constractor
	static int Previous_ID = 0; // for all class
	ID = Previous_ID++;
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	AbleToBeDrawn = true;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const   // get function for selection
{	return Selected; }
color CFigure::GetLastFigBorderColor()
{
	return FigGfxInfo.DrawClr;
}
color CFigure::GetLastFigFilledColor()
{
	return FigGfxInfo.FillClr;
}
void CFigure::ChngDrawClr(color Dclr) // oulinr color
{	FigGfxInfo.DrawClr = Dclr; }
bool CFigure::GetFilledStatus()
{
	return FigGfxInfo.isFilled;
}
void CFigure::SetFilledStatus(bool status)
{
	FigGfxInfo.isFilled = status;
}
void CFigure::ChngFillClr(color Fclr) /// fill color
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}
bool CFigure::GetFigureAbilityToBeDrawn() const
{
	return AbleToBeDrawn;
}
void CFigure::SetFigureAbilityToBeDrawn(bool PermissionToBeDrawn)
{
	AbleToBeDrawn = PermissionToBeDrawn;
}
