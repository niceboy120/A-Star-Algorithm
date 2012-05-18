#include "Vector2D.h"


Vector2D::Vector2D(int xin,int yin)
{
	x=xin; y=yin;
}

//Default constructor;
Vector2D::Vector2D(void){}

Vector2D::~Vector2D(void)
{
}

void Vector2D::incrementX(void)
{
	x++;
}

void Vector2D::incrementY(void)
{
	y++;
}

void Vector2D::resetX(void)
{
	x = 0;
}

void Vector2D::resetY(void)
{
	y = 0;
}