#include "Unit.h"

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
	if (this->name == "") /*[[likely]]*/{ this->name = "unit" + std::to_string(count); }
	ID = count;
	vision = std::move(Vision(std::make_shared<Unit>(*this), std::move(r)));	
	
	auto _This = std::make_shared<Unit>(*this);
	ResourceManager::Units.emplace("unit" + std::to_string(count), _This);
	Grid::GetInstance().AddUnit(*_This);


	++count;
}

Vision& Unit::GetVision()
{
	return vision;
}

const IVector2& Unit::GetCellPosition()
{
	auto gr = Grid::GetInstance();
	return gr.GetCell(position);
}