#include "PerlinTexture.h"

#include "Globals.h"
#include "Math.h"
#include "PerlinNoise.h"
#include "HitInfo.h"

PerlinTexture::PerlinTexture(PerlinNoise* perlin, const Vector3& dimensions, const int depth, Type noiseType) : _perlin(perlin), _scale(dimensions), _depth(depth), _noiseType(noiseType)
{
}

PerlinTexture::~PerlinTexture()
{
	RELEASE(_perlin);
}

Vector3 PerlinTexture::GetColor(const HitInfo& hitInfo) const
{
	switch (_noiseType)
	{
	case PerlinTexture::Type::Standard:
		return Vector3::one * 0.5f * (_perlin->Turbulence(hitInfo.point * _scale, _depth) + 1.0f);
	case PerlinTexture::Type::Sin:
		return Vector3::one * 0.5f * (1.0f + sin(_scale.e[0] * hitInfo.point.e[0] + 10.0f * _perlin->Turbulence(hitInfo.point * _scale, _depth)));
	}
}