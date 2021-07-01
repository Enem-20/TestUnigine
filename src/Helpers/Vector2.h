#pragma once

#include <cmath>

struct Vector2
{
	Vector2(double x = 0, double y = 0, double length = 0)
		: x(x)
		, y(y)
		, length(length)
	{
		Length();
	}

	Vector2(const Vector2& vec)
		: x(vec.x)
		, y(vec.y)
		, length(vec.length)
	{}

	Vector2(Vector2&& vec) noexcept
		: x(std::move(vec.x))
		, y(std::move(vec.y))
		, length(std::move(vec.length))
	{}

	Vector2 operator-(const Vector2& p);

	Vector2 operator+(const Vector2& p);

	Vector2 operator*(const Vector2& p);

	friend Vector2 operator/(const Vector2& a, const Vector2& p)
	{
		Vector2 vec(a.x / p.x + a.y / p.y);
		vec.Length();
		return vec;
	}

	friend Vector2 operator%(const Vector2& a, const Vector2& p)
	{
		Vector2 vec((int)a.x % (int)p.x + (int)a.y % (int)p.y);
		vec.Length();
		return vec;
	}

	Vector2 operator=(const Vector2& p);

	Vector2 operator=(const double& initVal);

	bool operator==(const Vector2& v);

	friend bool operator==(const Vector2& a, const Vector2& b)
	{
		return (a.x == b.x) && (a.y == b.y);
	}

	double length;
	double x, y;
private:
	void Length();
};