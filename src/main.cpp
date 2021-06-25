#include "GameClasses/Unit.h"
#include "Helpers/Vector2.h"
#include "Resources/ResourceManager.h"

#include <iostream>
#include <vector>
#include <memory>

int main(int argc, char** argv)
{
	ResourceManager::SetExecutablePath(argv[0]);

	ResourceManager::loadJSONUnits("/res/Scene.json");

	//ResourceManager::Units.emplace("unit1", std::make_shared<Unit>("unit1", Vector2(1.f, 1.f), Vector2(0.f, 1.f), 135.5, 2.f));
	//ResourceManager::Units.emplace("unit2", std::make_shared<Unit>("unit2", Vector2(1.f, 2.f), Vector2(1.f, 0.f), 135.5, 2.f));
	//ResourceManager::Units.emplace("unit3", std::make_shared<Unit>("unit3", Vector2(1.f, -1.5), Vector2(0.707, 0.707), 135.5, 2.f));

	for (auto unit : ResourceManager::Units)
	{
		unit.second->GetVision()->Update();
		std::cout << unit.second->GetVision()->VisibleAgents.size();
	}

	return 0;
}