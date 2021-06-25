#pragma once

#include <rapidjson/rapidjson.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>

class Serializer
{
public:
	static const rapidjson::StringBuffer Serialize();
};