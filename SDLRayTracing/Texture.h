#ifndef TEXTURE_H
#define TEXTURE_H

#include "Vector3.h"

class TextureData;

class Texture
{
public:
	enum Type
	{
		Color = 0,
		NoTexture
	};

	static Vector3 GetColor(const TextureData& textureData);
	virtual Vector3 GetColor() const = 0;
};

class NoTexture : public Texture
{
public:
	virtual Vector3 GetColor() const { return Vector3::zero; }
};

#endif // !TEXTURE_H