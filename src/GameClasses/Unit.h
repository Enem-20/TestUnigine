#pragma once

#include "../Helpers/Vector2.h"
#include "../Helpers/IVector2.h"
#include "../Resources/ResourceManager.h"
#include "../Components/Vision.h"

#include <memory>

class Unit
{
public:
	Unit(std::string name = "", Vector2 position = 0, Vector2 r = 0);

	Unit(Unit&& unit) noexcept;

	Unit(const Unit& unit);

	
	const IVector2& GetCellPosition();

	Vision& GetVision();

	Vector2 position;

	size_t ID;
private:
	static size_t count;
	Vision vision;
public:	
	std::string name;
};