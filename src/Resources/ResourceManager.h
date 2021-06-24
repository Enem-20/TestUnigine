#pragma once

#include <memory>
#include <vector>

class Unit;

class ResourceManager
{
public:
	typedef std::vector<std::shared_ptr<Unit>> UnitsPool;
	static UnitsPool Units;
};