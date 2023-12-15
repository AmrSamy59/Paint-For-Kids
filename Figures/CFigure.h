#ifndef CFIGURE_H
#define CFIGURE_H

#include <fstream>
#include "..\defs.h"
#include "..\GUI\Output.h"


//Base class for all figures all figures inhert from it
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	/// Add more parameters if needed.
	bool AbleToBeDrawn; // true if the figure is able to be drawn on interface update
	string Type; // type of figure
public:

	CFigure(GfxInfo FigureGfxInfo);

	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	virtual bool CheckSelection(int x, int y) = 0;
	virtual void Draw(Output* pOut) const = 0 ;		//Draw the figure
	virtual void Move(Output* pOut, Point Pm) = 0;
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color

	const color* GetFillColor() const;		//returns the figure's filling color

	string GetType() const; // returns the type of the figure
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure/// 
	void SetFigureAbilityToBeDrawn(bool PermissionToBeDrawn);
	bool GetFigureAbilityToBeDrawn() const;
	///Decide the parameters that you should pass to each function	

	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	//virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};

#endif