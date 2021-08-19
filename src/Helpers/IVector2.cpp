#include "IVector2.h"

#include <cmath>

IVector2 IVector2::operator-(const IVector2& p)
{
	IVector2 vec(x - p.x, y - p.y);
	vec.Length();
	return vec;
}

IVector2 IVector2::operator+(const IVector2& p)
{
	IVector2 vec(x + p.x, y + p.y);
	vec.Length();
	return vec;
}

IVector2 IVector2::operator*(const IVector2& p)
{
	IVector2 vec(x * p.x + y * p.y);
	vec.Length();
	return vec;
}

IVector2 IVector2::operator=(const IVector2& p)
{
	IVector2 vec(p.x, p.y);
	x = p.x;
	y = p.y;
	Length();
	vec.Length();
	return vec;
}

IVector2 IVector2::operator=(const int& initVal)
{
	IVector2 vec(initVal, initVal);
	vec.Length();
	return vec;
}

bool IVector2::operator==(const IVector2& v)
{
	return ((x == v.x) && (y == v.y));
}

void IVector2::Length()
{
	length = sqrt(x * x + y * y);
}