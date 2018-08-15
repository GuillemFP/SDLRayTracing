#ifndef TEXTURE_H
#define TEXTURE_H

#include "Vector3.h"

class TextureData;
struct HitInfo;

class Texture
{
public:
	enum Type
	{
		Color = 0,
		Checker,
		NoTexture
	};

	static Vector3 GetColor(const HitInfo& hitInfo, const TextureData& textureData);
	virtual Vector3 GetColor(const HitInfo& hitInfo) const = 0;
};

class NoTexture : public Texture
{
public:
	virtual Vector3 GetColor(const HitInfo& hitInfo) const { return Vector3::zero; }
};

#endif // !TEXTURE_H