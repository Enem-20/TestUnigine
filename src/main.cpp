//Количество видимых юнитов я поместил внутрь объектов-юнитов при сериализации

#define DEBUG
#define RandomTest

#include "Components/Vision.h"
#include "GameClasses/Unit.h"
#include "Helpers/Vector2.h"
#include "Helpers/IVector2.h"
#include "Resources/ResourceManager.h"
#include "Helpers/Grid.h"

#include <iostream>
#include <chrono>
#include <queue>
#include <unordered_map>
#include <ppl.h>

#ifdef RandomTest

#include <ctime>
#include <string>
#include <chrono>

#endif

#ifdef RandomTest
void Randomize()
{
	int size = 10000;
	size_t cellSize = size / 10;

	srand(time(NULL));
	Vision::Sector::angle = (1 + cos(/*rand() % 360 + 1*/135.5)) / 2;
	Vision::Sector::distance = cellSize/*rand() % 10000 + 1*/;	//for max performance Vision::Sector::distance <= grid.sectorSize.x

	Grid::GetInstance(std::move(Vector2(size, size)), std::move(Vector2(cellSize, cellSize)));

	//concurrency::parallel_for(0, size, [&](int i)
	//	{
	//		bool sign1 = rand() % 2;
	//		bool sign2 = rand() % 2;
	//		double posX = sign1 ? rand() % size * -1 : rand() % size;
	//		double posY = sign2 ? rand() % size * -1 : rand() % size;
	//		Vector2 position(std::move(posX), std::move(posY));
	//		bool sign3 = rand() % 2;
	//		bool sign4 = rand() % 2;
	//		double posX2 = sign3 ? rand() % size * -1 : rand() % size;
	//		double posY2 = sign4 ? rand() % size * -1 : rand() % size;
	//		Vector2 r(std::move(posX2), std::move(posY2));

	//		Unit("", std::move(position), std::move(r));
	//	});

#pragma omp simd
	for (size_t i = 0; i < size; ++i)
	{
		bool sign1 = rand() % 2;
		bool sign2 = rand() % 2;
		double posX = sign1 ? rand() % size * -1 : rand() % size;
		double posY = sign2 ? rand() % size * -1 : rand() % size;
		Vector2 position(std::move(posX), std::move(posY));
		bool sign3 = rand() % 2;
		bool sign4 = rand() % 2;
		double posX2 = sign3 ? rand() % size * -1 : rand() % size;
		double posY2 = sign4 ? rand() % size * -1 : rand() % size;
		Vector2 r(std::move(posX2), std::move(posY2));

		Unit("", std::move(position), std::move(r));
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
	size_t nulls = 0;
	size_t ones = 0;


	ResourceManager::init();

	auto& grid = Grid::GetInstance();
	//IVector2 checkVisited;
	//std::queue<IVector2, std::vector<IVector2>> q;
	//std::unordered_map<IVector2, bool, IVector2Hash> visited1;
	//std::cout << sizeof(q) << " " << sizeof(visited) /*+ sizeof(checkVisited)*/ << std::endl;
	auto start = std::chrono::high_resolution_clock::now();

	concurrency::parallel_for_each(ResourceManager::Units.begin(), ResourceManager::Units.end(),
		[&](auto& unit)
		{
			IVector2 checkVisited;
			std::queue<IVector2> q;
			std::unordered_map<IVector2, bool, IVector2Hash> visited;
			grid.GetFromRadius(*unit.second, checkVisited, q, visited);
			//std::cout << unit.second->GetVision().countVisibleAgents << '\n';
		});

	//for (auto& unit : ResourceManager::Units)
	//{
	//	grid.GetFromRadius(*unit.second, checkVisited, q, visited);
	//	//std::cout << unit.second->name << ": " << unit.second->GetVision().countVisibleAgents << std::endl;
	//}

	auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration<double>(end - start).count() << std::endl;
#ifdef  DEBUG
	std::cout << "distance: " << Vision::Sector::distance << std::endl;
	std::cout << "angle: " << Vision::Sector::angle << std::endl;
#endif //  DEBUG

	system("pause");
	ResourceManager::UnloadAllResources();
	return 0;
}