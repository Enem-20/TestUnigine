//Не стал заморачиваться с юнит-тестами и обработкой исключений для тестового, но могу, если надо

//#define DEBUG
//#define RandomTest

#include "GameClasses/Unit.h"
#include "Helpers/Vector2.h"
#include "Resources/ResourceManager.h"

#include <iostream>
#include <memory>

#ifdef RandomTest

#include <random>
#include <ctime>
#include <string>
#include <chrono>

#endif

#ifdef RandomTest
void Randomize()
{
	srand(time(NULL));
	Vision::Sector::angle = rand() % 361 + 1;
	Vision::Sector::distance = rand() % 40 + 1;

	for (size_t i = 0; i < 10000; ++i)
	{
		Vector2 position(rand() % 10000, rand() % 10000);
		Vector2 r(rand() % 10000, rand() % 10000);
		ResourceManager::Units.emplace("unit" + std::to_string(i), std::make_shared<Unit>("unit" + std::to_string(i), position, r));
	}
}
#endif

int main(int argc, char** argv)
{
	ResourceManager::SetExecutablePath(argv[0]);

#ifdef RandomTest
	Randomize();
#else
	ResourceManager::loadJSONUnits("/res/Scene.json");
#endif		

	for (auto unit : ResourceManager::Units)
	{

		unit.second->GetVision()->Update();
#ifdef  DEBUG
	std::cout << unit.second->GetVision()->VisibleAgents.size() << std::endl;
#endif //  DEBUG
	}

	ResourceManager::UnloadAllResources();
	return 0;
}