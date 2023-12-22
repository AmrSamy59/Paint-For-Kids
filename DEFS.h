#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported
{
	DRAW_RECT,		//Draw Rectangle Icon
	DRAW_SQUARE,	//Draw Square Icon
	DRAW_TRIANGLE,	//Draw Triangle Icon
	DRAW_HEXAGON,   //Draw Hexagon Icon
	DRAW_CIRC,      //DRAW Circle Icon
	DRAW_SELECT,	//Draw Select Icon
	DRAW_COLOR_0,	
	DRAW_COLOR_1,	
	DRAW_COLOR_2,
	DRAW_COLOR_3,
	DRAW_COLOR_4,
	DRAW_COLOR_5,
	DRAW_COLOR_6,
	DRAW_COLOR_7,
	DRAW_FILL_COLOR, // Draw fill color icon
	DRAW_OUTLINE_COLOR, // Draw outline color icon
	DRAW_MOVE,	//Draw Move Icon
	DRAW_DELETE,	//Draw Delete Icon
	DRAW_UNDO,	//Draw Undo Icon
	DRAW_REDO,	//Draw Redo Icon
	DRAW_CLEARALL,	//Draw Clearall Icon
	DRAW_SAVEGRAPH,	//Draw Save grapgh Icon
	DRAW_LOADGRAPH,	//Draw Load grapgh Icon
	DRAW_RECORDING,	//Draw Recording Icon
	DRAW_PLAYRECORDING,	//Draw Play recording Icon
	DRAW_PAUSERECORING,	//Draw Pause recording Icon
	EXIT,			//Exit
	TO_DRAW,		//Switch interface to Draw mode
	DRAW_ITM_BYTYPE, //Draw Picking an item by type Icon
	DRAW_ITM_BYCOLOR, //Draw Picking an item by color Icon
	DRAW_ITM_BYBOTH, //Draw Picking an item by both of type and color Icon
	DRAW_ITM_DRAWMODE, //Draw Draw Mode Icon
	TO_PLAY,		//Switch interface to Play mode
	EMPTY_DRAW_TOOLBAR,	//A click on empty place in the draw toolbar
	EMPTY_PLAY_TOOLBAR,//A click on empty place in the play toolbar
	DRAWING_AREA,	//A click on the drawing area
	PLAYING_AREA, //A click on the playing area
	STATUS,			//A click on the status bar

	OPERATION_CANCELED,		//operation canceled event
};

struct Point	//To be used for figures points
{ int x,y; };

struct GfxInfo	//Graphical info of each figure
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif