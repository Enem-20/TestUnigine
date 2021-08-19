#include "Grid.h"

#include <array>
#include <iostream>
#include <span>

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

void Grid::GetUnits(const Vector2& pos, const double& radius, std::vector<Unit*>& result, std::unordered_map<IVector2, bool, IVector2Hash>& visited, std::queue<IVector2>& q, IVector2& checkVisited)	//Обход в ширину, собирает ближайшие секторы с сетки в заданном радиусе и возвращает всех юнитов, которые могут быть обнаружены
{
	//size_t count_visited = 0;
	q.push(GetCell(pos));
	visited.emplace(q.front(), true);
	GetUnitsFromCell(result, q.front());
	while (!q.empty())
	{
		checkVisited = std::move(IVector2(q.front().x + 1, q.front().y));
		if (CheckMaxBorder(q.front().x, GetCell(pos).x, radius) && (visited.find(checkVisited) == visited.end()))
		{
			//++count_visited;
			visited.emplace(checkVisited, true);
			q.push(checkVisited); 
			GetUnitsFromCell(result, checkVisited);
		}
		checkVisited = std::move(IVector2(q.front().x - 1, q.front().y));
		if (CheckMinBorder(q.front().x, GetCell(pos).x, radius) && (visited.find(checkVisited) == visited.end()))
		{
			//++count_visited;
			visited.emplace(checkVisited, true);
			q.push(checkVisited);
			GetUnitsFromCell(result, checkVisited);
		}
		checkVisited = std::move(IVector2(q.front().x, q.front().y + 1));
		if (CheckMaxBorder(q.front().y, GetCell(pos).y, radius) && (visited.find(checkVisited) == visited.end()))
		{
			//++count_visited;
			visited.emplace(checkVisited, true);
			q.push(checkVisited);
			GetUnitsFromCell(result, checkVisited);
		}
		checkVisited = std::move(IVector2(q.front().x, q.front().y - 1));
		if (CheckMinBorder(q.front().y, GetCell(pos).y, radius) && (visited.find(checkVisited) == visited.end()))
		{
			//++count_visited;
			visited.emplace(checkVisited, true);
			q.push(checkVisited);
			GetUnitsFromCell(result, checkVisited);
		}
		q.pop();
	}
	//std::cout << count_visited << std::endl;
}

void Grid::GetUnitsFromCell(std::vector<Unit*>& result,const IVector2& pos)
{
	auto cell = UnitsInSectors.equal_range(pos);

	//size_t units_count = 0;

	if (cell.first != UnitsInSectors.end())
	{
		for(auto unit = cell.first; unit != cell.second; ++unit)
		result.push_back(unit->second);
		//++units_count;
	}	
	//std::cout << sizeof(cell) * units_count << std::endl;
}

const bool Grid::CheckMaxBorder(const int& CheckPos, const int& UnitPos, const double& radius) const
{
	return ((CheckPos + 1)/* * sectorSize.x*/ <= ((UnitPos + radius) / sectorSize.x)) && ((CheckPos + 1) < (fieldSize.x / sectorSize.x));
}

const bool Grid::CheckMinBorder(const int& CheckPos, const int& UnitPos, const double& radius) const
{
	return ((CheckPos - 1)/* * sectorSize.x*/ >= ((UnitPos - radius) / sectorSize.x)) && ((CheckPos - 1) >= 0);
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
	return std::move(IVector2(floor((pos.x + fieldSize.x/2) / sectorSize.x), floor((pos.y + fieldSize.y/2) / sectorSize.y)));
}