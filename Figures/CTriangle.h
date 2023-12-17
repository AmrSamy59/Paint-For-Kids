#ifndef _CTRIANGLR_H
#define _CTRIANGLR_H
#include"../Figures\CFigure.h"
class CTriangle :public CFigure {
private:
	Point c1, c2, c3;
public:
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	virtual Point GetFigureCenter();
	virtual void Draw(Output* pOut) const;
	virtual void Move(Point Pm);
	virtual bool CheckSelection(int x, int y);
	virtual void Save(ofstream& OutFile);


};
#endif // !1

