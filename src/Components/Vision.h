#pragma once

#include "../Helpers/Vector2.h"

#include <vector>
#include <memory>

class Unit;

struct Vision
{
	Vision(std::shared_ptr<Unit> owner, Vector2 r = 0.f, float angle = 0, float distance = 0)
		: r(r)
		, angle(angle)
		, distance(distance)
		, owner(owner)
	{}

	void Update()
	{
		CheckIntersects();
	}

	void CheckIntersects()
	{
		VisibleAgents.clear();

		for (auto unit : ResourceManager::Units)
		{
			if (owner != unit)
			{

			}
		}
	}

	Vector2 r;
	float angle;
	float distance;
	std::vector<std::shared_ptr<Unit>> VisibleAgents;
	std::shared_ptr<Unit> owner;
};