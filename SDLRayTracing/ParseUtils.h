#ifndef PARSEUTILS_H
#define PARSEUTILS_H

#include "EntityData.h"
#include "MathGeoLib\include\Math\float3.h"

class Config;
class ConfigArray;

namespace ParseUtils
{
	math::float3 ParseVector(const ConfigArray& config, const math::float3& defaultValue = math::float3::one);

	EntityData ParseEntityData(const Config& config);
	Entity::Type ParseEntityTypeFromString(const std::string& type);

	MaterialData ParseMaterialData(const Config& config);
	Material::Type ParseMaterialTypeFromString(const std::string& type);
}

#endif // !PARSEUTILS_H