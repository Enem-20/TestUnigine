#pragma once

struct Point
{
	int x;
	int y;

	Point(int x = 0, int y = 0)
		: x(x)
		, y(y)
	{}

	void operator-(const Point& p)
	{
		x -= p.x;
		y -= p.y;
	}

	void operator+(const Point& p)
	{
		x += p.x;
		y += p.y;
	}

	void operator=(const Point p)
	{
		x = p.x;
		y = p.y;
	}

	void operator=(const int initVal)
	{
		x = initVal;
		y = initVal;
	}
};