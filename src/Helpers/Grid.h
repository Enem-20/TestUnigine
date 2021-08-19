#pragma once

#include "../GameClasses/Unit.h"
#include "IVector2.h"
#include "Vector2.h"

#include <vector>
#include <memory>
#include <string>
#include <queue>
#include <unordered_map>


class IVector2Hash
{
public:
	std::size_t operator()(const IVector2& c) const
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
	void GetUnits(const Vector2& pos, const double& radius, std::vector<Unit*>& result, std::unordered_map<IVector2, bool, IVector2Hash>& visited, std::queue<IVector2>& q, IVector2& checkVisited);
	void Update();
	const bool CheckMaxBorder(const int& CheckPos, const int& UnitPos, const double& radius) const;
	const bool CheckMinBorder(const int& CheckPos, const int& UnitPos, const double& radius) const;
	const IVector2 GetCell(const Vector2& pos) const;
	void GetUnitsFromCell(std::vector<Unit*>& result, const IVector2& pos);

	~Grid();

	Vector2 sectorSize;
	Vector2 fieldSize;
	std::unordered_multimap<IVector2, Unit*, IVector2Hash> UnitsInSectors;
private:
	void Search(Vector2& pos, Vector2& radius);
	Grid(Vector2& fieldSize, Vector2& sectorSize);
};