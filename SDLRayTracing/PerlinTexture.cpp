#include "PerlinTexture.h"

#include "Globals.h"
#include "Math.h"
#include "PerlinNoise.h"
#include "HitInfo.h"

PerlinTexture::PerlinTexture(PerlinNoise* perlin, const Vector3& dimensions) : _perlin(perlin), _scale(dimensions)
{
}

PerlinTexture::~PerlinTexture()
{
	RELEASE(_perlin);
}

Vector3 PerlinTexture::GetColor(const HitInfo& hitInfo) const
{
	return Vector3::one * 0.5f * (_perlin->Noise(hitInfo.point * _scale) + 1.0f);
}