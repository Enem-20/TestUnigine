#include "Vision.h"
#include "../GameClasses/Unit.h"
#include "../Resources/ResourceManager.h"
#include "../Helpers/Grid.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <chrono>

float Vision::Sector::angle;
float Vision::Sector::distance;

//class IVector2Hash
//{
//public:
//	std::size_t operator()(const IVector2& c) const
//	{
//		return  std::hash<std::string>()(std::to_string(size_t(c.x + c.y) % 10000));
//	}
//};

Vision::Vision(std::shared_ptr<Unit> owner, Vector2 r)
	: r(std::move(r))
	, owner(owner)
{
	CalcL1BlockSize();
	result.reserve(9000);
}

void Vision::Update()
{
	CheckIntersects();
}

void Vision::CheckIntersects()
{
	countVisibleAgents = 0;

	std::unordered_map<IVector2, bool, IVector2Hash> visited;
	std::queue<IVector2> q;
	IVector2 checkVisited;

	result.clear();
	Grid::GetInstance().GetUnits(owner->position, Sector::distance, result, visited, q, checkVisited);

	const size_t size = result.size() / GetL1BlockSize();
	const size_t end_size = result.size() % GetL1BlockSize();

	for (size_t i = 0; i < size; ++i)
	{
		auto bias = result.begin();
		std::advance(bias, GetL1BlockSize() * i);

		auto unit = result.begin();
		if (i) { std::advance(unit, (GetL1BlockSize() * (i - 1)) + 1); }

		for (; unit != bias; ++unit)
		{
			CheckIntersect(**unit);
		}
	}

	if (end_size)
	{
		auto unit = result.begin();
		std::advance(unit, size * GetL1BlockSize() + 1);

		for (; unit != result.end(); ++unit)
		{
			CheckIntersect(**unit);
		}
	}
}

void Vision::CheckIntersect(Unit& unit)		//Отсекаем юнитов по полю зрения
{
	if (owner->ID != unit.ID)
	{
		Vector2 ownerToUnit(unit.position.x - owner->position.x, unit.position.y - owner->position.y);

		double alpha = (r.x * ownerToUnit.x + r.y * ownerToUnit.y) / (r.length * ownerToUnit.length);
		alpha = acos(alpha) * 180 / M_PI;

		if ((alpha <= Sector::angle / 2) && (ownerToUnit.length <= Sector::distance))
			++countVisibleAgents;
	}
}

void Vision::CalcL1BlockSize()
{
	L1BlockSize = L1CacheSize / sizeof(result);
}

const size_t Vision::GetL1BlockSize() const
{
	return L1BlockSize;
}