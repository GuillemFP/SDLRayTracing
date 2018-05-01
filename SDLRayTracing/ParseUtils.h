#ifndef PARSEUTILS_H
#define PARSEUTILS_H

#include "EntityData.h"
#include "MathGeoLib\include\Math\float3.h"

class Config;
class ConfigArray;

namespace ParseUtils
{
	math::float3 parseVector(const ConfigArray& config, const math::float3& defaultValue = math::float3::one);

	EntityData parseEntityData(const Config& config);
	Entity::Type parseEntityTypeFromString(const std::string& type);

	MaterialData parseMaterialData(const Config& config);
	Material::Type parseMaterialTypeFromString(const std::string& type);
}

#endif // !PARSEUTILS_H