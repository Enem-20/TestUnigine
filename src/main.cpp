//Количество видимых юнитов я поместил внутрь объектов-юнитов при сериализации

#define DEBUG
#define RandomTest

#include "Components/Vision.h"
#include "GameClasses/Unit.h"
#include "Helpers/Vector2.h"
#include "Resources/ResourceManager.h"
#include "Helpers/Grid.h"
#include "Resources/ThreadPool.h"

#include <iostream>
#include <memory>
#include <chrono>
#include <functional>
#include <ppl.h>

#ifdef RandomTest

#include <ctime>
#include <string>
#include <chrono>

#endif

#ifdef RandomTest
void Randomize()
{
	srand(time(NULL));
	Vision::Sector::angle = 360/*rand() % 360 + 1*/;
	Vision::Sector::distance = 0/*rand() % 50 + 1*/;


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

		Unit("", std::move(position), std::move(r));
	}
	std::cout << sizeof(Grid::GetInstance().UnitsInSectors)/* * Grid::GetInstance().UnitsInSectors.size()*/ << std::endl;
}
#endif

int main(int argc, char** argv)
{
	ResourceManager::SetExecutablePath(argv[0]);

#ifdef RandomTest
	//auto start1 = std::chrono::high_resolution_clock::now();
	Randomize();
	//auto end1 = std::chrono::high_resolution_clock::now();

	//std::cout << "Random time: " << std::chrono::duration<double>(end1 - start1) << std::endl;
#else
	ResourceManager::loadJSONUnits("/res/Scene.json");
#endif		
	size_t nulls = 0;	
	size_t ones = 0;

	ResourceManager::init();

	auto start = std::chrono::high_resolution_clock::now();
	/*concurrency::parallel_for_each(ResourceManager::Units.begin(),
		ResourceManager::Units.end(),
			[&](auto& unit) 
			{
				unit.second->GetVision().Update();
			}
	);*/

	for (auto& unit : ResourceManager::Units)
	{
		unit.second->GetVision().Update();
	}

	//size_t size = ResourceManager::Units.size() / ResourceManager::GetL1BlockSize();
	//size_t end_size = ResourceManager::Units.size() % ResourceManager::GetL1BlockSize();

	//for (size_t i = 0; i < size; ++i)
	//{
	//	auto bias = ResourceManager::Units.begin();
	//	std::advance(bias, ResourceManager::GetL1BlockSize() * i);

	//	auto unit = ResourceManager::Units.begin();
	//	if (i) { std::advance(unit, (ResourceManager::GetL1BlockSize() * (i - 1)) + 1); }

	//	for (; unit != bias; ++unit)
	//	{
	//		unit->second->GetVision().Update();
	//		unit->second->GetVision().VisibleAgents.size() ? ++ones : ++nulls;
	//	}
	//}

	//if (end_size)
	//{
	//	auto unit = ResourceManager::Units.begin();
	//	std::advance(unit, size * ResourceManager::GetL1BlockSize() + 1);

	//	for (; unit != ResourceManager::Units.end(); ++unit)
	//	{
	//		unit->second->GetVision().Update();
	//		unit->second->GetVision().VisibleAgents.size() ? ++ones : ++nulls;
	//	}
	//}

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration<double>(end - start).count() << std::endl;
#ifdef  DEBUG
	//std::cout << "nulls: " << nulls << std::endl;
	//std::cout << "ones: " << ones << std::endl;
	std::cout << "distance: " << Vision::Sector::distance << std::endl;
	std::cout << "angle: " << Vision::Sector::angle << std::endl;
#endif //  DEBUG

	

	ResourceManager::UnloadAllResources();
	system("pause");
	return 0;
}