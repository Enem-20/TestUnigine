#pragma once

#include "../Helpers/Vector2.h"
#include "../Resources/ResourceManager.h"
#include "../Components/Vision.h"

#include <memory>

class Unit
{
public:
	Unit(std::string name = "", Vector2 position = 0, Vector2 r = 0, float angle = 0.f, float distance = 0.f)
		: position(position)
		, name(name)
	{
		vision = std::make_shared<Vision>(std::make_shared<Unit>(*this), r, angle, distance);
	}

	const std::shared_ptr<Vision> GetVision() const;

	Vector2 position;
	std::string name;
private:
	std::shared_ptr<Vision> vision;
};