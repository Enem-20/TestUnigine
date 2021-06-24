#pragma once

#include "Point.h"

#include <cmath>

struct Vector2
{
	Vector2(Point begin, Point direction, int length = 0)
		: begin(begin)
		, direction(direction)
		, length(length)
	{}

	Point GetBegin() const
	{
		return begin;
	}

	Point GetDirection() const
	{
		return direction;
	}

	void SetBegin(const Point& begin)
	{
		this->begin = begin;
		UpdateLength();
	}

	void SetDirection(const Point& direction)
	{
		this->direction = direction;
		UpdateLength();
	}

	int length;
private:
	Point begin;
	Point direction;

	void UpdateLength()
	{
		length = sqrt((direction.x - begin.x) * (direction.x - begin.x) + (direction.y - begin.y) * (direction.y - begin.y));
	}
};