#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include "Texture.h"
#include "Vector3.h"

struct TextureData
{
	Texture::Type type;
	Vector3 color = Vector3::zero;
	Vector3 dimensions = Vector3::zero;
	std::vector<TextureData> subTextures;
	std::string image;
};

#endif // !TEXTUREDATA_H