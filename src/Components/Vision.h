#pragma once

#include "../Helpers/Vector2.h"

#include <vector>
#include <memory>
#include <cmath>

class Unit;

struct Vision
{
	Vision(std::shared_ptr<Unit> owner, Vector2 r = 0.f);

	struct Sector
	{
		static float angle;
		static float distance;
	};

	void Update();

	void CheckIntersects();

	void CheckIntersect(std::shared_ptr<Unit> unit);

	Vector2 r;
	std::vector<std::shared_ptr<Unit>> VisibleAgents;
	std::shared_ptr<Unit> owner;
};