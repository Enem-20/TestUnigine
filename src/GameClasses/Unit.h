#pragma once

#include "../Helpers/Vector2.h"
#include "../Resources/ResourceManager.h"
#include "../Components/Vision.h"

#include <memory>

class Unit
{
public:
	Unit(std::string name = "", Vector2 position = 0, Vector2 r = 0);

	Unit(Unit&& unit) noexcept
		: position(std::move(unit.position))
		, name(std::move(unit.name))
		, vision(std::move(unit.vision))
	{}

	Unit(const Unit& unit)
		: position(unit.position)
		, name(unit.name)
		, vision(unit.vision)
	{}

	const std::shared_ptr<Vision> GetVision() const;

	Vector2 position;
	std::string name;
private:
	static size_t ID;
	std::shared_ptr<Vision> vision;
};