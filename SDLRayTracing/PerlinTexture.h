#ifndef PERLINTEXTURE_H
#define PERLINTEXTURE_H

#include "Texture.h"

class PerlinNoise;

class PerlinTexture : public Texture
{
public:
	enum class Type
	{
		Standard,
		Sin
	};

	PerlinTexture(PerlinNoise* perlin, const Vector3& dimensions, const int depth, Type noiseType);
	~PerlinTexture();

	virtual Vector3 GetColor(const HitInfo& hitInfo) const;

private:
	PerlinNoise* _perlin = nullptr;
	Vector3 _scale = Vector3::one;
	const int _depth = 1;
	Type _noiseType;
};

#endif // !PERLINTEXTURE_H
