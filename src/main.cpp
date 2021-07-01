//Количество видимых юнитов я поместил внутрь объектов-юнитов при сериализации

//#define DEBUG
//#define RandomTest

#include "GameClasses/Unit.h"
#include "Helpers/Vector2.h"
#include "Resources/ResourceManager.h"
#include "Helpers/Grid.h"

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
	Vision::Sector::distance = rand() % 200 + 1;


	Grid::GetInstance(std::move(Vector2(10000.f, 10000.f)), std::move(Vector2(100.f, 100.f)));
	for (size_t i = 0; i < 10000; ++i)
	{
		bool sign1 = rand() % 2;
		bool sign2 = rand() % 2;
		double posX = sign1 ? rand() % 5000 * -1 : rand() % 5000;
		double posY = sign2 ? rand() % 5000 * -1 : rand() % 5000;
		Vector2 position(std::move(posX), std::move(posY));
		bool sign3 = rand() % 2;
		bool sign4 = rand() % 2;
		double posX2 = sign3 ? rand() % 5000 * -1 : rand() % 5000;
		double posY2 = sign4 ? rand() % 5000 * -1 : rand() % 5000;
		Vector2 r(std::move(posX2), std::move(posY2));

		Unit unit("", std::move(position), std::move(r));
	}
}
#endif

int main(int argc, char** argv)
{
	ResourceManager::SetExecutablePath(argv[0]);

#ifdef RandomTest
	auto start1 = std::chrono::high_resolution_clock::now();
	Randomize();
	auto end1 = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration<float>(end1 - start1) << std::endl;
#else
	ResourceManager::loadJSONUnits("/res/Scene.json");
#endif		
	for (auto unit : ResourceManager::Units)
	{
		unit.second->GetVision()->Update();
	}
#ifdef  DEBUG
	std::cout << "nulls: " << nulls << std::endl;
	std::cout << "ones: " << ones << std::endl;
	std::cout << "distance: " << Vision::Sector::distance << std::endl;
	std::cout << "angle: " << Vision::Sector::angle << std::endl;
#endif //  DEBUG

	ResourceManager::UnloadAllResources();
	system("pause");
	return 0;
}