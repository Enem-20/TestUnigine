#include "Vision.h"
#include "../GameClasses/Unit.h"
#include "../Resources/ResourceManager.h"

#define _USE_MATH_DEFINES
#include <math.h>

float Vision::Sector::angle;
float Vision::Sector::distance;

Vision::Vision(std::shared_ptr<Unit> owner, Vector2 r)
	: r(r)
	, owner(owner)
{}

void Vision::Update()
{
	CheckIntersects();
}

void Vision::CheckIntersects()
{
	VisibleAgents.clear();

	for (auto unit : ResourceManager::Units)
	{
		CheckIntersect(unit.second);
	}
}

void Vision::CheckIntersect(std::shared_ptr<Unit> unit)
{
	if (owner->name != unit->name)
	{
		Vector2 ownerToUnit(unit->position.x - owner->position.x, unit->position.y - owner->position.y);

		float alpha = atan2(r.y,r.x) - atan2(ownerToUnit.y,ownerToUnit.x);
		if (Sector::angle < 0) { Sector::angle += 2 * M_PI; }
		alpha *= 180 / M_PI;
		if ((alpha <= Sector::angle / 2) && (ownerToUnit.Length() <= Sector::distance))
			VisibleAgents.push_back(unit);
	}
}