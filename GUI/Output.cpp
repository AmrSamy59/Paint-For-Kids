#include "Output.h"


Output::Output()
{

	// get window size
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	screenWidth = desktop.right;
	screenHeight = desktop.bottom;

	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = int(screenWidth * 0.85); // make the size of the window 3/4 of the entire screen
	UI.height = int(screenHeight * 0.75);

	UI.width = UI.width < (DRAW_ITM_COUNT * UI.MenuItemWidth) ?
		DRAW_ITM_COUNT * (UI.MenuItemWidth + 2) : UI.width; // For smaller screens


	UI.wx = (screenWidth / 2) - (UI.width / 2);
	UI.wy = (screenHeight / 2) - (UI.height / 2);


	UI.StatusBarHeight = 40;

	UI.MenuItemWidth = 50;
	UI.MenuItemHeight = UI.MenuItemWidth; // 50x50 Icons
	UI.ToolBarHeight = UI.MenuItemHeight + 14; // 14px offset for labels (12px font height + 2px padding)

	UI.DefaultDrawColor = BLUE;
	UI.DrawColor = UI.DefaultDrawColor;	//Drawing color

	UI.MsgColor = WHITE;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = color(53, 47, 68);

	UI.ToolBarColor = UI.StatusBarColor;
	UI.DefaultFillColor = UI.ToolBarColor;	//Filling color
	UI.FillColor = UI.DefaultFillColor;	//Filling color

	UI.PenWidth = 2;	//width of the figures frames

	UI.IconsPadding = 10; // px
	// Colors 
	UI.c_rows = 2; // number of rows
	UI.c_cols = 4; // number of columns
	UI.drawColors = { new string[UI.c_rows * UI.c_cols] { "Red", "Green", "Blue", "Purple", "Orange", "Yellow", "Black", "Transparent"}};
	UI.drawColorsEq = { new color[UI.c_rows * UI.c_cols] { RED, DARKGREEN, DEEPSKYBLUE, PURPLE, ORANGE, YELLOW, BLACK, UI.DefaultFillColor } };

	UI.colorIconSize = 25; // px
	
	// Labels
	UI.DrawMenuLabels = { new string[DRAW_ITM_COUNT]{
	"Rectangle", "Square", "Triangle", "Hexagon", "Circle",
	"Select", "Colors", "Fill", "Outline", "Move", 
	"Delete", "Undo", "Redo", "Clear All", "Save", 
	"Load", "Record", "Play", "Pause", "Play Mode", "Sound","Exit"
	}};
	UI.PlayMenuLabels = { new string[PLAY_ITM_COUNT]{
		"By Type", "By Color", "By Both", "Draw Mode", "Exit"
	} };

	UI.SoundEnabled = true;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

void Output::ResizeByDraggingOutput(Point& P1)
{
		button mouse_button = LEFT_BUTTON;
		/*while (1)
		{
			if (pWind->GetButtonState(mouse_button, P1.x, P1.y) == BUTTON_DOWN)
				break;
		}*/
		/*while (pWind->GetButtonState(mouse_button, P.x, P.y) == BUTTON_UP)
		{
			pWind->GetMouseCoord(P.x, P.y);
			if (P.y < UI.ToolBarHeight)
				return NULL;
		}*/
		while (pWind->GetButtonState(mouse_button, P1.x, P1.y) == BUTTON_UP);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	int color_icon_size = UI.colorIconSize;
	string imagesPath = "images\\MenuItems\\";

	// Drawing toolbar icons
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "Menu_Rect.jpg";
	MenuItemImages[ITM_SQUARE] = "Menu_Sqaure.jpg";
	MenuItemImages[ITM_TRIANGLE] = "Menu_Triangle.jpg";
	MenuItemImages[ITM_CIRC] = "Menu_Circ.jpg";
	MenuItemImages[ITM_HEXA] = "Menu_Hexagon.jpg";
	MenuItemImages[ITM_SELECT] = "Menu_Select.jpg";

	MenuItemImages[ITM_COLORS] = imagesPath; // special case

	MenuItemImages[ITM_FILL_COLOR] = "Menu_Fill.jpg";
	MenuItemImages[ITM_OUTLINE_COLOR] = "Menu_Outline.jpg";
	MenuItemImages[ITM_MOVE]= "Menu_Move.jpg";
	MenuItemImages[ITM_DELETE] = "Menu_Deleteitem.jpg";
	MenuItemImages[ITM_UNDO] = "Menu_Undo.jpg";
	MenuItemImages[ITM_REDO] = "Menu_Redo.jpg";
	MenuItemImages[ITM_CLEARALL] = "Menu_Clearall.jpg";
	MenuItemImages[ITM_SAVEGRAPH] = "Menu_Savegraph.jpg";
	MenuItemImages[ITM_LOADGRAPH] = "Menu_Loadgraph.jpg";
	MenuItemImages[ITM_RECORDING]= "Menu_Recording.jpg";
	MenuItemImages[ITM_PLAYRECORDING] = "Menu_Playrecording.jpg";
	MenuItemImages[ITM_PAUSERECORING] = "Menu_Pauserecording.jpg";
	
	MenuItemImages[ITM_SOUND] = UI.SoundEnabled ? "Sound_Enabled.jpg" : "Sound_Disabled.jpg";
	MenuItemImages[ITM_PLAYMODE] = "Menu_PlayMode.jpg";



	
	MenuItemImages[ITM_EXIT] = "Menu_Exit.jpg";


	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	//Draw menu item one image at a time
	pWind->SetPen(UI.ToolBarColor, 0);

	int paddingAfterColors = UI.IconsPadding + UI.colorIconSize*(UI.c_cols-2);
	for (int i = 0; i < DRAW_ITM_COUNT; i++) {
		int ix, iy;
		if (i == ITM_COLORS) {
			for (int row = 0; row < UI.c_rows; row++) {
				for (int c = 0; c < UI.c_cols; c++) {
					ix = i * UI.MenuItemWidth + UI.IconsPadding + color_icon_size * c;
					iy = color_icon_size * row;
					pWind->DrawImage(MenuItemImages[i] + UI.drawColors[c + row * UI.c_cols] + ".jpg", ix, iy, color_icon_size, color_icon_size);
				}
			}
			ix = i * UI.MenuItemWidth + UI.IconsPadding;
			DrawCenteredText(UI.DrawMenuLabels[i], ix, UI.MenuItemHeight, UI.colorIconSize*UI.c_cols, UI.ToolBarHeight - UI.MenuItemHeight - 2, UI.BkGrndColor);
		}
		else {
			ix = i * UI.MenuItemWidth + (i > ITM_COLORS ? paddingAfterColors : UI.IconsPadding);
			iy = 0;
			pWind->DrawImage(imagesPath + MenuItemImages[i], ix, iy, UI.MenuItemWidth, UI.MenuItemHeight);
			DrawCenteredText(UI.DrawMenuLabels[i], ix, UI.MenuItemHeight, UI.MenuItemWidth, UI.ToolBarHeight - UI.MenuItemHeight - 2, UI.BkGrndColor);
		}
		if (i == ITM_FILL_COLOR) { //Outline the icon with the current fill color
			pWind->SetPen(UI.FillColor, 2);
			pWind->DrawRectangle(ix+1, iy+2, ix + UI.MenuItemWidth, UI.ToolBarHeight - 2, FRAME, 10, 10);
		}
		else if (i == ITM_OUTLINE_COLOR) { //Outline the icon with the current draw color
			pWind->SetPen(UI.DrawColor, 2);
			pWind->DrawRectangle(ix, iy+2, ix + UI.MenuItemWidth - 1, UI.ToolBarHeight - 2, FRAME, 10, 10);

		}
	}



	//Draw a line under the toolbar
	pWind->SetPen(color(92, 84, 112), 1);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;

	typedef enum {
		PICK,

		HIDE,

		NUMBER_OF_ITEMS
	}PLAY_MODE_ITEMS;

	string imagesPath = "images\\MenuItems_Play\\";
	string MenuItemImages[PLAY_ITM_COUNT];

	MenuItemImages[PLAY_ITM_BYCOLOR] = "Menu_ByColor.jpg";
	MenuItemImages[PLAY_ITM_BYTYPE] = "Menu_ByType.jpg";
	MenuItemImages[PLAY_ITM_BYBOTH] = "Menu_ByBoth.jpg";
	MenuItemImages[PLAY_ITM_DRAWMODE] = "Menu_DrawMode.jpg";

	MenuItemImages[PLAY_ITM_EXIT] = "Menu_Exit.jpg";

	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

	//Draw menu item one image at a time
	pWind->SetPen(UI.ToolBarColor, 0);


	for (int i = 0; i < PLAY_ITM_COUNT; i++) {
		int ix = i * UI.MenuItemWidth + UI.IconsPadding;
		pWind->DrawImage(imagesPath+MenuItemImages[i], ix, 0, UI.MenuItemWidth, UI.MenuItemHeight);
		DrawCenteredText(UI.PlayMenuLabels[i], ix, UI.MenuItemHeight, UI.MenuItemWidth, UI.ToolBarHeight - UI.MenuItemHeight - 2, UI.BkGrndColor);
	}

	//Draw a line under the toolbar
	pWind->SetPen(color(92, 84, 112), 1);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

void Output::DrawCenteredText(string msg, int x, int y, int width, int height, color Color) const {
	int tw, th; // Text Width, Height
	pWind->SetPen(Color, height);
	pWind->SetFont(height, BOLD, BY_NAME, "Arial"); // Keep that default font
	pWind->GetStringSize(tw, th, msg);
	pWind->DrawString(x + (width / 2) - (tw / 2), y + (height / 2) - (th / 2), msg); // Center the text
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight - 5), msg);
}
int Output::GetSelectedColor() const
{
	return selectedColor;
}
void Output::SetSelectedColor(int i)
{
	selectedColor = i;
}
string Output::GetColorName(color c) {
	for (int i = 0; i < UI.c_cols * UI.c_rows; i++) {
		if (c == UI.drawColorsEq[i])
			return UI.drawColors[i];
	}
	return UI.drawColors[UI.c_cols * UI.c_rows - 1];
}
color Output::GetColorFromName(string cname) {
	if(cname == "DEFAULT_DRAW_CLR")
		return UI.DefaultDrawColor;
	for (int i = 0; i < UI.c_cols * UI.c_rows; i++) {
		if (cname == UI.drawColors[i])
			return UI.drawColorsEq[i];
	}
	return UI.drawColorsEq[UI.c_cols * UI.c_rows -1];
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if(selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, UI.PenWidth);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}
///////////////////////////

void Output::DrawSquare(Point P1, int L, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, UI.PenWidth);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x-L,P1.y+L,P1.x+L,P1.y-L, style);
}


void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, UI.PenWidth);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;
	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}

void Output::DrawCirc(Point P1, int radius, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, UI.PenWidth);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;
	
	

	pWind->DrawCircle(P1.x, P1.y, radius, style);
}

void Output::DrawHexagon(Point P1, int L, GfxInfo HexaGfxInfo, bool selected) const
{
	color DrawingClr;

	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = HexaGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, UI.PenWidth);
	drawstyle style;
	if (HexaGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexaGfxInfo.FillClr);
	}
	else
		style = FRAME;

	Point PH[6]; // Hexagon vertices points

	PH[0].x = P1.x;
	PH[0].y = P1.y + L;
	PH[1].x = P1.x - L;
	PH[1].y = P1.y + (L / 2);
	PH[2].x = P1.x - L;
	PH[2].y = P1.y - (L / 2);
	PH[3].x = P1.x;
	PH[3].y = P1.y - L;
	PH[4].x = P1.x + L;
	PH[4].y = P1.y - (L / 2);
	PH[5].x = P1.x + L;
	PH[5].y = P1.y + (L / 2);


	int ix[6];
	int iy[6];
	for (int i = 0; i < 6; i++)
	{
		ix[i] = PH[i].x;
	}
	for (int i = 0; i < 6; i++)
	{
		iy[i] = PH[i].y;
	}

	pWind->DrawPolygon(ix, iy, 6, style);
}


//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
	delete[] UI.drawColors;
	delete[] UI.drawColorsEq;
	delete[] UI.DrawMenuLabels;
	delete[] UI.PlayMenuLabels;
}

