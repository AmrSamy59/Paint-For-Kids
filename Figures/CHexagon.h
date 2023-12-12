#ifndef _CHEXAGON_H
#define _CHEXAGON_H
#include"../Figures/CFigure.h"
class CHexagon :public CFigure
{
private:
	Point center;
	int L; // Half The Height
public:
	CHexagon(Point,GfxInfo FigureGfxInfo, int l=100); // Default Length = 100
	virtual void Draw(Output* pOut) const;
	virtual void Move(Output* pOut, Point Pm);
	virtual bool CheckSelection(int x, int y);
	virtual void Save(ofstream& OutFile);

};

#endif // !1

