#pragma once
#include "Vector2D.h"
class Heuristic
{
public:
	Heuristic(int X, int Y);
	~Heuristic(void);

	int find(Vector2D start, Vector2D end);
	int findY(Vector2D start, Vector2D end);
	int findX(Vector2D start, Vector2D end);
	int maxX, maxY;
private:
	int heur;
	int numNodes;
};

