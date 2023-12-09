#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
	int screenWidth;
	int screenHeight;
	int selectedColor=-1;
public:
	Output();

	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateDrawToolBar() const;
	void DrawCenteredText(string msg, int x, int y, int width, int height, color Color) const;
	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar

	Input* CreateInput() const; //creates a pointer to the Input object
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area

	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected=false) const;
    void DrawSquare(Point P1, int L, GfxInfo RectGfxInfo, bool selected = false) const;//Draw a Square
	void DrawTriangle(Point P1, Point P2,Point p3 ,GfxInfo RectGfxInfo, bool selected = false) const; // Draw Triangle
	void DrawCirc(Point P1, int radius, GfxInfo RectGfxInfo, bool selected = false) const;//Draw a circle
	
	void DrawHexagon(Point P1, int L, GfxInfo RectGfxInfo, bool selected = false) const;
	///Make similar functions for drawing all other figure types.
	void PrintMessage(string msg) const;	//Print a message on Status bar
	int GetSelectedColor() const;
	void SetSelectedColor(int i);
	static string GetColorName(color c);
	static color GetColorFromName(string cname);
	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width


	~Output();
};

#endif
