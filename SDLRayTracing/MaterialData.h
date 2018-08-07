#ifndef MATERIALDATA_H
#define MATERIALDATA_H

#include "Material.h"
#include "Vector3.h"

struct MaterialData
{
	Material::Type type;
	Vector3 albedo;
	float fuzziness = 0.0f;
	float refractiveIndex = 1.0f;
};

#endif // !MATERIALDATA_H