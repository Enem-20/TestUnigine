#include "NavMask.h"

#include "../Resources/ResourceManager.h"

NavMask* NavMask::mask;

NavMask* NavMask::GetInstance(Vector2 vec, Vector2 SectorSize)
{
	if (mask == nullptr)
		return mask = new NavMask;
	return mask;
}

NavMask::NavMask(Vector2 maskSize, Vector2 SectorSize)
	: maskSize(maskSize)
	, SectorSize(SectorSize)
{
	mask->grid.reserve(static_cast<int>(maskSize.x / SectorSize.x));
	for (auto it : mask->grid)
	{
		it.reserve(static_cast<int>(maskSize.y));
	}
}

Vector2& NavMask::GetMaskSize()
{
	return mask->maskSize;
}

void NavMask::SetMaskSize(Vector2& vec)
{
	mask->maskSize = vec;
}