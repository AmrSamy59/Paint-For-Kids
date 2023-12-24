#include "CFigure.h"
#include <iostream>

CFigure::CFigure(GfxInfo FigureGfxInfo, bool zeroID)
{ //constractor
	static int Previous_ID = 0; // for all class
	deleted = false;
	if (zeroID)
	{
		Previous_ID = 0;
	}
	ID = Previous_ID++;
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	AbleToBeDrawn = true;
	deletedID = 0;
}
void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const   // get function for selection
{	return Selected; }
color CFigure::GetDrawColor() const
{
	return FigGfxInfo.DrawClr;
}

int CFigure::GetDeletedID()
{
	return deletedID;
}

void CFigure::SetDeletedID(int i)
{
	deletedID = i;
}
int CFigure::GetID()
{
	return ID;
}

void CFigure::ChngDrawClr(color Dclr) // oulinr color
{	
	if (Dclr == UI.DefaultFillColor) {
		FigGfxInfo.DrawClr = UI.DefaultDrawColor;
		return;
	}
	FigGfxInfo.DrawClr = Dclr; 
}
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
	if (Fclr == UI.DefaultFillColor) {
		FigGfxInfo.isFilled = false;
	}
	FigGfxInfo.FillClr = Fclr; 
}
color CFigure::GetFillColor() const
{
	return FigGfxInfo.FillClr;
}
string CFigure::GetType() const
{
	return Type;
}
bool CFigure::isFigureShown() const
{
	return AbleToBeDrawn;
}

bool CFigure::CheckDelete()
{
	return deleted;
}

void CFigure::SetDelete(bool delete1)
{
	deleted = delete1;
}


void CFigure::showFigure(bool PermissionToBeDrawn)
{
	AbleToBeDrawn = PermissionToBeDrawn;
}
