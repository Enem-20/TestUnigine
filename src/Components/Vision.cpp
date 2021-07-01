#include "Vision.h"
#include "../GameClasses/Unit.h"
#include "../Resources/ResourceManager.h"
#include "../Helpers/Grid.h"

#define _USE_MATH_DEFINES
#include <math.h>

float Vision::Sector::angle;
float Vision::Sector::distance;

Vision::Vision(std::shared_ptr<Unit> owner, Vector2 r)
	: r(std::move(r))
	, owner(owner)
{}

void Vision::Update()
{
	CheckIntersects();
}

void Vision::CheckIntersects()
{
	VisibleAgents.clear();

	for (auto unit : Grid::GetInstance().GetUnits(owner->position, Sector::distance))
	{
		CheckIntersect(unit);
	}
}

void Vision::CheckIntersect(std::shared_ptr<Unit> unit)		//Отсекаем юнитов по полю зрения
{
	if (owner->name != unit->name)
	{
		Vector2 ownerToUnit(unit->position.x - owner->position.x, unit->position.y - owner->position.y);

		double alpha = (r.x * ownerToUnit.x + r.y * ownerToUnit.y) / (r.length * ownerToUnit.length);
		alpha = acos(alpha) * 180 / M_PI;

		if ((alpha <= Sector::angle / 2) && (ownerToUnit.length <= Sector::distance))
			VisibleAgents.push_back(unit);
	}
}