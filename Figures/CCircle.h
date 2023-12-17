#ifndef _CCircle_H
#define _CCircle_H
#include"../Figures/CFigure.h"
class CCircle :public CFigure {
private:
	Point point1;
	int radius; // Because it doesn't always depend on Second Point
public:
	CCircle(Point, int ,GfxInfo FigureGfxInfo);
	virtual Point GetFigureCenter();
	virtual void Draw(Output* pOut) const;
	virtual void Move(Point Pm);
	virtual bool CheckSelection(int x, int y);
	virtual void Save(ofstream& OutFile);

};


#endif // !1

