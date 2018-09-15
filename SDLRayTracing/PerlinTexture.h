#ifndef PERLINTEXTURE_H
#define PERLINTEXTURE_H

#include "Texture.h"

class PerlinNoise;

class PerlinTexture : public Texture
{
public:
	PerlinTexture(PerlinNoise* perlin);
	~PerlinTexture();

	virtual Vector3 GetColor(const HitInfo& hitInfo) const;

private:
	PerlinNoise* _perlin = nullptr;
};

#endif // !PERLINTEXTURE_H
