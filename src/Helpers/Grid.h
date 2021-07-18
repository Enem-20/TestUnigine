#pragma once

#include "../GameClasses/Unit.h"
#include "IVector2.h"

#include <vector>
#include <memory>
#include <string>
#include <queue>


class Vector2Hash
{
public:
	std::size_t operator()(const Vector2& c) const
	{
		return  std::hash<std::string>()(std::to_string(size_t(c.x + c.y) % 10000));
	}
};

class Grid
{
public:
	Grid() = delete;
	Grid(Grid&& grid) noexcept;
	Grid(const Grid& grid);

	static Grid& GetInstance(Vector2 SectorSize = 0, Vector2 fieldSize = 0);
	void AddUnit(Unit& unit);
	void GetUnits(const Vector2& pos, const double& radius, std::list<Unit>& result, std::vector<std::vector<bool>>& visited, std::queue<IVector2>& q);
	void Update();
	bool CheckMaxBorder(const int& CheckPos, const int& UnitPos, const double& radius);
	bool CheckMinBorder(const int& CheckPos, const int& UnitPos, const double& radius);
	const IVector2 GetCell(const Vector2& pos) const;
	void GetUnitsFromCell(std::list<std::shared_ptr<Unit>>& result, IVector2& pos);

	~Grid();

	Vector2 sectorSize;
	Vector2 fieldSize;
	std::vector<std::vector<std::list<Unit>>> UnitsInSectors;
private:
	void Search(Vector2& pos, Vector2& radius);
	Grid(Vector2& fieldSize, Vector2& sectorSize);

};