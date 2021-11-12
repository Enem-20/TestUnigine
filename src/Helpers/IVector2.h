#pragma once

class IVector2
{
public:
	IVector2(int x = 0, int y = 0, int length = 0)
		: x(x)
		, y(y)
		, length(length)
	{
		Length();
	}

	IVector2 operator-(const IVector2& p);

	IVector2 operator+(const IVector2& p);

	IVector2 operator*(const IVector2& p);

	friend IVector2 operator/(const IVector2& a, const IVector2& p)
	{
		IVector2 vec(a.x / p.x + a.y / p.y);
		vec.Length();
		return vec;
	}

	IVector2 operator=(const IVector2& p);

	IVector2 operator=(const int& initVal);

	bool operator==(const IVector2& v);

	friend bool operator==(const IVector2& a, const IVector2& b)
	{
		return (a.x == b.x) && (a.y == b.y);
	}

	friend IVector2&& operator-(const IVector2& v1, const IVector2& v2)
	{
		return IVector2(v1.x - v2.x, v1.y - v2.y);
	}

	//char m;
	int length;
	int x, y;
	//double t;
private:
	void Length();
};