#ifndef PERLINTEXTURE_H
#define PERLINTEXTURE_H

#include "Texture.h"

class PerlinNoise;

class PerlinTexture : public Texture
{
public:
	PerlinTexture(PerlinNoise* perlin, const Vector3& dimensions);
	~PerlinTexture();

	virtual Vector3 GetColor(const HitInfo& hitInfo) const;

private:
	PerlinNoise* _perlin = nullptr;
	Vector3 _scale = Vector3::one;
};

#endif // !PERLINTEXTURE_H
