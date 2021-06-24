#pragma once

#include "../Helpers/Vector2.h"
#include "../Resources/ResourceManager.h"
#include "../Components/Vision.h"

#include <memory>

class Unit
{
public:
	Unit()
	{
		vision = std::make_shared<Vision>(std::make_shared<Unit>(*this));
	}

	~Unit()
	{

	}

	Vector2 position;
private:
	std::shared_ptr<Vision> vision;
};