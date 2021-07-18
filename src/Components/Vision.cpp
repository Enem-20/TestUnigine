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

	std::list<Unit> result;
	std::vector<std::vector<bool>> visited;
	std::queue<IVector2> q;
	static size_t visited_size = Grid::GetInstance().fieldSize.x / Grid::GetInstance().sectorSize.x;
	visited.resize(visited_size);
	for (auto& it : visited)
	{
		it.resize(visited_size);
	}

	
	Grid::GetInstance().GetUnits(owner->position, Sector::distance, result, visited, q);


	for (auto& unit : result)
	{
		//auto start = std::chrono::high_resolution_clock::now();
		CheckIntersect(unit);	
		//auto end = std::chrono::high_resolution_clock::now();
		//std::cout << std::chrono::duration<double>(end - start).count() << std::endl;
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
			VisibleAgents.push_back(unit);
	}
}