#include "Grid.h"

#include <array>
#include <iostream>

Grid::Grid(Vector2& fieldSize, Vector2& sectorSize)
{
	this->fieldSize = std::move(fieldSize);
	this->sectorSize = std::move(sectorSize);

	UnitsInSectors.resize(fieldSize.x / sectorSize.x);

	for (size_t i = 0; i < UnitsInSectors.size(); ++i)
	{
		UnitsInSectors[i].resize(fieldSize.y / sectorSize.y);
	}
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
	UnitsInSectors[cellPos.x][cellPos.y].push_back(unit);
}

void Grid::GetUnits(const Vector2& pos, const double& radius, std::list<Unit>& result, std::vector<std::vector<bool>>& visited, std::queue<IVector2>& q)	//Обход в ширину, собирает ближайшие секторы с сетки в заданном радиусе и возвращает всех юнитов, которые могут быть обнаружены
{
	q.push(GetCell(pos));
	visited[q.front().x][q.front().y] = true;
	result.insert(result.end(), GetInstance().UnitsInSectors[q.front().x][q.front().y].begin(), GetInstance().UnitsInSectors[q.front().x][q.front().y].end());
	while (!q.empty())
	{
		if (CheckMaxBorder(q.front().x, GetCell(pos).x, radius) && (!visited[q.front().x + 1][q.front().y]))
		{
			visited[q.front().x + 1][q.front().y] = true;
			q.push(IVector2(q.front().x + 1, q.front().y));
			result.insert(result.end(), GetInstance().UnitsInSectors[q.front().x + 1][q.front().y].begin(), GetInstance().UnitsInSectors[q.front().x + 1][q.front().y].end());
		}
		if (CheckMinBorder(q.front().x, GetCell(pos).x, radius) && (!visited[q.front().x - 1][q.front().y]))
		{
			visited[q.front().x - 1][q.front().y] = true;
			q.push(IVector2(q.front().x - 1, q.front().y));
			result.insert(result.end(), GetInstance().UnitsInSectors[q.front().x - 1][q.front().y].begin(), GetInstance().UnitsInSectors[q.front().x - 1][q.front().y].end());
		}
		if (CheckMaxBorder(q.front().y, GetCell(pos).y, radius) && (!visited[q.front().x][q.front().y+1]))
		{
			visited[q.front().x][q.front().y + 1] = true;
			q.push(IVector2(q.front().x, q.front().y+1));
			result.insert(result.end(), GetInstance().UnitsInSectors[q.front().x][q.front().y + 1].begin(), GetInstance().UnitsInSectors[q.front().x][q.front().y + 1].end());
		}
		if (CheckMinBorder(q.front().y, GetCell(pos).y, radius) && (!visited[q.front().x][q.front().y - 1]))
		{
			visited[q.front().x][q.front().y - 1] = true;
			q.push(IVector2(q.front().x, q.front().y-1));
			result.insert(result.end(), GetInstance().UnitsInSectors[q.front().x][q.front().y - 1].begin(), GetInstance().UnitsInSectors[q.front().x][q.front().y - 1].end());
		}
		q.pop();
	}
	//std::cout << sizeof(UnitsInSectors) * UnitsInSectors.size() * UnitsInSectors.size() << std::endl;
}

void Grid::GetUnitsFromCell(std::list<std::shared_ptr<Unit>>& result, IVector2& pos)
{



}

bool Grid::CheckMaxBorder(const int& CheckPos, const int& UnitPos, const double& radius)
{
	return ((CheckPos + 1) <= (UnitPos + radius)) && ((CheckPos + 1) < (fieldSize.x / sectorSize.x));
}

bool Grid::CheckMinBorder(const int& CheckPos, const int& UnitPos, const double& radius)
{
	return ((CheckPos - 1) >= (UnitPos - radius)) && ((CheckPos - 1) >= 0);
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