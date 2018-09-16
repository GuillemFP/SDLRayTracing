#include "ModuleMaterials.h"

#include "CheckerTexture.h"
#include "ColorTexture.h"
#include "Dielectric.h"
#include "Diffuse.h"
#include "Material.h"
#include "MaterialData.h"
#include "Metal.h"
#include "Texture.h"
#include "TextureData.h"
#include "MathGeoLib\include\Algorithm\Random\LCG.h"
#include "PerlinNoise.h"
#include "PerlinTexture.h"

ModuleMaterials::ModuleMaterials() : Module(MODULEMATERIALS_NAME)
{
	rng = new math::LCG();
}

ModuleMaterials::~ModuleMaterials()
{
	RELEASE(rng);
}

Material* ModuleMaterials::LoadMaterial(const MaterialData& data) const
{
	static_assert(Material::Type::Unknown == 3, "Update material factory code");

	switch (data.type)
	{
	case Material::Type::Diffuse:
		return new Diffuse(TextureFactory(data.textureData));
	case Material::Type::Metal:
		return new Metal(TextureFactory(data.textureData), data.fuzziness);
	case Material::Type::Dielectric:
		return new Dielectric(data.refractiveIndex);
	}

	APPLOG("No material");
	return nullptr;
}

Texture* ModuleMaterials::TextureFactory(const TextureData& data) const
{
	static_assert(Texture::Type::NoTexture == 3, "Update texture factory code");

	Texture* texture = nullptr;

	switch (data.type)
	{
		case Texture::Type::Color:
		{
			return new ColorTexture(data.color);
		}
		case Texture::Type::Checker:
		{
			const std::vector<TextureData>& subTextures = data.subTextures;
			if (subTextures.size() < 2)
			{
				APPLOG("Wrong number of textures for checker texture in factory");
				return new NoTexture();
			}
			Texture* odd = TextureFactory(subTextures.at(0));
			Texture* even = TextureFactory(subTextures.at(1));
			return new CheckerTexture(odd, even, data.dimensions);
		}
		case Texture::Type::Perlin:
		{
			return new PerlinTexture(new PerlinNoise(*rng), data.dimensions);
		}
	}	

	APPLOG("No texture, loading empty texture");

	return new NoTexture();
}