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
#include "ImageTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image\stb_image.h"

ModuleMaterials::ModuleMaterials() : Module(MODULEMATERIALS_NAME)
{
	_rng = new math::LCG();
}

ModuleMaterials::~ModuleMaterials()
{
	RELEASE(_rng);

	for (VImageTex::reverse_iterator it = _images.rbegin(); it != _images.rend(); ++it)
		stbi_image_free(*it);
}

Material* ModuleMaterials::LoadMaterial(const MaterialData& data)
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

Texture* ModuleMaterials::TextureFactory(const TextureData& data)
{
	static_assert(Texture::Type::NoTexture == 4, "Update texture factory code");

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
			return new PerlinTexture(new PerlinNoise(*_rng), data.dimensions);
		}
		case Texture::Type::Image:
		{
			return new ImageTexture(CreateImage(data.image));
		}
	}	

	APPLOG("No texture, loading empty texture");

	return new NoTexture();
}

ImageData ModuleMaterials::CreateImage(const std::string& path)
{
	ImageData data;

	unsigned char* tex = stbi_load(path.c_str(), &data.nx, &data.ny, &data.nn, 0);
	_images.push_back(tex);
	data.tex = tex;

	return data;
}