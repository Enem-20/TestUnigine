#pragma once

#include "../Helpers/Vector2.h"

#include <vector>
#include <memory>
#include <cmath>
#include <list>

class Unit;

struct Vision
{
	Vision(std::shared_ptr<Unit> owner, Vector2 r = 0.f);

	Vision() = default;

	Vision(Vision&& vision) noexcept
		: r(std::move(vision.r))
		, countVisibleAgents(std::move(vision.countVisibleAgents))
		, owner(std::move(vision.owner))
	{}

	Vision(const Vision& vision)
		: r(vision.r)
		, countVisibleAgents(vision.countVisibleAgents)
		, owner(vision.owner)
	{}

	void operator=(Vision&& vis)
	{
		this->r = std::move(vis.r);
		this->countVisibleAgents = std::move(vis.countVisibleAgents);
		this->owner = std::move(vis.owner);
	}

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

	//void Update();

	//void CheckIntersects();

	//void CheckIntersect(Unit& unit);

	Vector2 r;
	std::shared_ptr<Unit> owner;

	const size_t GetL1BlockSize() const;
	
	size_t countVisibleAgents;
private:
	size_t L1BlockSize;
	const size_t L1CacheSize = 389120;//in bytes. now size for pentium 4
	std::vector<Unit*> result;
	
	void CalcL1BlockSize();
};