#include "ParseUtils.h"

#include "Globals.h"
#include "Config.h"
#include "Math.h"

namespace ParseUtils
{
	math::float3 parseVector(const ConfigArray& config, const math::float3& defaultValue)
	{
		math::float3 vector;

		vector.x = config.GetFloat(0, defaultValue.x);
		vector.y = config.GetFloat(1, defaultValue.y);
		vector.z = config.GetFloat(2, defaultValue.z);

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
			return Entity::Type::Sphere;

		APPLOG("Invalid entity type");
	}

	MaterialData parseMaterialData(const Config& config)
	{
		MaterialData data;

		data.type = parseMaterialTypeFromString(config.GetStringRequired("Type"));
		data.albedo = parseVector(config.GetArray("Albedo"));
		data.fuzziness = config.GetFloat("Fuzziness", 0.0f);
		data.refractiveIndex = config.GetFloat("RefractiveIndex", 1.0f);

		return data;
	}

	Material::Type parseMaterialTypeFromString(const std::string& type)
	{
		if (type == "Diffuse")
			return Material::Type::Diffuse;
		if (type == "Metal")
			return Material::Type::Metal;
		if (type == "Dielectric")
			return Material::Type::Dielectric;

		APPLOG("Invalid material type");
	}
}