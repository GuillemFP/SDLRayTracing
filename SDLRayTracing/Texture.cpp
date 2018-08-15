#include "Texture.h"

#include "Globals.h"
#include "TextureData.h"
#include "CheckerTexture.h"

Vector3 Texture::GetColor(const HitInfo& hitInfo, const TextureData& textureData)
{
	switch (textureData.type)
	{
	case Texture::Type::Color:
		return textureData.color;
	case Texture::Type::Checker:
	{
		if (textureData.subTextures.size() < 2)
		{
			APPLOG("Wrong number of subtextures for checker texture");
			return Vector3::zero;
		}
		Vector3 colorOdd = Texture::GetColor(hitInfo, textureData.subTextures.at(0));
		Vector3 colorEven = Texture::GetColor(hitInfo, textureData.subTextures.at(1));
		return CheckerTexture::GetColor(hitInfo, colorOdd, colorEven, textureData.dimensions);
	}
	case Texture::Type::NoTexture:
		return Vector3::zero;
	}
}