#include "Vector2.h"

void Vector2::operator-(const Vector2& p)
{
	x -= p.x;
	y -= p.y;
}

void Vector2::operator+(const Vector2& p)
{
	x += p.x;
	y += p.y;
}

void Vector2::operator=(const Vector2 p)
{
	x = p.x;
	y = p.y;
}

void Vector2::operator=(const float& initVal)
{
	x = initVal;
	y = initVal;
}

bool Vector2::operator==(const Vector2 v)
{
	return ((x == v.x) && (y == v.y));
}

float Vector2::Length() const
{
	return sqrt(x * x + y * y);
}