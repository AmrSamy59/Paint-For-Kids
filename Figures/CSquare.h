#ifndef CSQUARE_H
#define CSQUARE_H
#include "../Figures/CFigure.h"
//#include "DEFS.h"
class CSquare : public CFigure {
private:
	Point center;
	int L; // Half the length
	static int Count; // number of figures of this type
public:
	CSquare(Point, GfxInfo FigureGfxInfo, int l=100); // Default Length = 100
	virtual void Draw(Output* pOut) const;
	virtual void Move(Output* pOut, Point Pm);
	virtual bool CheckSelection(int x, int y);
	virtual void Save(ofstream& OutFile);

	static int GetCount();
	~CSquare();


 
};
#endif