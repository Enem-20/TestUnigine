#pragma once

#include "../Helpers/Vector2.h"

#include <vector>
#include <memory>
#include <cmath>

class Unit;

struct Vision
{
	Vision(std::shared_ptr<Unit> owner, Vector2 r = 0.f);

	Vision(Vision&& vision) noexcept
		: r(std::move(vision.r))
		, VisibleAgents(std::move(vision.VisibleAgents))
		, owner(std::move(vision.owner))
	{}

	Vision(const Vision& vision)
		: r(vision.r)
		, VisibleAgents(vision.VisibleAgents)
		, owner(vision.owner)
	{}

	struct Sector
	{
		Sector() = delete;
		~Sector() = delete;
		Sector(const Sector&) = delete;
		Sector& operator=(Sector&&) = delete;
		Sector(Sector&&) = delete;

		static float angle;
		static float distance;
	};

	void Update();

	void CheckIntersects();

	void CheckIntersect(Unit& unit);

	Vector2 r;
	std::vector<Unit> VisibleAgents;
	std::shared_ptr<Unit> owner;
};