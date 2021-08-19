#pragma once

#include <memory>
#include <vector>
#include <unordered_map>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

class Unit;
struct Vector2;

class ResourceManager
{
public:
	ResourceManager() = delete;
	~ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static void init();
	static void UnloadAllResources();
	static void SetExecutablePath(const std::string& executablePath);
	static std::string getFileString(const std::string& relativeFilePath);

	static rapidjson::Document documentParse(const std::string& relativePath);
	static void loadJSONUnits(const std::string& relativePath);
	static Vector2 loadJSONVector2(const rapidjson::Value& val, std::string name);
	static Vector2 loadJSONVector2(const rapidjson::Document& val, std::string name);
	static std::shared_ptr<Unit> getUnit(const std::string& name);

	typedef std::unordered_map<std::string, std::shared_ptr<Unit>> UnitsPool;
	static UnitsPool Units;

	static const size_t GetL1BlockSize();
private:
	static void CalcL1BlockSize();
	static size_t L1BlockSize;
	static size_t L1CacheSize;//in bytes. now size for pentium 4
	static std::string m_path;
};