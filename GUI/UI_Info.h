#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu
{
	//Note: Items are **(ordered)** here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_RECT,		//Recangle item in menu
	ITM_SQUARE, //Square item in menu
	ITM_TRIANGLE, //Triangle item in menu
	ITM_HEXA, //Hexafon item in menu
	ITM_CIRC, //Circle item in menu
	ITM_SELECT, //Select item in menu
	ITM_COLORS, //Colors
	ITM_FILL_COLOR, // Fill color
	ITM_OUTLINE_COLOR, // Outline color
	ITM_MOVE, //Move item in menu
	ITM_DELETE, //Delete item in menu
	ITM_UNDO, //Undo item in menu
	ITM_REDO, //Redo item in menu
	ITM_CLEARALL, //Clear item in menu
	ITM_SAVEGRAPH, //Save graph item in menu
	ITM_LOADGRAPH, //Load graph item in menu
	ITM_RECORDING, //Recording item in menu
	ITM_PLAYRECORDING, //Play recording item in menu
	ITM_PAUSERECORING, //Pause recording item in menu
	ITM_PLAYMODE, //Play mode item in menu
	ITM_EXIT,		//Exit item

	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};

enum PlayMenuItem //The items of the Play menu
{
	//Note: Items are **(ordered)** here as they appear in menu
	//If you want to change the menu items order, change the order here

	PLAY_ITM_BYTYPE, //Pick item by type in menu
	PLAY_ITM_BYCOLOR, //Pick item by color in menu
	PLAY_ITM_BYBOTH, //Draw Picking an item by both of type and color in menu
	PLAY_ITM_DRAWMODE, //Draw mode item in menu
	PLAY_ITM_EXIT,		//Exit item
	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};


__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;

	int	width, height,	    //Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth,
		MenuItemHeight;		//Width of each item in toolbar menu

	int IconsPadding;

	color DefaultDrawColor;	//Default drawing color
	color DefaultFillColor;	//Default filling color
	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	color ToolBarColor;
	int PenWidth;			//width of the pen that draws shapes

	// Colors
	int c_rows;
	int c_cols;
	string* drawColors; // Colors Labels
	color* drawColorsEq; // Equivalent Colors
	int colorIconSize;

	// Icon Labels
	string *DrawMenuLabels;
	string *PlayMenuLabels;
	// Saved Graphs DIr
	string graphsDir;
	string graphsFile; // To keep track of saved files


}UI;	//create a global object UI

#endif
