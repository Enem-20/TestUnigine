#pragma once

#include "../Helpers/Vector2.h"

#include <memory>
#include <vector>
#include <unordered_map>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

class Unit;

class ResourceManager
{
public:
	static void SetExecutablePath(const std::string& executablePath);
	static std::string getFileString(const std::string& relativeFilePath);

	static rapidjson::Document documentParse(const std::string& relativePath);
	static void loadJSONUnits(const std::string& relativePath);
	static void loadJSONVector2(Vector2& vec, const rapidjson::Value& val);

	typedef std::unordered_map<std::string, std::shared_ptr<Unit>> UnitsPool;
	static UnitsPool Units;
private:
	static std::string m_path;
};