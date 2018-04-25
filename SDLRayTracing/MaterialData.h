#ifndef MATERIALDATA_H
#define MATERIALDATA_H

#include "Material.h"

struct MaterialData
{
	Material::Type type;
	math::float3 albedo;
};

#endif // !MATERIALDATA_H