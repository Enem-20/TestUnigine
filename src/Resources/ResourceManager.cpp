#include "ResourceManager.h"
#include "../GameClasses/Unit.h"

#include <fstream>
#include <sstream>
#include <iostream>

ResourceManager::UnitsPool ResourceManager::Units;
std::string ResourceManager::m_path;

void ResourceManager::loadJSONUnits(const std::string& relativePath)
{
	rapidjson::Document d = documentParse(relativePath);

	float angle = d.FindMember("angle")->value.GetDouble();
	float distance = d.FindMember("distance")->value.GetDouble();

	for (const auto& unit : d.FindMember("Units")->value.GetArray())
	{
		std::string name = unit.FindMember("name")->value.GetString();
		Vector2 position;
		Vector2 r;
		loadJSONVector2(position, unit);
		loadJSONVector2(r, unit);

		Units.emplace(name, std::make_shared<Unit>(name, position, r, angle, distance));
	}
}

void ResourceManager::loadJSONVector2(Vector2& vec, const rapidjson::Value& val)
{
	size_t i = 0;
	for (const auto& arg : val.FindMember("position")->value.GetArray())
	{
		((i % 2) == 0) ? vec.x = arg.GetDouble() : vec.y = arg.GetDouble();
		++i;
	}
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