#include "CTriangle.h"

int CTriangle::Count = 0;
CTriangle::CTriangle(Point p1, Point p2, Point p3, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Type = "triangle";
	pointForResizing.x = 0;
	pointForResizing.y = 0;
	c1 = p1;
	c2 = p2;
	c3 = p3;
	cc1 = c1;
	cc2 = c2;
	cc3 = c3;
	CTriangle::Count++;
}

Point CTriangle::GetFigureCenter()
{
	Point Center;
	Center.x = (cc1.x + cc2.x + cc3.x) / 3;
	Center.y = (cc1.y + cc2.y + cc3.y) / 3;
	return Center;
}

void CTriangle::ResizeByDragging(Point& P1)
{
	if (P1.x < 0 || P1.y < 0 || P1.x > UI.width || P1.y > UI.height)
		return;


	Point Center = GetFigureCenter();

	int DifferenceX = abs(P1.x - Center.x);
	int DifferenceY = abs(P1.y - Center.y);
	
	int diff = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));

	if (c1.x > Center.x) {
		int diffx = cc1.x - Center.x;
		int diffy = cc1.y - Center.y;
		int l = sqrt((diffx * diffx) + (diffy * diffy));
		c1.x = cc1.x + abs(diff * ((diffx) / l));
	}
	else {
		int diffx = Center.x - cc1.x;
		int diffy = Center.y - cc1.y;
		int l = sqrt((diffx * diffx) + (diffy * diffy));
		c1.x = cc1.x - abs(diff * ((diffx) / l));
	}

	if (c2.x > Center.x) {
		int diffx = cc2.x - Center.x;
		int diffy = cc2.y - Center.y;
		int l = sqrt((diffx * diffx) + (diffy * diffy));
		c2.x = cc2.x + abs(diff * (float(diffx) / l));
	}
	else {
		int diffx = Center.x - cc2.x;
		int diffy = Center.y - cc2.y;
		int l = sqrt((diffx * diffx) + (diffy * diffy));
		c2.x = cc2.x - abs(diff * (float(diffx) / l));
	}

	if (c3.x > Center.x) {
		int diffx = cc3.x - Center.x;
		int diffy = cc3.y - Center.y;
		int l = sqrt((diffx * diffx) + (diffy * diffy));
		c3.x = cc3.x + abs(diff * (float(diffx) / l));
	}
	else {
		int diffx = Center.x - cc3.x;
		int diffy = Center.y - cc3.y;
		int l = sqrt((diffx * diffx) + (diffy * diffy));
		c3.x = cc3.x - abs(diff * (float(diffx) / l));
	}

	if (c1.y > Center.y) {
		int diffx = cc1.x - Center.x;
		int diffy = cc1.y - Center.y;
		int l = sqrt((diffx * diffx) + (diffy * diffy));
		c1.y = cc1.y + abs(diff * (float(diffy) / l));
	}
	else {
		int diffx = Center.x - cc1.x;
		int diffy = Center.y - cc1.y;
		int l = sqrt((diffx * diffx) + (diffy * diffy));
		c1.y = cc1.y - abs(diff * (float(diffy) / l));
	}

	if (c2.y > Center.y) {
		int diffx = cc2.x - Center.x;
		int diffy = cc2.y - Center.y;
		int l = sqrt((diffx * diffx) + (diffy * diffy));
		c2.y = cc2.y + abs(diff * (float(diffy) / l));
	}
	else {
		int diffx = Center.x - cc2.x;
		int diffy = Center.y - cc2.y;
		int l = sqrt((diffx * diffx) + (diffy * diffy));
		c2.y = cc2.y - abs(diff * (float(diffy) / l));
	}

	if (c3.y > Center.y) {
		int diffx = cc3.x - Center.x;
		int diffy = cc3.y - Center.y;
		int l = sqrt((diffx * diffx) + (diffy * diffy));
		c3.y = cc3.y + abs(diff * (float(diffy) / l));
	}
	else {
		int diffx = Center.x - cc3.x;
		int diffy = Center.y - cc3.y;
		int l = sqrt((diffx * diffx) + (diffy * diffy));
		c3.y = cc3.y - abs(diff * (float(diffy) / l));
	}
	

	RefineShape();

	//c1.x = c1.x + c1.x *;


	//pointForResizing.x = DifferenceX;
	//pointForResizing.y = DifferenceY;
}

void CTriangle::Draw(Output* pOut) const
{
	pOut->DrawTriangle(c1 + pointForResizing, c2 - pointForResizing, c3 + pointForResizing, FigGfxInfo, Selected);
}

void CTriangle::RefineShape()
{
	if(c1.x > UI.width)
		c1.x = UI.width - 1;
	if (c1.x < 0)
		c1.x = 1;
	if (c1.y > UI.height - UI.StatusBarHeight)
		c1.y = UI.height - UI.StatusBarHeight - 3;
	if (c1.y < UI.ToolBarHeight)
		c1.y = UI.ToolBarHeight + 3;

	if (c2.x > UI.width)
		c2.x = UI.width - 1;
	if (c2.x < 0)
		c2.x = 1;
	if (c2.y > UI.height - UI.StatusBarHeight)
		c2.y = UI.height - UI.StatusBarHeight - 3;
	if (c2.y < UI.ToolBarHeight)
		c2.y = UI.ToolBarHeight + 3;
	
	if (c3.x > UI.width)
		c3.x = UI.width - 1;
	if (c3.x < 0)
		c3.x = 1;
	if (c3.y > UI.height - UI.StatusBarHeight)
		c3.y = UI.height - UI.StatusBarHeight - 3;
	if (c3.y < UI.ToolBarHeight)
		c3.y = UI.ToolBarHeight + 3;

}

void CTriangle::DecreaseCount()
{
	Count--;
}

void CTriangle::IncreaseCount()
{
	Count++;
}



void CTriangle::Move(Point Pm)
{
	int diffX, diffY;
	Point center;
	center.x = (c1.x + c2.x + c3.x) / 3;
	center.y = (c1.y + c2.y + c3.y) / 3;
	int xi = center.x;
	int yi = center.y;
	center = Pm;
	diffX = center.x - xi;
	diffY = center.y - yi;
	c1.x += diffX;
	c1.y += diffY;
	c2.x += diffX;
	c2.y += diffY;
	c3.x += diffX;
	c3.y += diffY;
	Point * PxMax,* PyMax, *PxMin, *PyMin;
	Point arrP[3] = { c1, c2, c3 };
	PxMax = &c1;
	PyMax = &c1;
	PxMin = &c1;
	PyMin = &c1;
	for (int i = 0; i < 3; i++)
	{
		if (arrP[i].x > PxMax->x)
			PxMax = &arrP[i];
		if (arrP[i].x < PxMin->x)
			PxMin = &arrP[i];
		if (arrP[i].y > PyMax->y)
			PyMax = &arrP[i];
		if (arrP[i].y < PyMin->y)
			PyMin = &arrP[i];
	}
	if (PyMax->y > (UI.height - UI.StatusBarHeight))
	{
		int yi2 = PyMax->y;
		int DiffY2 = UI.height - UI.StatusBarHeight - 1 - yi2;
		c1.y += DiffY2;
		c2.y += DiffY2;
		c3.y += DiffY2;
	}
	if (PyMin->y < (UI.ToolBarHeight))
	{
		int yi2 = PyMin->y;
		int DiffY2 = UI.ToolBarHeight + 1 - yi2;
		c1.y += DiffY2;
		c2.y += DiffY2;
		c3.y += DiffY2;
	}
	if (PxMax->x > (UI.width))
	{
		int xi2 = PxMax->x;
		int DiffX2 = UI.width - 1 - xi2;
		c1.x += DiffX2;
		c2.x += DiffX2;
		c3.x += DiffX2;
	}
	if (PxMin->x < 0)
	{
		int xi2 = PxMin->x;
		int DiffX2 = 1 - xi2;
		c1.x += DiffX2;
		c2.x += DiffX2;
		c3.x += DiffX2;
	}
}

bool CTriangle::CheckSelection(int x, int y)
{
	bool selected=false;

	Point v[3] = { c1, c2, c3 };

	int count = 0;

	double slope = (double(c2.y) - double(c1.y)) / (double(c2.x) - double(c1.x));
	double slope2 = (double(c2.y) - double(c3.y)) / (double(c2.x) - double(c3.x));
	double slope3 = (double(c1.y) - double(c3.y)) / (double(c1.x) - double(c3.x));

	// x = ((y-y1)/slope) + X1;

	int _x = ((double(y) - double(c2.y)) / slope) + double(c2.x);
	int _x2 = ((double(y) - double(c2.y)) / slope2) + double(c2.x);
	int _x3 = ((double(y) - double(c1.y)) / slope3) + double(c1.x);

	int xmin = c1.x;
	int xmax = c1.x;
	int ymin = c1.y;
	int ymax = c1.y;

	for (int i = 0; i < 3; i++)
	{
		if (v[i].x <= xmin)
			xmin = v[i].x;
		if (v[i].x >= xmax)
			xmax = v[i].x;

		if (v[i].y <= ymin)
			ymin = v[i].y;
		if (v[i].y >= ymax)
			ymax = v[i].y;
	}

	if (_x >= x && _x <= xmax && _x >= xmin)
		count++;
	if (_x2 >= x && _x2 <= xmax && _x2 >= xmin)
		count++;

	if (_x3 >= x && _x3 <= xmax && _x3 >= xmin)
		count++;

	if (x >= xmin && x <= xmax && y >= ymin && y <= ymax)
		selected = true;


	return selected && count % 2 != 0;

}

void CTriangle::Save(ofstream& OutFile)
{
	string fcname = Output::GetColorName(FigGfxInfo.FillClr); // Fill color
	string dcname = Output::GetColorName(FigGfxInfo.DrawClr); // Draw color

	OutFile << "TRIANGLE" << "\t" << ID << "\t" << c1.x << "\t" << c1.y << "\t" << c2.x << "\t" << c2.y << "\t" << c3.x << "\t" << c3.y 
		<< "\t" << dcname << "\t" << fcname << endl;
}

int CTriangle::GetCount()
{
	return CTriangle::Count;
}

void CTriangle::PrintInfo(Output* pOut)
{
	string s = "Triangle ID: " + to_string(ID) + ", Fill Color: " + pOut->GetColorName(FigGfxInfo.FillClr) + ", Draw Color: " + pOut->GetColorName(FigGfxInfo.DrawClr) + ", Point 1: (" + to_string(c1.x) + "," + to_string(c1.y) + "), Point 2: (" + to_string(c2.x) + "," + to_string(c2.y) + "), Point 3: (" + to_string(c3.x) + "," + to_string(c3.y) + ")";
	pOut->PrintMessage(s);
}

CTriangle::~CTriangle()
{
	//CTriangle::Count--;
}
