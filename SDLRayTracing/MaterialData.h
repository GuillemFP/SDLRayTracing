#ifndef MATERIALDATA_H
#define MATERIALDATA_H

#include "Material.h"
#include "MathGeoLib\include\Math\float3.h"

struct MaterialData
{
	Material::Type type;
	math::float3 albedo;
};

#endif // !MATERIALDATA_H