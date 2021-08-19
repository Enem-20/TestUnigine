#pragma once 

#include "Vector2.h"

#include <vector>

class NavMask
{
public:
	static NavMask* GetInstance(Vector2 maskSize = 0, Vector2 SectorSize = 0);
	static Vector2& GetMaskSize();
	static void SetMaskSize(Vector2& vec);
private:
	NavMask(Vector2 maskSize = 0, Vector2 SectorSize = 0);

	Vector2 SectorSize;
	Vector2 maskSize;
	std::vector<std::vector<int>> grid;
	static NavMask* mask;
};