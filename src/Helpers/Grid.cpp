#include "Grid.h"
#include "../Components/Vision.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <span>
#include <chrono>
#include <ppl.h>
//#include <omp.h>
//#include <intrin.h>

const int& myfloorF(const float& some)
{
	return int(some < 0 ? some - !!(some - int(some)) : some);
}

const int& myCeil(const float& some)
{
	return (some <= 0.0 ? (int)some : some > (int) some ? (int)some + 1 : (int)some);
}

Grid::Grid(Vector2& fieldSize, Vector2& sectorSize)
{
	this->fieldSize = std::move(fieldSize);
	this->sectorSize = std::move(sectorSize);
}

Grid::Grid(Grid&& grid) noexcept
	: sectorSize(std::move(grid.sectorSize))
	, fieldSize(std::move(grid.fieldSize))
	, UnitsInSectors(std::move(grid.UnitsInSectors))
{}

Grid::Grid(const Grid& grid)
	: sectorSize(grid.sectorSize)
	, fieldSize(grid.fieldSize)
	, UnitsInSectors(grid.UnitsInSectors)
{}

Grid& Grid::GetInstance(Vector2 fieldSize, Vector2 SectorSize)
{
	static Grid grid(fieldSize, SectorSize);
	return grid;
}

void Grid::AddUnit(Unit& unit)
{
	IVector2 cellPos(GetCell(unit.position));
	UnitsInSectors.emplace(std::move(cellPos), &unit);
}

void Grid::GetFromRadius(Unit& unit, IVector2& checkVisited, std::queue<IVector2>& q, std::unordered_map<IVector2, bool, IVector2Hash>& visited)
{
	//visited.clear();
	q.push(GetCell(unit.position));
	visited.emplace(q.front(), true);
	GetUnitIntersects(unit, q.front());

	while (!q.empty())
	{
		checkVisited = std::move(IVector2(q.front().x + 1, q.front().y));
		if (CheckMaxBorder(q.front().x, GetCell(unit.position).x, Vision::Sector::distance) && !visited.contains(checkVisited))
		{
			visited.emplace(checkVisited, true);
			q.push(checkVisited);
			GetUnitIntersects(unit, checkVisited);
		}
		checkVisited = std::move(IVector2(q.front().x - 1, q.front().y));
		if (CheckMinBorder(q.front().x, GetCell(unit.position).x, Vision::Sector::distance) && !visited.contains(checkVisited))
		{
			visited.emplace(checkVisited, true);
			q.push(checkVisited);
			GetUnitIntersects(unit, checkVisited);
		}
		checkVisited = std::move(IVector2(q.front().x, q.front().y + 1));
		if (CheckMaxBorder(q.front().y, GetCell(unit.position).y, Vision::Sector::distance) && !visited.contains(checkVisited))
		{
			visited.emplace(checkVisited, true);
			q.push(checkVisited);
			GetUnitIntersects(unit, checkVisited);
		}
		checkVisited = std::move(IVector2(q.front().x, q.front().y - 1));
		if (CheckMinBorder(q.front().y, GetCell(unit.position).y, Vision::Sector::distance) && !visited.contains(checkVisited))
		{
			visited.emplace(checkVisited, true);
			q.push(checkVisited);
			GetUnitIntersects(unit, checkVisited);
		}
		q.pop();
	}
}

inline void Grid::GetUnitIntersects(Unit& unitFirst, const IVector2& pos)
{
	if (UnitsInSectors.contains(pos)) [[likely]]
	{
		auto cellNumber = UnitsInSectors.bucket(pos);
		//register auto cellIter = UnitsInSectors.equal_range(pos);
		size_t size = UnitsInSectors.bucket_size(cellNumber);
		std::unordered_multimap<IVector2, Unit*, IVector2Hash>::iterator starter = UnitsInSectors.begin(cellNumber);
		size_t i = 0;			
		auto& vis = unitFirst.GetVision();
		//auto it = cellIter.first;
		auto it = UnitsInSectors.begin(cellNumber);
#pragma vector always
		if (it != UnitsInSectors.end())
		{
			for (i; i < size; ++i)
			{
				//CheckIntersect(unitFirst, *it->second);

				if (unitFirst.ID != it->second->ID) [[likely]]
				{
					Vector2 ownerToUnit1(it->second->position.x - unitFirst.position.x, it->second->position.y - unitFirst.position.y);
				////float alpha = atan2(vis.r.x * ownerToUnit1.y - ownerToUnit1.x * vis.r.y, vis.r.x * ownerToUnit1.x + vis.r.x * ownerToUnit1.y);
				float alpha = (vis.r * ownerToUnit1)/* / (vis.r.length * ownerToUnit1.length)*/;

				if (alpha > Vision::Sector::angle * (ownerToUnit1.x * ownerToUnit1.x + ownerToUnit1.y * ownerToUnit1.y) * (vis.r.x * vis.r.x + vis.r.y * vis.r.y))
				{
					if (ownerToUnit1.Length() <= Vision::Sector::distance)
						++vis.countVisibleAgents;
				}
				///*alpha = acos(alpha) * (unsigned int)180 / M_PI;

				//if ((alpha <= Vision::Sector::angle / 2) && ())
				//	++vis.countVisibleAgents;*/
				//}
				++it;
				}
			}
		}
	}
}

inline void Grid::CheckIntersect(Unit& main, Unit& first)	const	//Отсекаем юнитов по полю зрения
{
	auto& vis = main.GetVision();
	if (main.ID != first.ID)[[likely]]
	{
		Vector2 ownerToUnit1(first.position.x - main.position.x, first.position.y - main.position.y);
		//float alpha = atan2(vis.r.x * ownerToUnit1.y - ownerToUnit1.x * vis.r.y, vis.r.x * ownerToUnit1.x + vis.r.x * ownerToUnit1.y);
		float alpha = (vis.r * ownerToUnit1)/* / (vis.r.length * ownerToUnit1.length)*/;

		if (alpha > Vision::Sector::angle * (ownerToUnit1.x * ownerToUnit1.x + ownerToUnit1.y * ownerToUnit1.y) * (vis.r.x * vis.r.x + vis.r.y * vis.r.y))
		{
			if (ownerToUnit1.Length() <= Vision::Sector::distance)
				++vis.countVisibleAgents;
		}
		/*alpha = acos(alpha) * (unsigned int)180 / M_PI;

		if ((alpha <= Vision::Sector::angle / 2) && ())
			++vis.countVisibleAgents;*/
	}
}

const bool Grid::CheckMaxBorder(const int& CheckPos, const int& UnitPos, const double& radius) const
{
	return ((CheckPos + 1) <= (UnitPos + myCeil(radius / sectorSize.x)) && ((CheckPos + 1) < (fieldSize.x / sectorSize.x)));
}

const bool Grid::CheckMinBorder(const int& CheckPos, const int& UnitPos, const double& radius) const
{
	return ((CheckPos - 1) >= (UnitPos - myCeil(radius / sectorSize.x)) && ((CheckPos - 1) >= 0));
}

void Grid::Search(Vector2& pos, Vector2& radius)
{

}

Grid::~Grid()
{
	UnitsInSectors.clear();
}

void Grid::Update()
{

}

const IVector2 Grid::GetCell(const Vector2& pos) const //Нормализуем координаты (x,y) э (-беск;+беск) в (x,y) э [0;+беск)
{
	return std::move(IVector2(myfloorF((pos.x + fieldSize.x / 2) / sectorSize.x), myfloorF((pos.y + fieldSize.y / 2) / sectorSize.y)));
}