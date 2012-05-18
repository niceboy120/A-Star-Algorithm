#include "Heuristic.h"
#include <iostream>

using namespace std;

Heuristic::Heuristic(int X, int Y) : heur(0)
{
	maxX = X;
	maxY = Y;
}


Heuristic::~Heuristic(void)
{
}

int Heuristic::find(Vector2D start, Vector2D end)
{
	int xx = 0, yy = 0;
	if(start.getX() < end.getX())
	{
		// Subtract?
		xx = start.getX() + end.getX();
		yy = start.getY() + end.getY();
		if(xx < 0)
			xx += xx * -2;
		if(yy < 0)
			yy += yy * -2;
	}
	else
	{
		xx = start.getX() - end.getX();
		yy = start.getY() - end.getY();
	}

	//Check if it's a negative number; If it is, switch it.
	heur = yy + xx;
	//Print it out for debugging purposes.
	//cout << "XY: " << xx + yy  << endl;
	//findY(start, end);
	return heur * 10;
}

int Heuristic::findY(Vector2D start, Vector2D end)
{
	if(start.getY() == maxY)
		start.resetY();
	if(start.getY() == end.getY()){
		//Found;
		findX(start, end);
	} else {
		heur++;
		start.incrementY();
		findY(start, end);
	}
	return heur;
}

int Heuristic::findX(Vector2D start, Vector2D end)
{
	if(start.getX() == maxX)
		start.resetX();
	if(start.getX() == end.getX()){
		return heur;
	} else {
		heur++;
		start.incrementX();
		findX(start, end);
	}
	return heur;
}
