#include "Input.h"
#include "Output.h"

Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

clicktype Input::GetPointClicked(int &x, int &y) const
{
	pWind->FlushMouseQueue(); //To fix an error where it reads cached mouse-presses
	return pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

buttonstate Input::GetButtonState(button button_spec, int &x, int &y) {
	return pWind->GetButtonState(button_spec, x, y);
}

clicktype Input::GetPointForDrawing(int& x, int& y, Output * pO) const
{
	int toolBarH = UI.ToolBarHeight;
	clicktype bState = GetPointClicked(x, y);

	while (y <= toolBarH || y >= (UI.height-UI.StatusBarHeight)) {
		if (pO)
			pO->PrintMessage("You can't draw on the toolbar/statusbar, Please pick a different point.");
		bState = GetPointClicked(x, y);
	}
	if(pO)
		pO->PrintMessage("Point Picked, Pick Another point (if any).");
	return bState;
}

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	bool firstPress = false; // to handle escape & enter presses before beginning the test
	
	pWind->FlushKeyQueue(); //To fix an error where it reads cached key-presses
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 && firstPress)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 && firstPress)	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else if(Key != 8 && Key != 27 && Key != 13)
		{
			Label += Key;
			firstPress = true;
		}

		if (pO && firstPress)
			pO->PrintMessage("You're entering: "+Label+", Press Enter to finish, Press ESC to cancel.");
	}
}

//This function reads the position where the user clicks to determine the desired action

ActionType Input::GetUserAction() const
{	
	int x,y;
	clicktype cType = pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	if (cType == RIGHT_CLICK)
		return OPERATION_CANCELED;

	if(UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int paddingAfterColors = UI.IconsPadding + UI.colorIconSize * (UI.c_cols - 2);
			int ClickedItemOrder = ((x - UI.IconsPadding) / (UI.MenuItemWidth));
			if (ClickedItemOrder > ITM_COLORS) // to deal with spacing after colors icons
				ClickedItemOrder = ((x - paddingAfterColors) / (UI.MenuItemWidth));
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			if (ClickedItemOrder == ITM_COLORS) {
				int color = 0;
				int row = y / UI.colorIconSize; // 2 rows / 25 px (color height)
				int column = (x - UI.IconsPadding - (UI.MenuItemWidth) * ITM_COLORS) / UI.colorIconSize; // 3 columns / 25 px (color width)
				color = row * UI.c_cols + column;
				return ActionType(DRAW_COLOR_0 + color);

			}
			switch (ClickedItemOrder)
			{
			case ITM_RECT:			return DRAW_RECT;
			case ITM_SQUARE:		return DRAW_SQUARE;
			case ITM_TRIANGLE:		return DRAW_TRIANGLE;
			case ITM_HEXA :			return DRAW_HEXAGON;
			case ITM_CIRC:			return DRAW_CIRC;
			case ITM_SELECT:		return DRAW_SELECT;
			case ITM_FILL_COLOR:	return DRAW_CHNG_FILL_COLOR;
			case ITM_OUTLINE_COLOR:	return DRAW_CHNG_OUTLINE_COLOR;
			case ITM_MOVE:			return DRAW_MOVE;
			case ITM_DELETE:		return DRAW_DELETE;
			case ITM_UNDO:			return DRAW_UNDO;
			case ITM_REDO:			return DRAW_REDO;
			case ITM_CLEARALL:		return DRAW_CLEARALL;
			case ITM_SAVEGRAPH:		return DRAW_SAVEGRAPH;
			case ITM_LOADGRAPH:		return DRAW_LOADGRAPH;
			case ITM_RECORDING:		return DRAW_RECORDING;
			case ITM_PLAYRECORDING:	return DRAW_PLAYRECORDING;
			case ITM_PAUSERECORING:	return DRAW_PAUSERECORING;
			case ITM_PLAYMODE:		return TO_PLAY;
			case ITM_EXIT:			return EXIT;	
			default:				return EMPTY_DRAW_TOOLBAR;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = ((x - 10) / (UI.MenuItemWidth));
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			
			switch (ClickedItemOrder)
			{
			case PLAY_ITM_BYTYPE:      return PLAYMODE_BYTYPE;
			case PLAY_ITM_BYCOLOR:     return PLAYMODE_BYCOLOR;
			case PLAY_ITM_BYBOTH:      return PLAYMODE_BYBOTH;
			case PLAY_ITM_DRAWMODE:    return TO_DRAW;
			case PLAY_ITM_EXIT:		   return EXIT;
			default: return EMPTY_PLAY_TOOLBAR;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return PLAYING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}	

}
/////////////////////////////////
	
Input::~Input()
{
}
