#include "Vector2.h"
#include <cmath>

Vector2 Vector2::operator-(const Vector2& p)
{
	Vector2 vec(x - p.x, y - p.y);
	//vec.Length();
	return vec;
}

Vector2 Vector2::operator+(const Vector2& p)
{
	Vector2 vec(x + p.x, y + p.y);
	//vec.Length();
	return vec;
}

Vector2 Vector2::operator=(const Vector2& p)
{
	x = p.x; y = p.y;
	//Length();
	return *this;
}

Vector2 Vector2::operator=(const double& initVal)
{
	Vector2 vec(initVal, initVal);
	//vec.Length();
	return vec;
}

bool Vector2::operator==(const Vector2& v)
{
	return ((x == v.x) && (y == v.y));
}

float Vector2::Length()
{
	return sqrt(x * x + y * y);
}