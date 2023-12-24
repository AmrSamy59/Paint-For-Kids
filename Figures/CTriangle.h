#ifndef _CTRIANGLR_H
#define _CTRIANGLR_H
#include"../Figures\CFigure.h"
class CTriangle :public CFigure {
private:
	Point c1, c2, c3;
	static int Count; // number of figures of this type
public:
	CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo,bool );
	virtual Point GetFigureCenter();
	virtual void Draw(Output* pOut) const;
	virtual void Move(Point Pm);
	virtual bool CheckSelection(int x, int y);
	virtual void Save(ofstream& OutFile);

	virtual void ResizeByDragging(Point& P);
	static void DecreasCount();
	static void IncreasCount();

	static int GetCount();
	~CTriangle();
};
#endif // !1

