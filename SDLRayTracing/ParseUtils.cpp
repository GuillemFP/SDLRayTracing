#include "ParseUtils.h"

#include "Globals.h"
#include "Config.h"
#include "Math.h"

namespace ParseUtils
{
	math::float3 ParseFloat3(const ConfigArray& config, const math::float3& defaultValue)
	{
		math::float3 vector;

		vector.x = config.GetFloat(0, defaultValue.x);
		vector.y = config.GetFloat(1, defaultValue.y);
		vector.z = config.GetFloat(2, defaultValue.z);

		return vector;
	}

	Vector3 ParseVector(const ConfigArray& config, const Vector3& defaultValue)
	{
		return ParseFloat3(config, defaultValue.toFloat3());
	}

	EntityData ParseEntityData(const Config& config)
	{
		EntityData data;

		data.type = ParseEntityTypeFromString(config.GetStringRequired("Type"));
		data.position = ParseVector(config.GetArray("Position"));
		data.radius = config.GetFloat("Radius", 1.0f);
		data.materialData = ParseMaterialData(config.GetSection("Material"));

		return data;
	}

	Entity::Type ParseEntityTypeFromString(const std::string& type)
	{
		if (type == "Sphere")
			return Entity::Type::Sphere;

		APPLOG("Invalid entity type");
	}

	MaterialData ParseMaterialData(const Config& config)
	{
		MaterialData data;

		data.type = ParseMaterialTypeFromString(config.GetStringRequired("Type"));
		data.albedo = ParseVector(config.GetArray("Albedo"));
		data.fuzziness = config.GetFloat("Fuzziness", 0.0f);
		data.refractiveIndex = config.GetFloat("RefractiveIndex", 1.0f);

		return data;
	}

	Material::Type ParseMaterialTypeFromString(const std::string& type)
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