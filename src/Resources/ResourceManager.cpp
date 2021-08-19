#include "ResourceManager.h"
#include "../GameClasses/Unit.h"
#include "../Components/Vision.h"
#include "Serializer.h"
#include "../Helpers/Grid.h"
#include "../Helpers/Vector2.h"

#include <fstream>
#include <sstream>
#include <iostream>

ResourceManager::UnitsPool ResourceManager::Units;
std::string ResourceManager::m_path;
size_t ResourceManager::L1BlockSize;
size_t ResourceManager::L1CacheSize = 393216;

void ResourceManager::init()
{
	CalcL1BlockSize();
}

void ResourceManager::loadJSONUnits(const std::string& relativePath)
{
	rapidjson::Document d = documentParse(relativePath);

	Grid::GetInstance(std::move(loadJSONVector2(d, "fieldSize")), std::move(loadJSONVector2(d, "sectorSize")));
	Vision::Sector::angle = d.FindMember("angle")->value.GetDouble();
	Vision::Sector::distance = d.FindMember("distance")->value.GetDouble();

	for (const auto& unit : d.FindMember("Units")->value.GetArray())
	{
		std::string name = unit.FindMember("name")->value.GetString();

		Unit(
			std::move(name), 
			std::move(loadJSONVector2(unit, "position")), 
			std::move(loadJSONVector2(unit, "r"))
		);
	}
}

Vector2 ResourceManager::loadJSONVector2(const rapidjson::Value& val, std::string name)
{
	size_t i = 0;
	float x = 0.f;
	float y = 0.f;
	for (const auto& arg : val.FindMember(name.c_str())->value.GetArray())
	{
		((i % 2) == 0) ? x = arg.GetDouble() : y = arg.GetDouble();
		++i;
	}

	return std::move(Vector2(x,y));
}

Vector2 ResourceManager::loadJSONVector2(const rapidjson::Document& val, std::string name)
{
	size_t i = 0;
	float x = 0.f;
	float y = 0.f;
	for (const auto& arg : val.FindMember(name.c_str())->value.GetArray())
	{
		((i % 2) == 0) ? x = arg.GetDouble() : y = arg.GetDouble();
		++i;
	}

	return std::move(Vector2(x, y));
}

void ResourceManager::SetExecutablePath(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath)
{
	std::ifstream f;
	f.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);

	if (!f.is_open())
	{
		system("pause");
		return std::string();
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	f.close();
	return buffer.str();
}

rapidjson::Document ResourceManager::documentParse(const std::string& relativePath)
{
	const std::string JSONstring = getFileString(relativePath);

	rapidjson::Document d;
	rapidjson::ParseResult parseScene = d.Parse(JSONstring.c_str());

	if (parseScene.IsError())
	{
		std::cerr << "document isn't parse" << std::endl;
	}

	return d;
}

void ResourceManager::UnloadAllResources()
{
	std::ofstream f(m_path + "/res/SceneSerialized.json");

	f << Serializer::Serialize().GetString();
	f.close();
	Units.clear();
}

std::shared_ptr<Unit> ResourceManager::getUnit(const std::string& name)
{
	auto unit = Units.find(name);

	if (unit != Units.end())
	{
		return unit->second;
	}

	return nullptr;
}

void ResourceManager::CalcL1BlockSize()
{
	L1BlockSize = L1CacheSize / sizeof(Units);
}

const size_t ResourceManager::GetL1BlockSize()
{
	return L1BlockSize;
}