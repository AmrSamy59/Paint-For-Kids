#ifndef _CTRIANGLR_H
#define _CTRIANGLR_H
#include"../Figures\CFigure.h"
class CTriangle :public CFigure {
private:
	Point pointForResizing;
	Point c1, c2, c3, cc1, cc2, cc3;
	static int Count; // number of figures of this type
public:
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	virtual Point GetFigureCenter();
	virtual void Draw(Output* pOut) const;
	virtual void RefineShape();
	virtual void Move(Point Pm);
	virtual bool CheckSelection(int x, int y);
	virtual void Save(ofstream& OutFile);

	virtual void ResizeByDragging(Point& P1);
	static void DecreaseCount();
	static void IncreaseCount();

	static int GetCount();
	virtual void PrintInfo(Output* pOut);
	~CTriangle();
};
#endif // !1

