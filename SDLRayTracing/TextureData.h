#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include "Texture.h"
#include "Vector3.h"

struct TextureData
{
	Texture::Type type;
	Vector3 color;
};

#endif // !TEXTUREDATA_H