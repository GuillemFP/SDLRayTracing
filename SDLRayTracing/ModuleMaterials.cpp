#include "ModuleMaterials.h"

#include "Diffuse.h"
#include "Material.h"
#include "MaterialData.h"

ModuleMaterials::ModuleMaterials() : Module(MODULEMATERIALS_NAME)
{
}

ModuleMaterials::~ModuleMaterials()
{
}

Material* ModuleMaterials::LoadMaterial(const MaterialData& data) const
{
	static_assert(Material::Type::Unknown == 1, "Update material factory code");

	switch (data.type)
	{
	case Material::Type::Diffusive:
		return new Diffuse(data.albedo);
	}
}