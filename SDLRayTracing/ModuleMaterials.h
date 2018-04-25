#ifndef MODULEMATERIALS_H
#define MODULEMATERIALS_H

#define MODULEMATERIALS_NAME "ModuleMaterials"

#include "Module.h"

class Material;
struct MaterialData;

class ModuleMaterials : public Module
{
public:
	ModuleMaterials();
	~ModuleMaterials();

	Material* LoadMaterial(const MaterialData& data) const;

private:

};

#endif // !MODULEMATERIALS_H