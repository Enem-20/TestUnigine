#include "Unit.h"
#include "../Components/Vision.h"

#include "../Helpers/Grid.h"

size_t Unit::count;

Unit::Unit(Unit&& unit) noexcept
	: position(std::move(unit.position))
	, name(std::move(unit.name))
	, vision(std::move(unit.vision))
	, ID(std::move(unit.ID))
{}

Unit::Unit(const Unit& unit)
	: position(unit.position)
	, name(unit.name)
	, vision(unit.vision)
	, ID(unit.ID)
{}


Unit::Unit(std::string name, Vector2 position, Vector2 r)
	: position(std::move(position))
	, name(name)
{
	if (this->name == "") { this->name = "unit" + std::to_string(count); }
	ID = count;
	vision = std::make_shared<Vision>(std::make_shared<Unit>(*this), std::move(r));	
	
	ResourceManager::Units.emplace("unit" + std::to_string(count), std::make_shared<Unit>(*this));
	Grid::GetInstance().AddUnit(*this);


	++count;
}

Vision& Unit::GetVision()
{
	return *vision;
}