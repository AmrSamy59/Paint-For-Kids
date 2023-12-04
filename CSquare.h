#ifndef CSQUARE_H
#define CSQUARE_H
#include "Figures/CFigure.h"
//#include "DEFS.h"
class CSquare : public CFigure {
private:
	Point center;

public:
	CSquare(Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool CheckSelection(int x, int y);
	virtual void Save(ofstream& OutFile);






 
};
#endif