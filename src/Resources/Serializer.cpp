#include "Serializer.h"

#include "../Components/Vision.h"
#include "ResourceManager.h"
#include "../GameClasses/Unit.h"

const rapidjson::StringBuffer Serializer::Serialize()
{
	rapidjson::StringBuffer sb;

	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

	writer.StartObject();

	writer.Key("angle");
	writer.Double(Vision::Sector::angle);
	writer.Key("distance");
	writer.Double(Vision::Sector::distance);

	SerializeUnits(writer);

	writer.EndObject();

	return sb;
}

void Serializer::SerializeUnits(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer)
{
	writer.Key("Units");
	writer.StartArray();
	for (const auto& unit : ResourceManager::Units)
	{
		writer.StartObject();

		writer.Key("name");
		writer.String(unit.second->name.c_str());

		SerializeVector2(writer, "position", unit.second->position);
		SerializeVector2(writer, "r", unit.second->GetVision().r);

		writer.Key("visible");
		writer.Int(unit.second->GetVision().countVisibleAgents);

		writer.EndObject();
	}
	writer.EndArray();
}

void Serializer::SerializeVector2(rapidjson::PrettyWriter<rapidjson::StringBuffer>& writer, const std::string& name, const Vector2& vec)
{
	writer.Key(name.c_str());
	writer.StartArray();
	writer.Double(vec.x);
	writer.Double(vec.y);
	writer.EndArray();
}