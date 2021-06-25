#pragma once

#include "../Helpers/Vector2.h"

#include <vector>
#include <memory>
#include <cmath>

class Unit;

struct Vision
{
	Vision(std::shared_ptr<Unit> owner, Vector2 r = 0.f, float angle = 0, float distance = 0)
		: r(r)
		, angle(angle)
		, distance(distance)
		, owner(owner)
	{}

	void Update();

	void CheckIntersects();

	void CheckIntersect(std::shared_ptr<Unit> unit);

	Vector2 r;
	float angle;
	float distance;
	std::vector<std::shared_ptr<Unit>> VisibleAgents;
	std::shared_ptr<Unit> owner;
};