#pragma once

#include "Point.h"

#include <cmath>

struct Vector2
{
	Vector2(int x = 0, int y = 0, int length = 0)
		: x(x)
		, y(y)
		, length(length)
	{}

	void operator-(const Vector2& p)
	{
		x -= p.x;
		y -= p.y;
	}

	void operator+(const Vector2& p)
	{
		x += p.x;
		y += p.y;
	}

	void operator=(const Vector2 p)
	{
		x = p.x;
		y = p.y;
	}

	void operator=(const float& initVal)
	{
		x = initVal;
		y = initVal;
	}

	float length;
	float x, y;
};