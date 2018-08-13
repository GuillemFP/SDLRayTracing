#include "ModuleMaterials.h"

#include "ColorTexture.h"
#include "Dielectric.h"
#include "Diffuse.h"
#include "Material.h"
#include "MaterialData.h"
#include "Metal.h"
#include "Texture.h"
#include "TextureData.h"

ModuleMaterials::ModuleMaterials() : Module(MODULEMATERIALS_NAME)
{
}

ModuleMaterials::~ModuleMaterials()
{
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
	Texture* texture = nullptr;

	switch (data.type)
	{
	case Texture::Type::Color:
		return new ColorTexture(data.color);
	}

	APPLOG("No texture, loading empty texture");

	return new NoTexture();
}