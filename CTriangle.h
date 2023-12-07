#ifndef _CTRIANGLR_H
#define _CTRIANGLR_H
#include"Figures/CFigure.h"
class CTriangle :public CFigure {
private:
	Point c1, c2, c3;
public:
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual void Move(Output* pOut, Point Pm);
	virtual bool CheckSelection(int x, int y);
	virtual void Save(ofstream& OutFile);


};
#endif // !1

