#include "PerlinTexture.h"

#include "Globals.h"
#include "Math.h"
#include "PerlinNoise.h"
#include "HitInfo.h"

PerlinTexture::PerlinTexture(PerlinNoise* perlin) : _perlin(perlin)
{
}

PerlinTexture::~PerlinTexture()
{
	RELEASE(_perlin);
}

Vector3 PerlinTexture::GetColor(const HitInfo& hitInfo) const
{
	return Vector3::one * _perlin->Noise(hitInfo.point);
}