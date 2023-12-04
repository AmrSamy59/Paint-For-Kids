#ifndef _CCircle_H
#define _CCircle_H
#include"Figures/CFigure.h"
class CCircle :public CFigure {
private:
	Point point1,point2;
public:
	CCircle(Point, Point ,GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool CheckSelection(int x, int y);
	virtual void Save(ofstream& OutFile);

};


#endif // !1

