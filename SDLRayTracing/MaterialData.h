#ifndef MATERIALDATA_H
#define MATERIALDATA_H

#include "Material.h"
#include "TextureData.h"

struct MaterialData
{
	Material::Type type;
	TextureData textureData;
	float fuzziness = 0.0f;
	float refractiveIndex = 1.0f;
};

#endif // !MATERIALDATA_H