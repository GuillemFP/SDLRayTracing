#ifndef MODULEMATERIALS_H
#define MODULEMATERIALS_H

#define MODULEMATERIALS_NAME "ModuleMaterials"

#include "Module.h"

class Material;
class Texture;
struct MaterialData;
struct TextureData;

class ModuleMaterials : public Module
{
public:
	ModuleMaterials();
	~ModuleMaterials();

	Material* LoadMaterial(const MaterialData& data) const;

private:
	Texture* TextureFactory(const TextureData& data) const;
};

#endif // !MODULEMATERIALS_H