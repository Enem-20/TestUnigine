#include "Unit.h"

#include "../Helpers/Grid.h"

size_t Unit::ID;

Unit::Unit(std::string name, Vector2 position, Vector2 r)
	: position(std::move(position))
	, name(name)
{
	if (this->name == "") { this->name = "unit" + std::to_string(ID); }
	vision = std::make_shared<Vision>(std::make_shared<Unit>(*this), r);
	ResourceManager::Units.emplace("unit" + std::to_string(ID), std::make_shared<Unit>(*this));
	Grid::GetInstance().AddUnit(std::make_shared<Unit>(*this));
	
	++ID;
}

const std::shared_ptr<Vision> Unit::GetVision() const
{
	return vision;
}