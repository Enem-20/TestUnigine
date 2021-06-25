#pragma once

#include <cmath>

struct Vector2
{
	Vector2(int x = 0, int y = 0, int length = 0)
		: x(x)
		, y(y)
		, length(length)
	{}

	void operator-(const Vector2& p);

	void operator+(const Vector2& p);

	void operator=(const Vector2 p);

	void operator=(const float& initVal);

	bool operator==(const Vector2 v);

	float Length() const;

	float length;
	float x, y;
};