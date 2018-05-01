#include "ModuleMaterials.h"

#include "Dielectric.h"
#include "Diffuse.h"
#include "Material.h"
#include "MaterialData.h"
#include "Metal.h"

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
		return new Diffuse(data.albedo);
	case Material::Type::Metal:
		return new Metal(data.albedo, data.fuzziness);
	case Material::Type::Dielectric:
		return new Dielectric(data.refractiveIndex);
	}
}