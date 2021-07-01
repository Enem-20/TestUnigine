#pragma once

#include <rapidjson/rapidjson.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>

#include <string>

class Vector2;

class Serializer
{
public:
	static const rapidjson::StringBuffer Serialize();
	static void SerializeUnits(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer);
	static void SerializeVector2(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const std::string& name, const Vector2& vec);
private:
	
};