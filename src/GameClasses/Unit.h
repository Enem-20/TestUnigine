#pragma once

#include "../Helpers/Vector2.h"
#include "../Helpers/IVector2.h"
#include "../Resources/ResourceManager.h"
//#include "../Components/Vision.h"

#include <memory>

class Vision;

class Unit
{
public:
	Unit(std::string name = "", Vector2 position = 0, Vector2 r = 0);

	Unit(Unit&& unit) noexcept;

	Unit(const Unit& unit);

	Vision& GetVision();
	const IVector2& GetCellPosition();

	Vector2 position;
	std::string name;	
	size_t ID;
private:
	static size_t count;
	std::shared_ptr<Vision> vision;
};