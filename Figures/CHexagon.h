#ifndef _CHEXAGON_H
#define _CHEXAGON_H
#include"../Figures/CFigure.h"
class CHexagon :public CFigure
{
private:
	Point center;
	int L; // Half The Height
	static int Count; // number of figures of this type
public:
	CHexagon(Point,GfxInfo FigureGfxInfo,bool zeroID, int l=100); // Default Length = 100
	virtual Point GetFigureCenter();
	virtual void Draw(Output* pOut) const;
	virtual void Move(Point Pm);
	virtual bool CheckSelection(int x, int y);
	virtual void Save(ofstream& OutFile);

	virtual void ResizeByDragging(Point& P);

	static void SetCount(int i);

	static int GetCount();
	~CHexagon();

};

#endif // !1

