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
	bool deleted;  //Checking whether the figure is deleted or not
	int deletedID;
	string Type; // type of figure
	static int Previous_ID; // for all figures to have a unique ID
public:

	CFigure(GfxInfo FigureGfxInfo);

	virtual void ResizeByDragging(Point& P0,Point& P1) = 0;
	static void ResetIDs();

	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	virtual Point GetFigureCenter() = 0;
	bool GetFilledStatus();
	void SetFilledStatus(bool status);
	virtual bool CheckSelection(int x, int y) = 0;
	virtual void Draw(Output* pOut) const = 0 ;		//Draw the figure
	virtual void Move(Point Pm) = 0;
	int GetDeletedID();
	void SetDeletedID(int i);

	int GetID();
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color

	color GetDrawColor() const;		//returns the figure's border color
	color GetFillColor() const;		//returns the figure's filling color

	bool isDeleted();     //Checks whether the figure is deleted or not 
	void SetDelete(bool delete1);   //Delete or undelete the figure

	string GetType() const; // returns the type of the figure
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure/// 
	void showFigure(bool PermissionToBeDrawn);
	bool isFigureShown() const;
	///Decide the parameters that you should pass to each function	

	virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
	bool operator==(CFigure& fig); // checks if two figures are equal

};



#endif