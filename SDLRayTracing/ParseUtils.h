#ifndef PARSEUTILS_H
#define PARSEUTILS_H

#include "EntityData.h"
#include "Vector3.h"
#include "MathGeoLib\include\Math\float3.h"

class Config;
class ConfigArray;

namespace ParseUtils
{
	math::float3 ParseFloat3(const ConfigArray& config, const math::float3& defaultValue = math::float3::one);
	Vector3 ParseVector(const ConfigArray& config, const Vector3& defaultValue = Vector3::one);

	EntityData ParseEntityData(const Config& config);

	ShapeData ParseShapeData(const Config& config);
	Shape::Type ParseShapeTypeFromString(const std::string& type);

	MaterialData ParseMaterialData(const Config& config);
	Material::Type ParseMaterialTypeFromString(const std::string& type);
}

#endif // !PARSEUTILS_H