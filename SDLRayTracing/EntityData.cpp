#include "EntityData.h"

#include "Config.h"
#include "Globals.h"
#include "Math.h"
#include "ParseUtils.h"

namespace EntityDataUtils
{
	EntityData parseEntityData(const Config& config)
	{
		EntityData data;

		data.type = typeFromString(config.GetString("Type"));
		data.position = ParseUtils::parseVector(config.GetArray("Position"));
		data.radius = config.GetFloat("Radius", 1.0f);

		return data;
	}

	Entity::Type typeFromString(const std::string& type)
	{
		if (type == "Sphere")
		{
			return Entity::Type::Sphere;
		}

		APPLOG("Invalid entity type");
	}
}
