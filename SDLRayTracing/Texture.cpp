#include "Texture.h"

#include "TextureData.h"

Vector3 Texture::GetColor(const TextureData& textureData)
{
	switch (textureData.type)
	{
	case Texture::Type::Color:
		return textureData.color;
	case Texture::Type::NoTexture:
		return Vector3::zero;
	}
}