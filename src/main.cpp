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

	for (auto unit : ResourceManager::Units)
	{
		unit.second->GetVision()->Update();
		std::cout << unit.second->GetVision()->VisibleAgents.size();
	}


	ResourceManager::UnloadAllResources();
	return 0;
}