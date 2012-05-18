#pragma once
class Vector2D
{
public:
	Vector2D(int xin,int yin);
	Vector2D();
	~Vector2D(void);
	int getX(){return x;};
	int getY(){return y;};
	void incrementX();
	void incrementY();
	void resetX(void);
	void resetY(void);
private:
	int x, y;
};

