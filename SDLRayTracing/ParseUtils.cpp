#include "ParseUtils.h"

#include "Globals.h"
#include "Config.h"
#include "Math.h"

namespace ParseUtils
{
	math::float3 parseVector(const ConfigArray& config)
	{
		math::float3 vector;

		vector.x = config.GetFloatRequired(0);
		vector.y = config.GetFloatRequired(1);
		vector.z = config.GetFloatRequired(2);

		return vector;
	}

	EntityData parseEntityData(const Config& config)
	{
		EntityData data;

		data.type = parseEntityTypeFromString(config.GetStringRequired("Type"));
		data.position = parseVector(config.GetArray("Position"));
		data.radius = config.GetFloat("Radius", 1.0f);
		data.materialData = parseMaterialData(config.GetSection("Material"));

		return data;
	}

	Entity::Type parseEntityTypeFromString(const std::string& type)
	{
		if (type == "Sphere")
		{
			return Entity::Type::Sphere;
		}

		APPLOG("Invalid entity type");
	}

	MaterialData parseMaterialData(const Config& config)
	{
		MaterialData data;

		data.type = parseMaterialTypeFromString(config.GetStringRequired("Type"));
		data.albedo = parseVector(config.GetArray("Albedo"));

		return data;
	}

	Material::Type parseMaterialTypeFromString(const std::string& type)
	{
		if (type == "Diffuse")
		{
			return Material::Type::Diffuse;
		}

		APPLOG("Invalid material type");
	}
}