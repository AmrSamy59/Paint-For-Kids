#ifndef _CHEXAGON_H
#define _CHEXAGON_H
#include"Figures/CFigure.h"
class CHexagon :public CFigure
{
private:
	Point center;
public:
	CHexagon(Point,GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool CheckSelection(int x, int y);
	virtual void Save(ofstream& OutFile);

};

#endif // !1

